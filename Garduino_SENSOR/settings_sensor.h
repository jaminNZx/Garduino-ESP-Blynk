/**************************************************************

                           Settings

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

#if   (SENSOR == 1)
  #define AUTH_SENSOR           AUTH_SENSOR1
#elif (SENSOR == 2)
  #define AUTH_SENSOR           AUTH_SENSOR2
#elif (SENSOR == 3)
  #define AUTH_SENSOR           AUTH_SENSOR3
#endif
/*
   Wifi Credentials
*/
#define WIFI_SSID               "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_PASS               "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define OTA_HOSTNAME            "GARDUINO-SENSOR-" + SENSOR
/*
   Local Server Settings
*/
#define USE_LOCAL_SERVER       
#define SERVER                  IPAddress(192, 168, 1, 2)
/*
   Sensor Labels
*/
#define LABEL_SENSOR1           "VEGE GARDEN" 
#define LABEL_SENSOR2           "FENCE GARDEN"
#define LABEL_SENSOR3           "POTTED PLANTS"
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

*/
