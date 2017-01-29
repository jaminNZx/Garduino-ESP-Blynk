/**************************************************************
 *
 *                  Settings - Sensor
 *
 **************************************************************/
/*
  !!!IMPORTANT!!! Select which sensor this sketch will act as!!
*/
#define SENSOR  1
//#define SENSOR  2
//#define SENSOR  3
/*
   Auth Codes & Wifi info go in the following file.
   Create a new folder in your library dir called 'private_credentials_garduino'
   and create a new file called 'private_credentials_garduino.h' and copy the 
   example in the repo.
*/
#include <wifi_credentials.h>
/*
     Blynk Auth Codes
*/
#define AUTH_BASE               "d8a785e101d74d5696a13c8fe597c981"
#define AUTH_SENSOR1            "6e17b587a36c4892911267bdcc7062ce"
#define AUTH_SENSOR2            "420ff5509d974a218ba945fea719d945"
#define AUTH_SENSOR3            "b6cf9b61c05f4a7aac99bc62b3109459"
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
