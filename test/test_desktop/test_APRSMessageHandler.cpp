/*
 * File: test_APRSMessage.cpp
 * Project: test_desktop
 * File Created: 2021-10-18 21:33
 * Author: (DL7UXA) Johannes G.  Arlt (dl7uxa@arltus.de)
 * -----
 * Last Modified: 2021-10-20 2:28
 * Modified By: (DL7UXA) Johannes G.  Arlt (dl7uxa@arltus.de>)
 * -----
 * Copyright © 2021 - 2021 (DL7UXA) Johannes G.  Arlt
 * License: MIT License  http://www.opensource.org/licenses/MIT
 */

#include <APRSMessageHandler.h>
#include <unity.h>

void test_a_well_known_truth(void) { TEST_ASSERT_EQUAL(1, 1); }

// void test_simple_aprs_msg(void) {
//     APRSMessage amsg;
//     amsg.setSource(String("DL7UXA-3"));
//     amsg.setDestination(String("DL1BQF"));
//     assertEqual_STRING(amsg.encode().c_str(), String("Hallo Welt").c_str());
// }

// void test_decode_aprs_msg(void) {
//     String str = String("AB1CDE-10>APRS,AB1CDE:=1234.12N/12345.12E-QTH von
//     AB1CDE"); APRSMessage msg; msg.decode(str);
//     assertEqual_STRING(msg.getRawBody().c_str(), "Hallo Welt");

// }

// void test_decode_position(){
//   String test = String("5229.09N/01334.52E>286/251/A=999999");
//   APRSPosition ap;
//   ap.decode(test);
//   assertEqual_STRING("5229.09", ap.lat.c_str());
//   assertEqual_STRING("01334.52", ap.lng.c_str());
//   assertEqual_STRING(">", ap.symbol.c_str());
//   assertEqual_STRING("/", ap.table.c_str());
//   assertEqual_INT16(286, ap.course);
//   assertEqual_INT16(251, ap.speed);
//   assertEqual_INT16(999999, ap.altitude);
// }

// int process() {
//   UNITY_BEGIN();
//   // test_simple_aprs_msg();
//   // test_decode_aprs_msg();
//   test_decode_position();
//   UNITY_END();

//   return 0;
// }

#ifdef ARDUINO

#include <Arduino.h>
void setup() {
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(200);
  UNITY_BEGIN(); // IMPORTANT LINE!
  RUN_TEST(test_a_well_known_truth);
  delay(500);
}

void loop() { delay(500); }

#else

int main(int argc, char **argv) {
  test_a_well_known_truth();
  return 0;
}

#endif
