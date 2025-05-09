#ifndef TIMING_H
#define TIMING_H

#define PI 3.1415926

void timingInit(void);

void tickHandler(void);

float getFrequency(void);

float getPhase(void);

void zeroCrossing(void);

#endif