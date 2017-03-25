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

SimpleTimer timer;
WidgetTerminal terminal(vPIN_TERMINAL);
WidgetRTC rtc;
int limitType, tap_limit_value, timer1, timer2, timer3, rowIndex = 0, month_old;
volatile byte pulseCount = 0;
float flowRate = 0.00, waterCost, waterCost_month;
float flowMilliLitres;
float totalMilliLitres, totalMilliLitres_month;
String extraZeroH, extraZeroM, extraZeroS;

/*
   GET DATE AND TIME
*/
String getCurrentTime() {
  extraZeroH = "";
  extraZeroM = "";
  extraZeroS = "";
  if (hour() < 10) {
    extraZeroH = '0';
  }
  if (minute() < 10) {
    extraZeroM = '0';
  }
  if (second() < 10) {
    extraZeroS = '0';
  }
  return String(extraZeroH + hour()) + ':' + extraZeroM + minute() + ':' + extraZeroS + second();
}
String getCurrentDate() {
  return String(day()) + '-' + monthShortStr(month()) + '-' + (year() - 2000);
}
String curDateTime() {
  return getCurrentDate() + String(" ") + getCurrentTime();
}
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
  waterCost = 0;
  digitalWrite(TAP, LOW);
  Blynk.virtualWrite(vPIN_TAP_LED, 255);
  switch (limitType) {
    case 1:
      printTask("TAP=ON  LIMIT", String(tap_limit_value / 1000) + String(" SEC"));
      timer.setTimeout(tap_limit_value, TAP_Off);
      break;
    case 2:
      printTask("TAP=ON  LIMIT", String(tap_limit_value) + String(" LTRS"));
      timer1 = timer.setInterval(50, tap_limit_value_waterchecker);
      break;
  }
}
void TAP_Off() {
  digitalWrite(TAP, HIGH);
  Blynk.virtualWrite(vPIN_TAP_LED, 128);
  printTask("TAP", "SHUTTING DOWN..");
  timer.setTimeout(6000, finish_TAP_shutdown);
}
void TAP_Toggle() {
  if (digitalRead(TAP)) {
    TAP_On();
  } else {
    TAP_Off();
  }
}
void finish_TAP_shutdown() {
  printTask("TAP", "OFF");
  printTask("USED", String((float)totalMilliLitres / 1000) + String("L  COST=$") + String(waterCost, 6));
  Blynk.virtualWrite(vPIN_TAP_LED, 0);
  Blynk.virtualWrite(vPIN_TABLE, "add", rowIndex, curDateTime(), String( (float)totalMilliLitres / 1000, 6) + String(" L"));
  rowIndex++;
  Blynk.virtualWrite(vPIN_TABLE, "add", rowIndex, " ", String("$") + String(waterCost, 6));
  rowIndex++;
}
/*
   BLYNK WRITES
*/
BLYNK_WRITE(vPIN_LIMITMENU) {
  switch (param.asInt()) {
    case 1:
      limitType = param.asInt();
      printTask("LIMITED BY", "TIME");
      Blynk.setProperty(vPIN_TAP_LIMIT, "label", "TIME: MINUTES");
      break;
    case 2:
      limitType = param.asInt();
      printTask("LIMITED BY", "WATER");
      Blynk.setProperty(vPIN_TAP_LIMIT, "label", "WATER: LITRES");
      break;
  }
  Blynk.syncVirtual(vPIN_TAP_LIMIT);
}

BLYNK_WRITE(vPIN_TAP_LIMIT) {
  switch (limitType) {
    case 1:
      tap_limit_value = param.asInt() * 60000;
      printTask("TAP LIMIT", String(tap_limit_value / 1000) + String(" SEC"));
      break;
    case 2:
      tap_limit_value = param.asInt() * 10;
      printTask("TAP LIMIT", String(tap_limit_value) + String(" LTRS"));
      break;
  }
}

BLYNK_WRITE(vPIN_TAP_MANUAL) {
  TAP_Toggle();
}

BLYNK_WRITE(vPIN_TAP_ACTIVATE) {
  if (param.asInt()) {
    if (digitalRead(TAP)) {
      TAP_On();
    } else {
      TAP_Off();
    }
  }
}

void tap_limit_value_waterchecker() {
  if (tap_limit_value <= (float)totalMilliLitres / 1000) {
    timer.disable(timer1);
    TAP_Off();
  }
}

/*
   FLOW SENSOR FUNCTIONS
*/
void pulseCounter() {
  pulseCount++;
}
void flowSensor() {
  detachInterrupt(FLOW_SENSOR);
  flowRate = pulseCount / FLOW_CALIBRATION;
  pulseCount = 0;
  attachInterrupt(FLOW_SENSOR, pulseCounter, FALLING);
  //calc totals
  flowMilliLitres = (flowRate / 60) * 1000;
  totalMilliLitres += flowMilliLitres;
  totalMilliLitres_month += flowMilliLitres;
  Blynk.virtualWrite(vPIN_WATER_TOTAL, (float)totalMilliLitres / 1000);
  Blynk.virtualWrite(vPIN_WATER_FLOW,  String((float)flowMilliLitres, 0));
  Blynk.virtualWrite(vPIN_WATER_TOTAL_MONTH, (float)totalMilliLitres_month / 1000);
  waterCost = waterCost + ( ( ( (float)flowMilliLitres / 1000 ) * WATER_PRICE ) / 100);
  Blynk.virtualWrite(vPIN_WATER_COST, String(waterCost, 6));
  waterCost_month = waterCost_month + ( ( ( (float)flowMilliLitres / 1000 ) * WATER_PRICE ) / 100);
  Blynk.virtualWrite(vPIN_WATER_COST_MONTH, String(waterCost_month, 6));
}

BLYNK_WRITE(vPIN_WATER_COST_MONTH) {
  waterCost_month = param.asFloat();
  printTask("SYNC WATER COST", String(waterCost_month, 6));
}

BLYNK_WRITE(vPIN_WATER_TOTAL_MONTH) {
  totalMilliLitres_month = param.asFloat() * 1000;
  printTask("SYNC WATER USE", String((float)totalMilliLitres_month / 1000));
}

BLYNK_WRITE(vPIN_LAST_MONTH) {
  month_old = param.asInt();
  printTask("SYNC MONTH", String(month_old));
}

void sendUptime() {
  Blynk.setProperty(vPIN_TERMINAL, "label", String("WIFI: ") + String(map(WiFi.RSSI(), -105, -40, 0, 100)) + String("% (") + WiFi.RSSI() + String("dB)") + String(" | ") + curDateTime() );
  if (month() != month_old && year() != 1970) {
    waterCost_month = 0;
    totalMilliLitres_month = 0;
    month_old = month();
    Blynk.virtualWrite(vPIN_LAST_MONTH, month());
    Blynk.virtualWrite(vPIN_TABLE, "add", rowIndex, "RESET MONTHLY DATA", " ");
    rowIndex++;
  }
}

void normalSync() {
  if (year() != 1970) {
    setSyncInterval(300);
    printTask("RTC SYNC", "5 MIN");
    timer.disable(timer2);
  }
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
  Blynk.virtualWrite(vPIN_TABLE, "clr");
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
