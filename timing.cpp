#include "mbed.h"
#include "arm_book_lib.h"
#include "timing.h"
#include "meassurements.h"
#include "math.h"

//Declaración de objetos globales

Timer pulse_duration;

InterruptIn voltage_zero_crossing(D15);
InterruptIn current_zero_crossing(D14);

// Declaración de variables privadas
static int difference, period;

static float frequency;
static float phase;

static bool alreadyCrossed;


// Declaración de funciones privadas

static void zeroCrossing(void);

//Implementación de funciones publicas

void timingInit(void){
    alreadyCrossed = 0;
    frequency = 0;
    phase = 0;

    voltage_zero_crossing.rise(&zeroCrossing);  //Interrupción de flanco ascendente
    current_zero_crossing.rise(&zeroCrossing);  //Interrupción de flanco ascendente
    pulse_duration.start();                     //Inicialización del clock

}

float getFrequency(){
    return frequency;
}

float getPhase(){
    return phase;
}

//Implementaciónd e funciones privadas

static void zeroCrossing(void){
    int time_between_pulses = pulse_duration.elapsed_time().count();    //Toma el tiempo entre pulsos con el clock

    if(!alreadyCrossed){                                                //Si no hubo un cruce por cero, es la misma señal
        pulse_duration.reset();                                         //Reicnicia el clock
        frequency = 1000000/time_between_pulses;                        //Obtiene la frecuencia
    }else {
        phase = cos(2*PI*frequency*(float(time_between_pulses)/1000000));   //Sino es la otra señal
    }
    alreadyCrossed = !alreadyCrossed;
}

