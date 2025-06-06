#include "mbed.h"
#include "arm_book_lib.h"
#include "interface.h"


int main(void){
    interfaceInit();        //Inicializa las interfaces y los módulos utilizados
    while(true){
        interfaceUpdate();  //En el loop, actualiza las interfaces y las variables internas
    }
}

