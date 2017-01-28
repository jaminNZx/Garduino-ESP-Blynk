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
WidgetBridge sensor1(vPIN_SENS1_BRIDGE);
WidgetBridge sensor2(vPIN_SENS2_BRIDGE);
WidgetBridge sensor3(vPIN_SENS3_BRIDGE);
WidgetTerminal terminal(vPIN_TERMINAL);
/*
   BLYNK WRITES
*/
int tap1_threshold_value = 10, tap2_threshold_value = 10, tap3_threshold_value = 10;
int tap1_timeout_value = 60000,   tap2_timeout_value = 60000,   tap3_timeout_value = 60000;
int activeTAPs = 0;
int flowMilliLitresSplit, totalMilliLitres1, totalMilliLitres2, totalMilliLitres3, totalMilliLitres4;

volatile byte pulseCount = 0;
float flowRate = 0.00;
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
   BLYNK BRIDGE
*/
BLYNK_CONNECTED() {
  sensor1.setAuthToken(AUTH_SENSOR1);
  sensor2.setAuthToken(AUTH_SENSOR2);
  sensor3.setAuthToken(AUTH_SENSOR3);
}
/*
   TAP CONTROL
*/
void TAP1_On() {
  digitalWrite(TAP1, LOW);
  Blynk.virtualWrite(vPIN_TAP1_LED, 255);
  activeTAPs++;
  printTask("TAP1", "ON");
}
void TAP1_Off() {
  digitalWrite(TAP1, HIGH);
  Blynk.virtualWrite(vPIN_TAP1_LED, 0);
  activeTAPs--;
  printTask("TAP1", "OFF");
}
void TAP1_Toggle() {
  if (digitalRead(TAP1)) {
    TAP1_On();
  } else {
    TAP1_Off();
  }
}

void TAP2_On() {
  digitalWrite(TAP2, LOW);
  Blynk.virtualWrite(vPIN_TAP2_LED, 255);
  activeTAPs++;
  printTask("TAP2", "ON");
}
void TAP2_Off() {
  digitalWrite(TAP2, HIGH);
  Blynk.virtualWrite(vPIN_TAP2_LED, 0);
  activeTAPs--;
  printTask("TAP2", "OFF");
}
void TAP2_Toggle() {
  if (digitalRead(TAP2)) {
    TAP2_On();
  } else {
    TAP2_Off();
  }
}

void TAP3_On() {
  digitalWrite(TAP3, LOW);
  Blynk.virtualWrite(vPIN_TAP3_LED, 255);
  activeTAPs++;
  printTask("TAP3", "ON");
}
void TAP3_Off() {
  digitalWrite(TAP3, HIGH);
  Blynk.virtualWrite(vPIN_TAP3_LED, 0);
  activeTAPs--;
  printTask("TAP3", "OFF");
}
void TAP3_Toggle() {
  if (digitalRead(TAP3)) {
    TAP3_On();
  } else {
    TAP3_Off();
  }
}

void TAP4_On() {
  digitalWrite(TAP4, LOW);
  Blynk.virtualWrite(vPIN_TAP4_LED, 255);
  activeTAPs++;
  printTask("TAP4", "ON");
}
void TAP4_Off() {
  digitalWrite(TAP4, HIGH);
  Blynk.virtualWrite(vPIN_TAP4_LED, 0);
  activeTAPs--;
  printTask("TAP4", "OFF");
}
void TAP4_Toggle() {
  if (digitalRead(TAP4)) {
    TAP4_On();
  } else {
    TAP4_Off();
  }
}
/*
   BLYNK WRITES
*/
BLYNK_WRITE(vPIN_TAP1_THRESHOLD) {
  tap1_threshold_value = param.asInt();
  printTask("TAP1 THRESHOLD", String(tap1_threshold_value));
}
BLYNK_WRITE(vPIN_TAP2_THRESHOLD) {
  tap2_threshold_value = param.asInt();
  printTask("TAP2 THRESHOLD", String(tap2_threshold_value));
}
BLYNK_WRITE(vPIN_TAP3_THRESHOLD) {
  tap3_threshold_value = param.asInt();
  printTask("TAP3 THRESHOLD", String(tap3_threshold_value));
}

BLYNK_WRITE(vPIN_TAP1_TIMEOUT) {
  tap1_timeout_value = param.asInt() * 60000;
  printTask("TAP1 TIMEOUT", String(tap1_timeout_value / 1000));
}
BLYNK_WRITE(vPIN_TAP2_TIMEOUT) {
  tap2_timeout_value = param.asInt() * 60000;
  printTask("TAP2 TIMEOUT", String(tap2_timeout_value / 1000));
}
BLYNK_WRITE(vPIN_TAP3_TIMEOUT) {
  tap3_timeout_value = param.asInt() * 60000;
  printTask("TAP3 TIMEOUT", String(tap3_timeout_value / 1000));
}

BLYNK_WRITE(vPIN_TAP1_MANUAL) {
  if (param.asInt()) {
    TAP1_Toggle();
  }
}
BLYNK_WRITE(vPIN_TAP2_MANUAL) {
  if (param.asInt()) {
    TAP2_Toggle();
  }
}
BLYNK_WRITE(vPIN_TAP3_MANUAL) {
  if (param.asInt()) {
    TAP3_Toggle();
  }
}
BLYNK_WRITE(vPIN_TAP4_MANUAL) {
  if (param.asInt()) {
    TAP4_Toggle();
  }
}

