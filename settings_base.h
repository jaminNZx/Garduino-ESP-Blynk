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
#define AUTH                      "0913ee2009cd4fa9b5307e572a0c5028"
/*
   Over The Air Hostname
*/
#define OTA_HOSTNAME              "GARDUINO-BASE"
/*
   Local Server Settings (uncomment to use local server)
*/
#define LOCAL_SERVER              IPAddress(192, 168, 1, 2)
/*
   Console Output (Debug/Log)
*/
//#define OUTPUT_SERIAL
#define OUTPUT_TERMINAL
/*
   Hardware Pins
*/
#define TAP                       14 // D5
/*
   Flow Meter Pin and Calibration factor
*/
#define FLOW_SENSOR               4  // D2
#define FLOW_CALIBRATION          4.5
/*
   Water Cost. Comment out to disable.
*/
#define WATER_PRICE               0.1444 // c/l -- Find it on your water bill. $1.444 /Kl = $0.001444 /l === 0.1444 c/l !
/*
   Virtual Pins - Base
*/
#define vPIN_TABLE                V1

#define vPIN_TAP_LED              V7
#define vPIN_TAP_LIMIT            V14
#define vPIN_TAP_MANUAL           V18
#define vPIN_TAP_ACTIVATE         V19

#define vPIN_WATER_TOTAL          V25
#define vPIN_WATER_TOTAL_MONTH    V21
#define vPIN_WATER_FLOW           V26
#define vPIN_WATER_COST           V28
#define vPIN_WATER_COST_MONTH     V11

#define vPIN_WATER_TAP            V27

#define vPIN_TERMINAL             V31

#define vPIN_LIMITMENU            V9

#define vPIN_LAST_MONTH           V10
/*

*/

 
