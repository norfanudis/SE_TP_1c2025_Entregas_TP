#include "mbed.h"

#include "RTC.h"


//Implementación de funciones publicas

void RTCGetTime(char* RTCTime){
    time_t epochSeconds = time(NULL);                   //Toma el tiempo del sistema
    struct tm *rtc_info = localtime(&epochSeconds);     //Lo transforma en un struct rm
    if(rtc_info!=NULL){                                 //Si devuelve un valor correcto, toma la informacion de hora, minutos y segundos 
        sprintf(RTCTime,"%02i:%02i:%02i", rtc_info->tm_hour, rtc_info->tm_min,rtc_info->tm_sec);    //y lo formatea en un string
    }
}




void RTCSetTime( int year, int month, int day, int hour, int minute, int second ){
    struct tm rtcTime;

    rtcTime.tm_year = year - 1900;                      //Toma cada valor que se le envia a la funcion 
    rtcTime.tm_mon  = month - 1;                        //Y lo carga en la estructura tm
    rtcTime.tm_mday = day;
    rtcTime.tm_hour = hour;
    rtcTime.tm_min  = minute;
    rtcTime.tm_sec  = second;

    rtcTime.tm_isdst = -1;

    set_time( mktime( &rtcTime ) );                     //Finalmente lo carga en el sistema
}