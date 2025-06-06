#ifndef MEASSUREMENTS_H
#define MEASSUREMENTS_H


#define ROOT_2 1.414213562                              //Raiz de 2
#define MAX_ALLOWED_VOLTAGE 500                         //Se admite un valor máximo de tensión de 500V Pico 
#define MAX_ALLOWED_CURRENT 5                           //Se admite un valor de corriente de 5A pico
#define VOLTAGE_CONV_FACTOR 2*MAX_ALLOWED_VOLTAGE*ROOT_2 //Factor de corrección de tension
#define CURRENT_CONV_FACTOR 2*MAX_ALLOWED_CURRENT*ROOT_2 //Factor de conversión de corriente          

// -------------- Funciones publicas ---------------------

float getVoltage();

float getCurrent();

#endif