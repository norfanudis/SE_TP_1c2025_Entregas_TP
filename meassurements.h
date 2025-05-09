#ifndef MEASSUREMENTS_H
#define MEASSUREMENTS_H

#define VOLTAGE_CONV_FACTOR 1
#define CURRENT_CONV_FACTOR 1
#define ROOT_2 1.414213562

void meassurementsInit();

float getVoltage();

float getCurrent();

float getVoltageRMS();

float getCurrentRMS();

void inputMeassurements();

void meassureTicker();

bool getMeassureFlag();

#endif