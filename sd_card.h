//=====[#include guards - begin]===============================================

#ifndef _SD_CARD_H_
#define _SD_CARD_H_

//=====[Declaration of public defines]=========================================

#define SD_CARD_FILENAME_MAX_LENGTH 32      //Cantidad maxima de caracteres del nombre del archivo
#define FILE_NAME "log.txt"                 //Nombre del archivo 
#define SDCARD_LINE_SIZE 55                 //Tamaño de la linea del log
#define SDCARD_LINES_TO_PRINT 10            

//=====[Declaration of public data types]======================================


//=====[Declarations (prototypes) of public functions]=========================

bool sdCardInit();
void sdCardWriteLog(float, float, float, float);
bool sdCardWriteFile( const char* fileName, const char* writeBuffer );
bool sdCardReadFile( const char* fileName, char * readBuffer, int readBufferSize );
bool sdCardEraseFile(const char* fileName);


//=====[#include guards - end]=================================================

#endif // _SD_CARD_H_
