#include "mbed.h"
#include "HC06.h"
#include "comunUSB.h"

UnbufferedSerial HC06(PD_5, PD_6, 9600);

static void HC06StringWrite( const char* );
static bool HC06Ping(void);

void HC06Init(void){
    if(!HC06Ping()){
        printToUSB("Ocurrió un error con el modulo bluetooth");
    }
}

void HC06SendValues(float voltage, float current, float frequency, float phase){
    char str_voltage[6]="";
    char str_current[6]="";
    char str_frequency[5]="";
    char str_phase[5]="";
    char str_powerS[7]="";
    char str_powerP[7]="";
    char str_powerQ[7]="";

    char values[17]="";

    floatToString(str_voltage,voltage,3,1);             //Convierte los valores de tensión en string con 3 dígtos y 1 decimal
    floatToString(str_current,current,1,3);             //Realiza lo mismo con la corriente, con 1 dígito y 3 decimales
    floatToString(str_frequency,frequency,2,1);          
    floatToString(str_phase,phase,1,3);
    floatToString(str_powerS,voltage*current,4,1);
    floatToString(str_powerP,voltage*current*phase,3,1);
    floatToString(str_powerQ,voltage*current*sqrt(1-(phase*phase)),3,1);

    sprintf(values,"V+%s",str_voltage);                 //Envia los valores con un identificador en el caso de que se pierda un paquete
    HC06StringWrite(values);

    sprintf(values,"I+%s",str_current);
    HC06StringWrite(values);

    sprintf(values,"F+%s",str_frequency);
    HC06StringWrite(values);
    
    sprintf(values,"H+%s",str_phase);
    HC06StringWrite(values);

    sprintf(values,"S+%s",str_powerS);
    HC06StringWrite(values);

    sprintf(values,"P+%s",str_powerP);
    HC06StringWrite(values);

    sprintf(values,"Q+%s",str_powerQ);
    HC06StringWrite(values);
}

static void HC06StringWrite( const char* str ){
    HC06.write( str, strlen(str) );
}

static bool HC06Ping(){
    char receivedChar[4] = "";

    HC06.write("AT\r\n",4);                     //Envia comando "AT" al modulo bluetooth
    if( HC06.readable() ) {                     //Evalua si se puede leer el puerto UART
        HC06.read(&receivedChar,4);             //Recibe la respuesta
    }
    return !(strcmp(receivedChar,"OK\r\n"));    //Compara con "OK, strcmp() devuelve 0 cuando dos strings son iguales
}