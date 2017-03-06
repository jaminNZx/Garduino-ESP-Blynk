/**************************************************************

        Garduino - Base Sketch

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
#include <SimpleTimer.h>
#include "settings_base.h"

SimpleTimer timer;
WidgetTerminal terminal(vPIN_TERMINAL);
int tap_timeout_value = 60000;
volatile byte pulseCount = 0;
float flowRate = 0.00, waterCost;
unsigned int flowMilliLitres = 0;
unsigned long totalMilliLitres = 0;
unsigned long oldTime = 0;
/*
   OUTPUT TO CONSOLE FUNCTION
*/
void printTask(String a, String b) {
#if defined(OUTPUT_SERIAL)
  Serial.print(a + String("="));
  Serial.println(b);
#endif
#if defined(OUTPUT_TERMINAL)
  terminal.print(a + String("="));
  terminal.println(b);
  terminal.flush();
#endif
}
/*
   TAP CONTROL
*/
void TAP_On() {
  totalMilliLitres = 0;
  digitalWrite(TAP, LOW);
  Blynk.virtualWrite(vPIN_TAP_LED, 255);
  printTask("TAP", "ON");
}
void TAP_Off() {
  digitalWrite(TAP, HIGH);
  Blynk.virtualWrite(vPIN_TAP_LED, 0);
  printTask("TAP", "OFF");
  printTask("WATER USED", String((float)totalMilliLitres / 1000));
}
void TAP_Toggle() {
  if (digitalRead(TAP)) {
    TAP_On();
  } else {
    TAP_Off();
  }
}
/*
   BLYNK WRITES
*/
BLYNK_WRITE(vPIN_TAP_TIMEOUT) {
  tap_timeout_value = param.asInt() * 60000;
  printTask("TAP TIMEOUT", String(tap_timeout_value / 1000) + String(" SEC"));
}

BLYNK_WRITE(vPIN_TAP_MANUAL) {
  if (param.asInt()) {
    TAP_Toggle();
  }
}
BLYNK_WRITE(vPIN_TAP_TIMER) {
  if (param.asInt()) {
    TAP_On();
    printTask("TAP TIMEOUT", String(tap_timeout_value / 1000) + String(" SEC"));
    timer.setTimeout(tap_timeout_value, TAP_Off);
  }
}
/*
   FLOW SENSOR FUNCTIONS
*/
void GetFlowSensorData() {
  detachInterrupt(FLOW_SENSOR);
  flowRate = pulseCount / FLOW_CALIBRATION;
  pulseCount = 0;
  attachInterrupt(FLOW_SENSOR, pulseCounter, FALLING);
  //calc totals
  flowMilliLitres = (flowRate / 60) * 1000;
  totalMilliLitres += flowMilliLitres;
}
void pulseCounter() {
  pulseCount++;
}
void ShowFlowSensorData() {
  Blynk.virtualWrite(vPIN_WATER_TOTAL, (float)totalMilliLitres / 1000);
  Blynk.virtualWrite(vPIN_WATER_FLOW,  (float)flowMilliLitres / 1000);
#ifdef WATER_PRICE
  waterCost = waterCost + (((float)flowMilliLitres / 1000) * WATER_PRICE);
  Blynk.virtualWrite(vPIN_WATER_COST, String(waterCost,6));
#endif
}
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
  oldTime           = 0;
  attachInterrupt(FLOW_SENSOR, pulseCounter, FALLING);
  // COMMUNICATIONS
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  // CONNECT TO BLYNK
#if defined(USE_LOCAL_SERVER)
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS, SERVER);
#else
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS);
#endif
  while (Blynk.connect() == false) {}
  // OVER THE AIR UPDATES
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.begin();
  // TIMERS
  timer.setInterval(1000L, GetFlowSensorData);
  timer.setInterval(500L, ShowFlowSensorData);
  // DONE
  Serial.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.flush();
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
