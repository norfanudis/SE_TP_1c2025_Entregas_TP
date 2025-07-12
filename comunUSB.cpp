#include "mbed.h"
#include "comunUSB.h"
#include "arm_book_lib.h"
#include "string.h"
#include "math.h"
#include "RTC.h"

//Declaración de objetos globales
UnbufferedSerial uartUsb(USBTX, USBRX, 115200);
DigitalOut comunicationIndicator(LED1);

// Declaración de funciones privadas
static void SetDateAndTime();

//Implementación de funciones publicas
void comunUSBInit(void){
    comunicationIndicator = OFF;    //Apaga el indicador de comunicación
    SetDateAndTime();               //Setea el tiempo via consola
    
}

void floatToString(char* str, float value, int integer, int decimal){   //Convierte un numero float en un string
    int integ, dec;

    for(int i=integer; i>0; i--){           //El loop divide el número original por potencias progresivas de 10, quedandose con
        integ = int(value/pow(10,i-1))%10;  //el dígito restante, obteniendo así los valores de decenas, centenas, etc
        str[integer-i] = '0'+integ;
    }
    if(decimal>0){
        str[integer] = '.';                     //Coloca una coma antes de los decimales
    }
    
    for(int j=1; j<=decimal;j++){           //realiza la misma operación, pero ahora multiplica por las potencias
        dec = int(value*pow(10,j))%10;      //y se queda con el ultimo digito
        str[integer+j] = '0'+dec;
    }
    str[integer+decimal+1] = '\0';          //Finaliza el string con el '\0'
}



void printToUSB(const char* str){
    comunicationIndicator = !comunicationIndicator;             //Enciende el led indicador
    uartUsb.write( str, strlen(str) );      //Escribe el mensaje en la consola 
    delay(COMMUNICATION_LED_ON);
    comunicationIndicator = !comunicationIndicator;            //Luego del delay, apaga el led
}

void comunUSBStringRead( char* str, int strLength ){
    int strIndex;
    for ( strIndex = 0; strIndex < strLength; strIndex++) {    //Continua leyendo la consola hasta llegar a la cantidad de caracteres deseados
        uartUsb.read( &str[strIndex] , 1 );
    }
    str[strLength]='\0';                                        //Finaliza el string con el '\0'
}           


//Implementaciónd e funciones privadas

static void SetDateAndTime(){                                   //Permite ingresar los calores de hora, minutos y segundos mediante la consola
    char year[5] = "2025";                                      //Ya inicializa el dia, mes y año, los cuales no son utilizados pero necesarios
    char month[3] = "05";                                       //Para la carga de datos
    char day[3] = "15";
    char hour[3] = "";
    char minute[3] = "";
    char second[3] = "";

    printToUSB("Ingrese el anio con 4 digitos (1900-2999): ");  
    comunUSBStringRead( year, 4);
    printToUSB("\r\n");

    printToUSB("Ingrese el mes con dos digitos (01-12): ");
    comunUSBStringRead( month, 2);
    printToUSB("\r\n");

    printToUSB("Ingrese el día del mes con dos digitos (01-12): ");
    comunUSBStringRead( day, 2);
    printToUSB("\r\n");

    printToUSB("Ingrese la hora con dos digitos (00-23): ");  
    comunUSBStringRead( hour, 2);
    printToUSB("\r\n");

    printToUSB("Ingrese los minutos con dos digitos (00-59): ");
    comunUSBStringRead( minute, 2);
    printToUSB("\r\n");

    printToUSB("Ingrese los segundos con dos digitos (00-59): ");
    comunUSBStringRead( second, 2);
    printToUSB("\r\n");
    
    printToUSB("La fecha y hora han sido configurada\r\n");

    RTCSetTimeAndDate(atoi(year), atoi(month), atoi(day), atoi(hour), atoi(minute), atoi(second) );    //Formatea los datos como enteros para la funcion del RTC
}
