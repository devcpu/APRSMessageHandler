/*
 * File: APRS_MSG.h
 * Project: src
 * File Created: 2020-11-11 20:13
 * Author: (DL7UXA) Johannes G.  Arlt (dl7uxa@arltus.de)
 * -----
 * Last Modified: 2021-10-20 0:29
 * Modified By: (DL7UXA) Johannes G.  Arlt (dl7uxa@arltus.de>)
 * -----
 * Copyright © 2019 - 2021 (DL7UXA) Johannes G.  Arlt
 * License: MIT License  http://www.opensource.org/licenses/MIT
 */

#include <Arduino.h>

#ifndef SRC_APRSMESSAGEHANDLER_H_
#define SRC_APRSMESSAGEHANDLER_H_

#define CONVERT_FEED_METER 3.28084
#define WX_DEVICE_STR_LENGHT 12
#define CALL_LENGHT 12 // @TODO needs check if it is in APRS OK

/*
 APRS Message Format
 Message:
 [sender-call]>[dest-call or software],[WIDE],
*/

/*
  symboltabelle steht zwischen lat und lng
  symbol steht nach dem
  enum aprs_symbol_table_e { primary = '/', alternate = '\\' };
*/



class APRS_MSG {
 public:


  APRS_MSG();
  APRS_MSG(String sender_call, String sender_call_ext, char aprs_symbol_table, char aprs_symbol);
  virtual ~APRS_MSG();

  String computeAPRSPos(double lat, double lng);
  String computeAPRSWXField(float temp, float pressure, float humidity, String sensor);
  String computeGPSMoveInfo(double speed, double course, double altitude);
  String computeTimestamp(double day, double hour, double minute);
  String computeMSG(String to, String msg);
  
  /**
 * @brief round and convert 100% humidity to APRS syle 00
 *
 * @param char* rv: return value
 * @param float humidity: humidity
 * @return char*
 */
  static String calcHumidity(float humidity);

  /**
   * @brief converts given miles/hour to km/h (imperial2metric)
   *
   * @param mph miles/hour
   * @return double_t km/h
   */
  static double_t mph2kmh(double_t mph);

  /**
   * @brief converts given km/h to miles/hour (metric2imperial)
   *
   * @param kmh km/h
   * @return double_t mph
   */
  static double_t kmh2mph(double_t kmh);

  /**
   * @brief converts hunderts of inch to mm (imperial2metric)
   *
   * @param hinch inch/100
   * @return double_t inch/100
   */
  static double_t hinch2mm(double_t hinch);

  /**
   * @brief converts mm to hunderts of inch (metric2imperial)
   *
   * @param mm mm
   * @return double_t inch/100
   */
  static double_t mm2hinch(double_t mm);

  /**
   * @brief converts temperature fahrendheit to Celsius (imperial2metric)
   *
   * @param temp °F
   * @return double_t °C
   */
  static double_t f2c(double_t temp);

  /**
   * @brief converts temperature Celsius to fahrendheit (metric2imperial)
   *
   * @param temp °C
   * @return double_t  °F
   */
  static double_t c2f(double_t temp);

  /**
   * @brief converts wgs data from dc (decimal) to APRS - gms
   * (grad,minutes,secundes), given from GPS Lib to APRS format
   *
   * keep in mind the format for APRS differs from normal.
   * 52.2904N in APRS will be 5229.04N!
   * there no negative for S or W, it will be show as W or S
   *
   * @param retvar _aprs_lng or _aprs_lat (char[10])
   * @param gpsdata lat or lng from GPS
   * @param lng must be true from lng, it sets fromat (xxxxx.xx for lng xxxx.xx
   * for lat and also E/W or N/S)
   *
   * @see https://www.gpskoordinaten.de/gps-koordinaten-konverter
   * @see
   * https://www.giga.de/extra/gps/tipps/gps-koordinaten-umrechnen-online-oder-mit-formel/
   */

  static String dc2gms(double gpsdata, boolean lng);

  static double_t feed2meter(double_t feed);
  static double_t meter2feed(double_t meter);

  

 private:
  String _sender_call;
  String _sender_call_ext;
  char _aprs_symbol_table;
  char _aprs_symbol;
  char _ARPSWXFiled[64] = {0};
  char _APRSMoveField[32] = {0};
  char _APRSPosField[64] = {0};
  char _APRSTimeStamp[16] = {0};


  // void computeWXField(void);
  // void computeGPSMoveInfo(void);
};

#endif // SRC_APRSMESSAGEHANDLER_H_
