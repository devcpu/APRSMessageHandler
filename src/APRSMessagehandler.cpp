/*
 * File: APRS_MSG.cpp
 * Project: src
 * File Created: 2020-11-11 20:14
 * Author: (DL7UXA) Johannes G.  Arlt (dl7uxa@arltus.de)
 * -----
 * Last Modified: 2021-10-20 0:46
 * Modified By: (DL7UXA) Johannes G.  Arlt (dl7uxa@arltus.de>)
 * -----
 * Copyright © 2019 - 2021 (DL7UXA) Johannes G.  Arlt
 * License: MIT License  http://www.opensource.org/licenses/MIT
 */

#include <APRSMessageHandler.h>
#include <stdio.h>
#include <stdlib.h>

// ".../...g...t...r...p...P...h..b...."

String APRS_MSG::computeAPRSWXField(float temp, float pressure, float humidity, String sensor) {
  char buf[64] = {0};
  snprintf(buf, sizeof(buf) - 1, "%s/%sg%st%03dr%sp%sP%sh%sb%05d Sensor: %s",
           "...",                                           // winddirection 0-360
           "...",                                           // windspeed in mph
           "...",                                           // gust
           static_cast<int8_t>(round(APRS_MSG::c2f(temp))), // temperature
           "...",                                           // rainfalllasthourhinch
           "...",                                           // rainfalllast24hinch
           "...",                                           // rainfallsinceMidnightinch
           APRS_MSG::calcHumidity(humidity).c_str(),        // humidity
           static_cast<uint8_t>(round(pressure * 10)),      // pressure @FIXME / 100.00L * 10 ??
           sensor.c_str());                                 // wx sensor @FIXME sensor from i2c-scanner, not
                                                            // staticly
  return String(buf);
}

String APRS_MSG::calcHumidity(float humidity) {
  char buf[4] = {0};
  if (humidity == 100) {
    snprintf(buf, sizeof(buf) - 1, "%s", "00");
  } else {
    snprintf(buf, sizeof(buf) - 1, "%02u", static_cast<uint8_t>(round(humidity)));
  }
  return String(buf);
}

String APRS_MSG::computeAPRSPos(double lat, double lng) {
  char buf[64] = {0};
  char buf_lat[16] = {0};
  char buf_lng[16] = {0};
  snprintf(buf, sizeof(buf) - 1, "%s%c%s%c", dc2gms(lat, false).c_str(), _aprs_symbol_table, dc2gms(lng, true).c_str(),
           _aprs_symbol);
  return String(buf);
}

String APRS_MSG::computeGPSMoveInfo(double speed, double course, double altitude) {
  snprintf(_APRSMoveField, sizeof(_APRSMoveField) - 1, "%03.0f/%03.0f/A=%06.0f", speed, course, altitude);
  return String(_APRSMoveField);
}

String APRS_MSG::computeTimestamp(double day, double hour, double minute) {
  char buf[16] = {0};
  snprintf(buf, sizeof(buf) - 1, "%02d%02d%02dz", static_cast<uint8_t>(day), static_cast<uint8_t>(hour),
           static_cast<uint8_t>(minute));
  return String(buf);
}

String APRS_MSG::computeMSG(String to, String msg) {
  return _sender_call + String("-") + _sender_call_ext + String(">APRS:@") + String(_APRSTimeStamp) +
         String(_APRSPosField) + String(_APRSMoveField) + String(" ") + msg;
}

// char* APRS_MSG::getAPRSTxPos(char* retvar) {
//     computeAPRSPos();
//     snprintf(retvar, 254, "%s>APRS:!%s", _call, _aprs_pos);
//     //Serial.printf("APRS_MSG::getAPRSTxPos retvar '%s'\n", retvar);
//     return retvar;

// DL7UXA-1>APRS:!
//};

/***************************************************************************/
/**************************   static converters   **************************/
/***************************************************************************/
double_t APRS_MSG::feed2meter(double_t feed) { return round(feed / CONVERT_FEED_METER); }

double_t APRS_MSG::meter2feed(double_t meter) { return round(meter * CONVERT_FEED_METER); }

double_t APRS_MSG::mph2kmh(double_t mph) { return round(mph / 0.62137); }

double_t APRS_MSG::kmh2mph(double_t kmh) { return round(kmh * 0.62137); }

double_t APRS_MSG::hinch2mm(double_t hinch) { return round(hinch / 3.93701); }

double_t APRS_MSG::mm2hinch(double_t mm) { return round(mm * 3.93701); }

double_t APRS_MSG::f2c(double_t temp) { return round((temp - 32) * 5 / 9); }

double_t APRS_MSG::c2f(double_t temp) { return round(temp * 9 / 5 + 32); }

String APRS_MSG::dc2gms(double gpsdata, boolean lng) {
  char fstr[16] = {0};
  char buf[16] = {0};
  char ew;

  if (gpsdata < 0 && lng) {
    ew = 'W';
  }
  if (gpsdata >= 0 && lng) {
    ew = 'E';
  }
  if (gpsdata < 0 && !lng) {
    ew = 'S';
  }
  if (gpsdata >= 0 && !lng) {
    ew = 'N';
  }

  if (gpsdata < 0) {
    gpsdata = -gpsdata;
  }

  uint8_t grad = gpsdata;
  float tmp = gpsdata - grad;
  tmp = tmp * 60;
  uint8_t minute = tmp;
  tmp = tmp - minute;
  uint8_t second = tmp * 60;

  if (lng) {
    strncpy(fstr, "%03d%02d.%02d%c", sizeof(fstr) - 1);
  } else {
    strncpy(fstr, "%02d%02d.%02d%c", sizeof(fstr) - 1);
  }
  snprintf(buf, 15, // Flawfinder: ignore // NOLINT
           fstr, grad, minute, second, ew);

  return String(buf);
}
