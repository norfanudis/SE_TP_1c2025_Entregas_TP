#include "mbed.h"
#include "arm_book_lib.h"
#include "timing.h"
#include "meassurements.h"
#include "math.h"

Ticker frequency_timer;
uint32_t time_elapsed = 0;

float frequency;
float phase;

bool alreadyCrossed;

InterruptIn voltage_zero_crossing(D15);
InterruptIn current_zero_crossing(D14);

void timingInit(void){
    alreadyCrossed = 0;
    frequency = 0;
    phase = 0;

    voltage_zero_crossing.rise(&zeroCrossing);
    current_zero_crossing.rise(&zeroCrossing);

    frequency_timer.attach_us(&tickHandler, 10u);
}

void tickHandler(void){
    time_elapsed++;
}

float getFrequency(){
    return frequency;
}

float getPhase(){
    return phase;
}

void zeroCrossing(void){
    if(!alreadyCrossed){
        frequency = 1000000/time_elapsed;
        time_elapsed = 0;
    }else {
        phase = cos(2*PI*frequency*time_elapsed);
    }
    alreadyCrossed = !alreadyCrossed;
}

