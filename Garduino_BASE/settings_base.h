/**************************************************************
 *
 *                  Settings - Base
 *
 **************************************************************/
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
   Over The Air Hostname
*/
#define OTA_HOSTNAME            "GARDUINO-BASE"
/*
   Local Server Settings (uncomment to use local server)
*/
#define USE_LOCAL_SERVER
#define SERVER                  IPAddress(192, 168, 1, 2)
/*
   Console Output (Debug/Log)
*/
#define OUTPUT_SERIAL
#define OUTPUT_TERMINAL
/*
   Hardware Pins
*/
#define TAP1                    14 // D5
#define TAP2                    12 // D6
#define TAP3                    13 // D7
#define TAP4                    2  // D4
/*
   Flow Meter Pin and Calibration factor
*/
#define FLOW_SENSOR             4  // D2
#define FLOW_CALIBRATION        4.5
/*
   Virtual Pins - Base
*/
#define vPIN_MOISTURE1          V1
#define vPIN_MOISTURE2          V2
#define vPIN_MOISTURE3          V3

#define vPIN_SENS1_BRIDGE       V4
#define vPIN_SENS2_BRIDGE       V5
#define vPIN_SENS3_BRIDGE       V6

#define vPIN_TAP1_LED           V7
#define vPIN_TAP2_LED           V8
#define vPIN_TAP3_LED           V9
#define vPIN_TAP4_LED           V10

#define vPIN_TAP1_THRESHOLD     V11
#define vPIN_TAP2_THRESHOLD     V12
#define vPIN_TAP3_THRESHOLD     V13

#define vPIN_TAP1_TIMEOUT       V14
#define vPIN_TAP2_TIMEOUT       V15
#define vPIN_TAP3_TIMEOUT       V16

#define vPIN_TAP1_MANUAL        V18
#define vPIN_TAP2_MANUAL        V19
#define vPIN_TAP3_MANUAL        V20
#define vPIN_TAP4_MANUAL        V21

#define vPIN_WATER_TOTAL        V25
#define vPIN_WATER_FLOW         V26

#define vPIN_WATER_TAP1         V27
#define vPIN_WATER_TAP2         V28
#define vPIN_WATER_TAP3         V29
#define vPIN_WATER_TAP4         V30


#define vPIN_TERMINAL           V31
/*

*/


