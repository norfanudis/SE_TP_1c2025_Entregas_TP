#include "mbed.h"
#include "arm_book_lib.h"
#include "meassurements.h"

Ticker meassure;

AnalogIn  voltage(A1);				//Medicion de tensión
AnalogIn  current(A2);			//Medicion de corriente

float peakVoltage;
float peakCurrent;

bool meassure_flag;

void meassurementsInit(void){
    peakVoltage = 0;
    peakCurrent = 0;
    meassure_flag = 0;
    meassure.attach_us(&meassureTicker, 1000000u);
}

float getVoltage(void){
    return peakVoltage;
}

float getCurrent(void){
    return peakCurrent;
}

float getVoltageRMS(void){
    return peakVoltage/ROOT_2;
}

float getCurrentRMS(void){
    return peakCurrent/ROOT_2;
}

void inputMeassurements(void){
    peakVoltage = peakCurrent = 0;
    float voltageRead, currentRead;
    for(int i=0; i<=4000; i++){
        voltageRead = voltage.read();
        if(voltageRead > peakVoltage){
            peakVoltage = voltageRead;
        }
        wait_us(10);
    }
    for(int i=0; i<=4000; i++){
        currentRead = current.read();
        if(currentRead > peakCurrent){
            peakCurrent = currentRead;
        }
        wait_us(10);
    }
    meassure_flag = 0;
}

void meassureTicker(){
    meassure_flag = 1;
}

bool getMeassureFlag(){
    return meassure_flag;    
}