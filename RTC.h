#ifndef RTC_H
#define RTC_H


#include "mbed.h"


// -------------- Funciones publicas ---------------------

void RTCGetTime(char* RTCTime);

void RTCGetDate(char* RTCDate);

void RTCSetTimeAndDate(int year, int month, int day, int hour, int minute, int second );

#endif