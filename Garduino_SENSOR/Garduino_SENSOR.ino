/**************************************************************
 *
 *      Garduino - Sensor Sketch
 *      
 *      An Arduino Controlled Irrigation System using 
 *      Wifi connected moisture sensors and integrated
 *      with the Blynk Mobile App for input and control.
 *      
 *      Github: https://github.com/jaminNZx/Garduino-ESP-Blynk
 *
 *      Written by: Ben Selkirk (JaminNZx)
 *      
 *      Official Blynk Support Forum: Coming Soon
 *      
 **************************************************************/
//#define BLYNK_DEBUG
#define BLYNK_PRINT Serial

#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include "settings_sensor.h"

SimpleTimer timer;
WidgetBridge base(vPIN_BASE_BRIDGE);

bool noSleep;
int timer1, timer2;

void updateMoisture() {
  //int moistureSensor = analogRead(A0);
  int moistureSensor = random(1023);
  moistureSensor = map(moistureSensor, 0, 1023, 1, 100);
  Serial.print("SENSOR=");
  Serial.println(moistureSensor);
  Blynk.virtualWrite(vPIN_MOISTURE, moistureSensor ); // update dash page with data
  base.virtualWrite(vPIN_MOISTURE1, moistureSensor); // update BASE with data
}

BLYNK_WRITE(vPIN_BUTTON_NOSLEEP) {
  if (param.asInt()) {
    noSleep = 1;
  } else {
    noSleep = 0;
  }
}

BLYNK_CONNECTED() {
  base.setAuthToken(AUTH_BASE);
}

void checkNoSleep() {
  Blynk.syncVirtual(vPIN_BUTTON_NOSLEEP);
  if (!noSleep) {
    Blynk.virtualWrite(vPIN_SLEEP_LED, 255);
    timer.disable(timer1);
    Serial.println("SLEEPING");
    ESP.deepSleep(1000000 * 5); // sleep 60 sec
    delay(100);
  } else {
    Blynk.virtualWrite(vPIN_SLEEP_LED, 0);
    timer.enable(timer1);
  }
}

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  #if defined(USE_LOCAL_SERVER)
    Blynk.begin(AUTH_SENSOR, WIFI_SSID, WIFI_PASS, SERVER);
  #else
    Blynk.begin(AUTH_SENSOR, WIFI_SSID, WIFI_PASS);
  #endif
  while (Blynk.connect() == false) {}
  Blynk.syncVirtual(vPIN_BUTTON_NOSLEEP);
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.begin();
  Blynk.virtualWrite(vPIN_LABEL, LABEL_SENSOR1);
  Blynk.virtualWrite(vPIN_SLEEP_LED, 0);
  updateMoisture(); // read and send moisture data to dash and BASE
  timer1 = timer.setInterval(10000L, updateMoisture);
  timer2 = timer.setInterval(1000L, checkNoSleep);
}

void loop() {
  Blynk.run();
  ArduinoOTA.handle();
  timer.run();
}