BLYNK_WRITE(vPIN_MOISTURE1) {
  int moisture1 = param.asInt();
  printTask("SENSOR1", String(moisture1));

  if (moisture1 <= tap1_threshold_value && digitalRead(TAP1)) {
    TAP1_On();
    timer.setTimeout(tap1_timeout_value, TAP1_Off);
  }
}
BLYNK_WRITE(vPIN_MOISTURE2) {
  int moisture2 = param.asInt();
  printTask("SENSOR2", String(moisture2));

  if (moisture2 <= tap2_threshold_value && digitalRead(TAP2)) {
    TAP2_On();
    timer.setTimeout(tap2_timeout_value, TAP2_Off);
  }
}
BLYNK_WRITE(vPIN_MOISTURE3) {
  int moisture3 = param.asInt();
  printTask("SENSOR3", String(moisture3));

  if (moisture3 <= tap3_threshold_value && digitalRead(TAP3)) {
    TAP3_On();
    timer.setTimeout(tap3_timeout_value, TAP3_Off);
  }
}
/*
   TERMINAL I/O
*/
BLYNK_WRITE(vPIN_TERMINAL) {
  if (String("sync tap1") == param.asStr()) {
    terminal.println("SYNCING TAP1");
    Blynk.syncVirtual(vPIN_TAP1_THRESHOLD, vPIN_TAP1_TIMEOUT);
  } else if (String("sync tap2") == param.asStr()) {
    terminal.println("SYNCING TAP2");
    Blynk.syncVirtual(vPIN_TAP2_THRESHOLD, vPIN_TAP2_TIMEOUT);
  } else if (String("sync tap3") == param.asStr()) {
    terminal.println("SYNCING TAP3");
    Blynk.syncVirtual(vPIN_TAP3_THRESHOLD, vPIN_TAP3_TIMEOUT);
  } else if (String("sync water") == param.asStr()) {
    terminal.println("SYNCING WATER");
    Blynk.syncVirtual(vPIN_WATER_TOTAL);
    ShowFlowSensorData();
  } else if (String("reset water") == param.asStr()) {
    terminal.println("RESETTING WATER TOTALS");
    totalMilliLitres = 0;
    ShowFlowSensorData();
  } else {
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }
  terminal.flush();
}
/*
   FLOW SENSOR FUNCTIONS
*/
void GetFlowSensorData() {

  detachInterrupt(FLOW_SENSOR);
  //flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / FLOW_CALIBRATION;
  //oldTime = millis();
  flowRate = pulseCount / FLOW_CALIBRATION;
  pulseCount = 0;
  attachInterrupt(FLOW_SENSOR, pulseCounter, FALLING);
  //calc totals
  flowMilliLitres = (flowRate / 60) * 1000;
  totalMilliLitres += flowMilliLitres;
  Blynk.virtualWrite(vPIN_WATER_TOTAL, (float)totalMilliLitres / 1000);
  Blynk.virtualWrite(vPIN_WATER_FLOW,  (float)flowMilliLitres / 1000);
  if (activeTAPs > 0) {
    flowMilliLitresSplit = flowMilliLitres / activeTAPs;
    if (!digitalRead(TAP1)) {
      totalMilliLitres1 += flowMilliLitresSplit;
      Blynk.virtualWrite(vPIN_WATER_TAP1, (float)totalMilliLitres1 / 1000);
    }
    if (!digitalRead(TAP2)) {
      totalMilliLitres2 += flowMilliLitresSplit;
      Blynk.virtualWrite(vPIN_WATER_TAP2, (float)totalMilliLitres2 / 1000);
    }
    if (!digitalRead(TAP3)) {
      totalMilliLitres3 += flowMilliLitresSplit;
      Blynk.virtualWrite(vPIN_WATER_TAP3, (float)totalMilliLitres3 / 1000);
    }
    if (!digitalRead(TAP4)) {
      totalMilliLitres4 += flowMilliLitresSplit;
      Blynk.virtualWrite(vPIN_WATER_TAP4, (float)totalMilliLitres4 / 1000);
    }
  }

  // old function
  //unsigned int frac;
  //frac = (flowRate - int(flowRate)) * 10;
  //Blynk.virtualWrite(29, frac);
}
void pulseCounter() {
  pulseCount++;
}
void ShowFlowSensorData() {
  printTask("WATER LITRES", String((float)totalMilliLitres / 1000));
}
/*
   SETUP
*/
void setup() {
  // PINMODES
  pinMode(TAP1, OUTPUT);
  pinMode(TAP2, OUTPUT);
  pinMode(TAP3, OUTPUT);
  pinMode(TAP4, OUTPUT);
  // SET RELAYS OFF
  digitalWrite(TAP1, HIGH);
  digitalWrite(TAP2, HIGH);
  digitalWrite(TAP3, HIGH);
  digitalWrite(TAP4, HIGH);
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
  Blynk.begin(AUTH_BASE, WIFI_SSID, WIFI_PASS, SERVER);
#else
  Blynk.begin(AUTH_BASE, WIFI_SSID, WIFI_PASS);
#endif
  while (Blynk.connect() == false) {}
  // OVER THE AIR UPDATES
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.begin();
  // TIMERS
  timer.setInterval(1000L, GetFlowSensorData);
  timer.setInterval(30000L, ShowFlowSensorData);
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
