#ifndef COMUNUSB_H
#define COMUNUSB_H

#define COMMUNICATION_LED_ON 500        //Tiempo de encendido del LED

// -------------- Funciones publicas ---------------------

void comunUSBInit(void);

void floatToString(char* , float, int, int);

void printToUSB(const char* str);


#endif