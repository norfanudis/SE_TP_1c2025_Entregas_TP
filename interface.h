#ifndef INTERFACE_H
#define INTERFACE_H

#define  SCREEN_UPDATES_VALUES 3     //Veces que loopea entre actualizaciones de mediciones 
#define  SCREEN_UPDATES_POWER 3
#define  TIME_BETWEEN_UPDATES 2000          //Tiempo entre actualizacion del LCD

// -------------- Funciones publicas ---------------------

void interfaceInit(void); 

void lcdInit();

void displayTime(void);

void displayDate(void);

void interfaceUpdate(void);

void displayValues(float, float, float, float);

void displayTimeAndDate(void);

void displayPowerValues(float, float, float);

void displayTimeAndPower(float, float);

void userButtonInterrupt();

void sdCardtimer();

#endif