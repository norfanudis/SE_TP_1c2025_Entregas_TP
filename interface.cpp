#include "mbed.h"
#include"string.h"

#include "interface.h"
#include "arm_book_lib.h"
#include "meassurements.h"
#include "timing.h"
#include "comunUSB.h"
#include "TextLCD.h"
#include "RTC.h"
#include "sd_card.h"
#include "HC06.h"


// Objetos publicos
TextLCD lcd(D7,D0,D2,D6,D9,D8, TextLCD::LCD16x2);   //Declaración de los pines que usará el LCD
// D7:RS, D0:E, D2:D4, D6:D5, D9:D6, D8:D7

// Variables privadas
static int timesLooped = 0;         //Variable que cuenta las veces loopeadas para medir las entradas

Ticker sdCardSave;                    //Interrupción del pulsador OnBoard

typedef enum {                                          //Tipo enum para la Maquina de estados fiitos
    DISPLAY_INITIAL_MESSAGE,
    DISPLAY_VALUES,
    DISPLAY_POWER,
    DISPLAY_TIME_AND_DATE,
    SAVE_TO_SD
} interfaceState_t;

static interfaceState_t interfaceState = DISPLAY_INITIAL_MESSAGE;

void interfaceInit(void){
    lcdInit();                      //Inicialización del modulo LCD
    comunUSBInit();                 //Inicialización del puerto USB
    lcd.cls();                      //Comienza con el LCD en blanco
    timingInit();                   //Inicializa el módulo de timers
    sdCardInit();                   //Inicializa la SD
    HC06Init();
    interfaceState = DISPLAY_VALUES;
    sdCardSave.attach(&sdCardtimer,10s);
}

void interfaceUpdate(void){        
    switch(interfaceState){                                 //En caso de que se quiera inicializar la interfaz nuevamente
        case DISPLAY_INITIAL_MESSAGE:
            interfaceInit();
            interfaceState = DISPLAY_VALUES;
            break;
        case DISPLAY_VALUES:                                //Estado de muestra de variables
            timesLooped++;
            displayValues(getVoltage(),getCurrent(), getFrequency(), getPhase());   //Actualiza los valores de tensión y corriente
            if(timesLooped >= SCREEN_UPDATES_VALUES){ //Si lo actualizó una cantida de veces definida
                timesLooped = 0;                            //resetea la variable de conteo
                interfaceState = DISPLAY_TIME_AND_DATE;    //Y pasa al estado de mostrar potencia y tiempo
                }
            break;
        case DISPLAY_TIME_AND_DATE:
            displayTimeAndDate(); 
            interfaceState = DISPLAY_POWER;                //Vuelve a mostrar los valores de tension, corriente, etc.. 
            break;
        case DISPLAY_POWER:
            timesLooped++;
            displayPowerValues(getVoltage(),getCurrent(), getPhase());   //Actualiza los valores de tensión y corriente
            if(timesLooped >= SCREEN_UPDATES_POWER){ //Si lo actualizó una cantida de veces definida
                timesLooped = 0;                            //resetea la variable de conteo
                interfaceState = DISPLAY_VALUES;    //Y pasa al estado de mostrar potencia y tiempo
                HC06SendValues(getVoltage(),getCurrent(), getFrequency(), getPhase());
                }
            break;
        case SAVE_TO_SD:
            sdCardWriteLog(getVoltage(),getCurrent(), getFrequency(), getPhase());
            interfaceState = DISPLAY_VALUES;
            break;
    }
    delay(TIME_BETWEEN_UPDATES);                            //Tiempo entre refrescos
}

void lcdInit(){                     //Imprime el mensaje inicial para cargar la hora por consola
    lcd.cls();      
    lcd.locate(0,0);
    lcd.printf("Ingrese la hora ");
    lcd.locate(0,1);
    lcd.printf("via la consola");
}

void displayValues(float voltage, float current, float frequency, float phase){
    char str_voltage[6]="";
    char str_current[6]="";
    char str_frequency[5]="";
    char str_phase[5]="";

    char values[17]="";

    floatToString(str_voltage,voltage,3,1);             //Convierte los valores de tensión en string con 3 dígtos y 1 decimal
    floatToString(str_current,current,1,2);             //Realiza lo mismo con la corriente, con 1 dígito y 3 decimales
    floatToString(str_frequency,frequency,2,2);          
    floatToString(str_phase,phase,1,3);

    sprintf(values,"%s V %s A",str_voltage,str_current);//Formatea el string para imprimir

    lcd.cls();                                          //Limpia la pantalla
    lcd.locate(0,0);                                    //Se posiciona en el renglon inferior
    lcd.printf(values);                                 //Muestra los valores de corriente y tensión

    sprintf(values,"%s Hz %s",str_frequency,str_phase);//Formatea el string para imprimir
    lcd.locate(0,1);
    lcd.printf(values);

}

void displayTimeAndDate(){
    lcd.cls();
    lcd.locate(0,0);
    displayTime();
    lcd.locate(0,1);
    displayDate();

}

void displayPowerValues(float voltage, float current, float phase){
    char str_power1[17]="";
    char str_power2[17]="";
    char values[17]="";

    lcd.cls();
    lcd.locate(0,0);

    floatToString(str_power1,voltage*current,4,1);
    sprintf(values,"%s W",str_power1);       //Formatea el string para imprimir
    lcd.printf(values);
    
    floatToString(str_power1,voltage*current*phase,4,0);
    floatToString(str_power2,voltage*current*sqrt(1-(phase*phase)),4,0);

    sprintf(values,"%sVA %sVAR",str_power1, str_power2);       //Formatea el string para imprimir
    lcd.printf(values);
}

void displayTime(){                 //Muestra el tiempo en pantalla en el renglon superior
    char current_time[12]="";

    RTCGetTime(current_time);       //Solicita el tiempo como string
    lcd.printf(current_time);
}

void displayDate(){
    char current_date[12]="";

    RTCGetDate(current_date);       //Solicita el tiempo como string
    lcd.printf(current_date);
}


void sdCardtimer(){
    if(sdCardInserted()){
        interfaceState = SAVE_TO_SD;    //Cambia la variable de la maquina de estados finita
    }
}