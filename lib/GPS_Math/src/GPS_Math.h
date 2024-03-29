#ifndef _GPS_MATH_H
#define _GPS_MATH_H

#include <math.h>
#include <ctype.h>

 //http://arduinodev.woofex.net/2013/02/06/adafruit_gps_forma/
double convertDegMinToDecDeg (float degMin) {
  double min = 0.0;
  double decDeg = 0.0;

  //get the minutes, fmod() requires double
  min = fmod((double)degMin, 100.0);

  //rebuild coordinates in decimal degrees
  degMin = (int) ( degMin / 100 );
  decDeg = degMin + ( min / 60 );

  return decDeg;
}

int crc8(String str) {
    int len = str.length();
    const char * buffer = str.c_str();

    int crc = 0;
    for(int i=0;i<len;i++) {
        crc ^= (buffer[i] & 0xff);
    }
    return crc;
}

#endif