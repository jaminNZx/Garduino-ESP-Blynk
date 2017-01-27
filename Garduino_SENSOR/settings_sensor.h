/**************************************************************
 *
 *                  Settings - Sensor
 *
 **************************************************************/
/*
    !!!IMPORTANT!!! Select which sensor this sketch is uploaded to!!
*/
#define SENSOR  1
//#define SENSOR  2
//#define SENSOR  3
/*
     Blynk Auth Codes
*/
#define AUTH_BASE               "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define AUTH_SENSOR1            "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define AUTH_SENSOR2            "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define AUTH_SENSOR3            "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
/*
   Wifi Credentials
*/
#define WIFI_SSID               "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_PASS               "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
/*
   Local Server Settings
*/
#define USE_LOCAL_SERVER       
#define SERVER                  IPAddress(192, 168, 1, 2)
/*
   Sensor Labels
*/
#define LABEL_SENSOR1           "VEGE GARDEN" 
#define LABEL_SENSOR2           "BACKYARD FENCE GARDEN"
#define LABEL_SENSOR3           "POT PLANTS"
/*
   Virtual Pins - Base
*/
#define vPIN_MOISTURE1          V1
#define vPIN_MOISTURE2          V2
#define vPIN_MOISTURE3          V3
/*
   Virtual Pins - Sensors
*/
#define vPIN_BASE_BRIDGE        V0
#define vPIN_BUTTON_NOSLEEP     V1
#define vPIN_SLEEP_LED          V2
#define vPIN_LABEL              V3
#define vPIN_MOISTURE           V4
/*
   DO NOT CHANGE ANYTHING BELOW
*/
#if   (SENSOR == 1)
  #define AUTH_SENSOR           AUTH_SENSOR1
  #define LABEL_SENSOR          LABEL_SENSOR1
  #define vPIN_MOISTURE_BASE    vPIN_MOISTURE1
  #define OTA_HOSTNAME          "GARDUINO-SENSOR-1"
#elif (SENSOR == 2)
  #define AUTH_SENSOR           AUTH_SENSOR2
  #define LABEL_SENSOR          LABEL_SENSOR2
  #define vPIN_MOISTURE_BASE    vPIN_MOISTURE2
  #define OTA_HOSTNAME          "GARDUINO-SENSOR-2"
#elif (SENSOR == 3)
  #define AUTH_SENSOR           AUTH_SENSOR3
  #define LABEL_SENSOR          LABEL_SENSOR3
  #define vPIN_MOISTURE_BASE    vPIN_MOISTURE3
  #define OTA_HOSTNAME          "GARDUINO-SENSOR-3"
#endif
/*
   
*/
