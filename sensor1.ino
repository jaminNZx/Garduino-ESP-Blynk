//#define BLYNK_DEBUG
#define BLYNK_PRINT Serial

#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#define vPIN_BASE_BRIDGE V0

// vPINs for BASE (must be the same as defined on BASE)
#define vPIN_MOISTURE1 V1
#define vPIN_MOISTURE2 V2
#define vPIN_MOISTURE3 V3

// vPINs SENSORS
#define vPIN_BUTTON_NOSLEEP V1
#define vPIN_SLEEP_LED V2
#define vPIN_LABEL V3
#define vPIN_MOISTURE V4

SimpleTimer timer;
WidgetBridge base(vPIN_BASE_BRIDGE);

char auth[] = "xxxxxxxxxxxxxxxxx"; // SENSOR AUTH
char base_auth[] = "xxxxxxxxxxxxxxxxx"; // BASE AUTH
char ssid[] = "xxxxxxxxxxxxxxxxx";
char pass[] = "xxxxxxxxxxxxxxxxx";

bool noSleep;
int timer1, timer2;

void updateMoisture() {
  //int moistureSensor = analogRead(A0);
  int moistureSensor = random(1023);
  moistureSensor = map(moistureSensor, 0, 1023, 1, 100);
  Serial.print("Moisture=");
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
  base.setAuthToken(base_auth);
}

void checkNoSleep() {
  Blynk.syncVirtual(vPIN_BUTTON_NOSLEEP);
  if (!noSleep) {
    Blynk.virtualWrite(vPIN_SLEEP_LED, 255);
    timer.disable(timer1);
    Serial.println("Sleeping...");
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
  Blynk.begin(auth, ssid, pass);
  while (Blynk.connect() == false) {}
  Blynk.syncVirtual(vPIN_BUTTON_NOSLEEP);
  ArduinoOTA.setHostname("Garduino-Sensor1");
  ArduinoOTA.begin();
  Blynk.virtualWrite(vPIN_LABEL, "SENSOR 1 - VEGE GARDEN"); 
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
