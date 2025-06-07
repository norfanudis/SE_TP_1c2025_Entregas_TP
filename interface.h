#ifndef INTERFACE_H
#define INTERFACE_H

#define  LOOPS_BETWEEN_MEASSUREMENTS 10     //Veces que loopea entre actualizaciones de mediciones 
#define  TIME_BETWEEN_UPDATES 1000          //Tiempo entre actualizacion del LCD

// -------------- Funciones publicas ---------------------

void interfaceInit(void); 

void lcdInit();

void displayTime(void);

void interfaceUpdate(void);

void displayValues(float, float, float, float);

void displayTimeAndPower(float, float);

void userButtonInterrupt();

#endif