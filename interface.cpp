#include "mbed.h"
#include"string.h"

#include "interface.h"
#include "arm_book_lib.h"
#include "comunUSB.h"
#include "meassurements.h"
#include "TextLCD.h"
#include "RTC.h"


// Objetos publicos
TextLCD lcd(D13,D12,D11,D10,D9,D8, TextLCD::LCD16x2);


// Variables privadas
static int timesLooped = 0;         //Variable que cuenta las veces loopeadas para medir las entradas



void interfaceInit(void){
    lcdInit();                      //Inicialización del modulo LCD
    comunUSBInit();                 //Inicialización del puerto USB
    lcd.cls();                      //Comienza con el LCD en blanco
}

void interfaceUpdate(void){                             
    displayTime();                                  //Actualiza el tiempo mostrado en el LCD
    timesLooped++;
    if(timesLooped >= LOOPS_BETWEEN_MEASSUREMENTS){ //Si lo actualizó una cantida de veces definida
        displayValues(getVoltage(),getCurrent());   //Actualiza los valores de tensión y corriente
        timesLooped = 0;                            //Y resetea la variable de conteo
    }
    delay(TIME_BETWEEN_UPDATES);                                    
}

void displayValues(float voltage, float current){
    char str_voltage[7]="";
    char str_current[6]="";

    char values[17]="";

    floatToString(str_voltage,voltage,3,1);             //Convierte los valores de tensión en string con 3 dígtos y 1 decimal
    floatToString(str_current,current,1,2);             //Realiza lo mismo con la corriente, con 1 dígito y 3 decimales

    sprintf(values,"%s V %s A",str_voltage,str_current);//Formatea el string para imprimir

    lcd.cls();                                          //Limpia la pantalla
    displayTime();                                      //Muestra el tiempo
    lcd.locate(0,1);                                    //Se posiciona en el renglon inferior
    lcd.printf(values);                                 //Muestra los valores de corriente y tensión
}

void lcdInit(){                     //Imprime el mensaje inicial para cargar la hora por consola
    lcd.cls();      
    lcd.locate(0,0);
    lcd.printf("Please input the");
    lcd.printf("time via console");
}


void displayTime(){                 //Muestra el tiempo en pantalla en el renglon superior
    char current_time[12]="";

    lcd.locate(0,0);
    RTCGetTime(current_time);       //Solicita el tiempo como string
    lcd.printf(current_time);
}