/**************************************************************

        Garduino

        An Arduino Controlled Irrigation System using
        Wifi connected moisture sensors and integrated
        with the Blynk Mobile App for input and control.

        Github: https://github.com/jaminNZx/Garduino-ESP-Blynk

        Written by: Ben Selkirk (JaminNZx)

        Official Blynk Support Forum: Coming Soon

 **************************************************************/

//#define BLYNK_DEBUG
#define BLYNK_PRINT Serial

#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <SimpleTimer.h>
#include "settings_base.h"

#include "globals.h"
#include "functions.h"
#include "tapControl.h"
#include "blynk_writes.h"


/*
   SETUP
*/
void setup() {
  // PINMODES
  pinMode(TAP, OUTPUT);
  digitalWrite(TAP, HIGH);
  // FLOW METER
  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  attachInterrupt(FLOW_SENSOR, pulseCounter, FALLING);
  // COMMUNICATIONS
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  // CONNECT TO BLYNK
#ifdef LOCAL_SERVER
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS, LOCAL_SERVER);
#else
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS);
#endif
  while (Blynk.connect() == false) {}
  Blynk.syncVirtual(vPIN_LIMITMENU, vPIN_WATER_COST_MONTH, vPIN_WATER_TOTAL_MONTH, vPIN_LAST_MONTH);
  // OVER THE AIR UPDATES
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.begin();
  // RTC
  rtc.begin();
  setSyncInterval(5);
  // TIMERS
  timer.setInterval(1000, flowSensor);
  timer.setInterval(1000, sendUptime);
  timer2 = timer.setInterval(1000, normalSync);
  // DONE
  Serial.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.flush();
  //Blynk.virtualWrite(vPIN_TABLE, "clr");
}
/*
   LOOP
*/
void loop() {
  Blynk.run();
  ArduinoOTA.handle();
  timer.run();
}
/*

*/
