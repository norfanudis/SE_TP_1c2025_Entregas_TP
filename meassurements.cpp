#include "mbed.h"
#include "arm_book_lib.h"
#include "meassurements.h"

//Declaración de objetos globales

AnalogIn  voltage(A1);			//Medicion de tensión
AnalogIn  current(A2);			//Medicion de corriente

// Declaración de funciones privadas
static float meassurePeakVoltage();
static float meassurePeakCurrent();

//Implementación de funciones publicas

float getVoltage(void){  
    return meassurePeakVoltage()/ROOT_2;
}

float getCurrent(void){  
    return meassurePeakCurrent()/ROOT_2;
}

//Implementaciónd e funciones privadas

static float meassurePeakVoltage(){
    float peakVoltage = 0;              //Inicializa las variables en cero
    float voltageRead = 0;
    for(int i=0; i<=4000; i++){         //Toma las sufcieintes muestra para garatnizar al menos dos ciclos de la señal
        voltageRead = voltage.read();   //Mide la tension analogica del puerto
        if(voltageRead > peakVoltage){  //Si es mayor, sobreescribe la existente
            peakVoltage = voltageRead;
        }
        wait_us(10);                    //Espera 10us antes de la siguiente toma
    }
    peakVoltage -=0.5;                  //Le resta la tension de offset de la señal
    peakVoltage *= VOLTAGE_CONV_FACTOR; //lo multiplica por el factor de conversión
    return peakVoltage;          //Por ultimo lo convierte en tension RMS
}

static float meassurePeakCurrent(){     //mismo procedimiento que la medicion de tensión 
    float peakCurrent = 0;              
    float currentRead = 0;
    for(int i=0; i<=4000; i++){
        currentRead = current.read();
        if(currentRead > peakCurrent){
            peakCurrent = currentRead;
        }
        wait_us(10);
    }
    peakCurrent -= 0.5;
    peakCurrent *= CURRENT_CONV_FACTOR;
    return peakCurrent;
}