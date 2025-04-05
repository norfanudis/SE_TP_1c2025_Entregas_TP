#include "mbed.h"
#include "arm_book_lib.h"
#include "math.h"

#define TIEMPO_ENTRE_MEDICIONES 1000    //Tiempo entre mediciones (en ms)
#define TIEMPO_ENCENDIDO_LED    500   	//Tiempo de prendido de LED de transmisión
#define FACTOR_CONV_TENSION		146		//Factor de conversión de tensión (Cambiar una vez realizada y calibrada a placa)
#define FACTOR_CONV_CORRIENTE	1.5		//Factor de conversión de corriente (Cambiar una vez realizada y calibrada a placa)
#define FRECUENCIA_CLOCK		72000000//Frecuencia del microcontrolador (en Hertz)	
#define PI						3.14159265


//------------ Declaracion de Entradas y salidas ----------------------------------------------------
AnalogIn   tension(A1);				//Medicion de tensión
AnalogIn   corriente(A2);			//Medicion de corriente
DigitalIn  cruceTensión(PB_13); 	//Detector de cruce por cero de la tensión
DigitalIn  cruceCorriente(PB_14);   //Detector de cruce por cero de la corriente

DigitalOut LEDComunicacion(PC_13);	//LED indicador de comunicación por UART

    
//------------ Variables públicas -------------------------------------------------------------------

float valorTensión;					//Valor medido de tension
float valorCorriente;				//Valor medido de corriente
float valorPotencia;				//Valor calculado de potencia
float valorFrecuencia;				//Valor calculado de potencia
float valorCosenoPhi;				//Valor calculado de coseno Phi

uint periodo;						//Periodo de la señal de tensión (En pulsos de clock)
uint defasaje;						//Defasaje entre tensión y corriente (En pulsos de clock)

bool adelantaTensión;				//Indica si adelanta tensión (true) o corriente (false)
bool crucePorCero;					//Indica si ya ocurrió un cruce por cero, permitiendo calcular el defasaje

//------------ Prototipos de funciones --------------------------------------------------------------
void inicEntradas();				//Inicialización de las entradas
void inicSalidas();					//Inicialización de las salidas
void inicVariables();				//Inicialización de las variables del sistema

void medirTension();				//Funcion para medir el valor de la entrada analógica y convertirla en un valor de tensión
void medirCorriente();				//Funcion para medir el valor de la entrada analógica y convertirla en un valor de corriente
void calcularVariables();			//Calcula las variables del sistema, como potencia y coseno phi
void enviarConsumo();				//Envia los datos por UART

//------------ Programa Principal --------------------------------------------------------------------

int main(){
	inicEntradas();
	inicSalidas();
	inicVariables();
	
		while(true){
		medirCorriente();
		medirTension();
		calcularVariables();
		enviarConsumo();
		delay(TIEMPO_ENTRE_MEDICIONES);
	}
}
	

//------------ Implementación de funciones ------------------------------------------------------------


//Comentario: Las funciones relacionadas a los timers todavía no se implementaron, pero se utilzian las variables de frecuencia y coseno phi

void inicEntradas(){
	cruceTensión.mode(PullDown);
	cruceCorriente.mode(PullDown);
}

void inicSalidas(){
	LEDComunicacion = OFF;
}

void inicVariables(){
	valorTensión = 0;
	valorCorriente = 0;
	valorPotencia = 0;
	valorFrecuencia = 0;
	valorCosenoPhi = 0;
	periodo = 0;
	defasaje = 0;
	adelantaTensión = true;
	crucePorCero = false;
}

void medirTension(){
	valorTensión = tension*FACTOR_CONV_TENSION;
}

void medirCorriente(){
	valorCorriente = corriente*FACTOR_CONV_CORRIENTE;
}

calcularVariables(){
	valorPotencia = valorCorriente*valorTensión;			//Se calcula la potencia 
	valorFrecuencia = 1/(float(periodo)/FRECUENCIA_CLOCK);	//Se calcula la frecuencia con el periodo y la frecuecia de Clock
	valorCosenoPhi = cos(2*PI*valorFrecuencia*(float(defasaje)/FRECUENCIA_CLOCK));	//Se calcula el defasaje con el coseno de 2Pi por la frecuencia y el defasaje
}

void enviarConsumo(){					//Por el momento se imprime por pantalla	
	LEDComunicacion = ON;
	printf("Tensión: %.1f, Corriente %.1f, Potencia %.1f\n", valorTensión, valorCorriente, valorPotencia);
	printf("Frecuencia: %.1f, Coseno Phi: %.1f, Potencia %.1f\n", valorFrecuencia, valorCosenoPhi);
	delay(TIEMPO_ENCENDIDO_LED);
	LEDComunicacion = OFF;
}
