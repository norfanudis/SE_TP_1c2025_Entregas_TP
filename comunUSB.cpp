#include "mbed.h"
#include "comunUSB.h"
#include "arm_book_lib.h"
#include "string.h"
#include "math.h"


UnbufferedSerial uartUsb(USBTX, USBRX, 115200);
DigitalOut comunicationIndicator(LED1);


void comunUSBInit(void){
    comunicationIndicator = OFF;
}

void floatToString(char* str, float value, int integer=4, int decimal=5){
    int integ, dec;

    for(int i=integer; i>0; i--){
        integ = int(value/pow(10,i-1))%10;
        str[integer-i] = '0'+integ;
    }
    str[integer] = '.';
    
    for(int j=1; j<=decimal;j++){
        dec = int(value*pow(10,j))%10;
        str[integer+j] = '0'+dec;
    }
    str[integer+decimal+1] = '\0';
}



void printToUSB(const char* str){
    comunicationIndicator = ON;
    uartUsb.write( str, strlen(str) );
    delay(COMMUNICATION_LED_ON);
    comunicationIndicator = OFF;
}


