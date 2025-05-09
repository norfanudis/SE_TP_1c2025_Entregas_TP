#include "mbed.h"
#include"string.h"

#include "interface.h"
#include "arm_book_lib.h"
#include "comunUSB.h"
#include "timing.h"
#include "meassurements.h"


void interfaceInit(void){
    meassurementsInit();
    timingInit();
    comunUSBInit();
}

void interfaceUpdate(void){
    if(getMeassureFlag()){
        inputMeassurements();
    }
    delay(1000);
    displayValues(getVoltageRMS(),getCurrentRMS(),getFrequency(),getPhase());
}

void displayValues(float voltage, float current, float frequency, float phase){
    char str_voltage[7]="";
    char str_current[6]="";
    char str_power[8]="";
    char str_frequency[6]="";
    char str_phase[6]="";

    char message[60]="";

    floatToString(str_voltage,voltage,3,2);
    floatToString(str_current,current,1,3);
    floatToString(str_power,voltage*current,4,2);
    floatToString(str_frequency,frequency,2,2);
    floatToString(str_phase,phase,1,3);


    sprintf(message,"--- Estado de la Red ---");
    printToUSB(message);
    sprintf(message,"Tensión: %s, Corriente: %s, Potencia: %s \n",str_voltage, str_current, str_power);
    printToUSB(message);
    sprintf(message,"Frecuencia: %s, Coseno Phi: %s \n",str_frequency, str_phase);
    printToUSB(message);
}
