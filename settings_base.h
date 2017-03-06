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
#define USE_LOCAL_SERVER
#define SERVER                    IPAddress(192, 168, 1, 2)
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
#define WATER_PRICE               0.00001444 // cents per L. Find it on your water bill.
/*
   Virtual Pins - Base
*/
#define vPIN_TAP_LED              V7
#define vPIN_TAP_TIMEOUT          V14
#define vPIN_TAP_MANUAL           V18
#define vPIN_TAP_TIMER            V19

#define vPIN_WATER_TOTAL          V25
#define vPIN_WATER_FLOW           V26
#define vPIN_WATER_COST           V28

#define vPIN_WATER_TAP            V27

#define vPIN_TERMINAL             V31
/*

*/

 
