//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "sd_card.h"

#include "comunUSB.h"
#include "RTC.h"

#include "FATFileSystem.h"
#include "SDBlockDevice.h"

#include "platform/mbed_retarget.h"

//Declaración de defines privados

#define SPI3_MOSI   PC_12
#define SPI3_MISO   PC_11
#define SPI3_SCK    PC_10
#define SPI3_CS     PA_4_ALT0

//Declaración de objetos globales

SDBlockDevice sd( SPI3_MOSI, SPI3_MISO, SPI3_SCK, SPI3_CS );    //Puerto SPI para la comunicación con la SD
FATFileSystem fs("sd", &sd);                                    //Filesystem
DigitalOut sdWriteIndicator(LED2);                              //Led indicador de grabado

// Variables privadas

static char systemBuffer[SDCARD_LINES_TO_PRINT*SDCARD_LINE_SIZE];

//Implementación de funciones publicas

bool sdCardInit(){   
    //sdWriteIndicator = OFF;
    printToUSB("Iniciando tarjeta SD \r\n");
    fs.mount(&sd);
    DIR *dir = opendir("/sd/");
    if ( dir != NULL ) {
        printToUSB("Tarjeta SD encontrada!. \r\n");
        closedir(dir);
        return true;
    } else {
        printToUSB("Ocurrió un error con al tarjeta. \r\n");
        printToUSB("Inserte una tarjeta SD ");
        printToUSB("y reinicie el sistema.\r\n");
        return false;
    }
}

bool sdCardWriteFile( const char* fileName, const char* writeBuffer ){
    char fileNameSD[SD_CARD_FILENAME_MAX_LENGTH+4];
    
    fileNameSD[0] = '\0';
    strcat( fileNameSD, "/sd/" );
    strcat( fileNameSD, fileName );

    FILE *fd = fopen( fileNameSD, "a" );

    if ( fd != NULL ) {
        sdWriteIndicator = ON;
        fprintf( fd, "%s", writeBuffer );                       
        fclose( fd );
        delay(100);
        sdWriteIndicator = OFF;
        return true;
    } else {
        return false;
    }
}

bool sdCardEraseFile(const char* fileName){
    char fileNameSD[SD_CARD_FILENAME_MAX_LENGTH+4];
    fileNameSD[0] = '\0';
    strcat( fileNameSD, "/sd/" );
    strcat( fileNameSD, fileName );

    FILE *fd = fopen( fileNameSD, "w" );
    if ( fd != NULL ) {
        fclose( fd );
        return true;
    } else {
        return false;
    }
}

bool sdCardReadFile( const char* fileName, char * readBuffer, int readBufferSize ){
    char fileNameSD[SD_CARD_FILENAME_MAX_LENGTH+4];
    int i;
    
    fileNameSD[0] = '\0';
    strcat( fileNameSD, "/sd/" );
    strcat( fileNameSD, fileName );
    
    FILE *fd = fopen( fileNameSD, "r" );
    
    if ( fd != NULL ) {
        printToUSB( "Abriendo archivo: " );
        printToUSB( fileNameSD );
        printToUSB( "\r\n" );

        i = 0;
        while ( ( !feof(fd) ) && ( i < readBufferSize - 1 ) ) {
           fread( &readBuffer[i], 1, 1, fd );
           i++;
        }
        readBuffer[i-1] = '\0';
        fclose( fd );
        return true;
    } else {
        printToUSB( "No se encontro el archivo\r\n" );
        return false;
    }
}

void sdCardReadLastLogs(){
    sdWriteIndicator = ON;
    sdCardReadFile(FILE_NAME,systemBuffer,sizeof(systemBuffer));
    printToUSB( systemBuffer );
    sdWriteIndicator = OFF;
}

void sdCardWriteLog(float voltage, float current, float frequency, float phase){
    char fileName[SD_CARD_FILENAME_MAX_LENGTH]=FILE_NAME;
    char logLine[SDCARD_LINE_SIZE];
    char current_time[12]="";

    char str_voltage[6]="";
    char str_current[6]="";
    char str_frequency[5]="";
    char str_phase[5]="";

    floatToString(str_voltage,voltage,3,1);             //Convierte los valores de tensión en string con 3 dígtos y 1 decimal
    floatToString(str_current,current,1,2);             //Realiza lo mismo con la corriente, con 1 dígito y 3 decimales
    floatToString(str_frequency,frequency,2,2);          
    floatToString(str_phase,phase,1,3);

    RTCGetTime(current_time);

    sprintf(logLine,"%s: %s V, %s A, %s Hz, %s \n", current_time, str_voltage, str_current, str_frequency, str_phase);

    if ( !sdCardWriteFile( fileName,logLine ) ){
        printToUSB("Ocurrió un error inesperado\n");
    }
}