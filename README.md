# Garduino-ESP-Blynk
A wireless (solar poweed) sensor controlled garden irrigation system.

This is still a work in progress. I'll write up a readme later on but feel free to pick it up and try it out. 

Hardware: 

* 5V 4-way relay board (LOW active)
* ESP8266 (WeMos/NodeMCU style)
* Liquid Flow meter (just the basic type)
* 12VDC Solenoid water valves

Software:

* Load up the INO sketches and match the pinouts from the code. 
* Download the Blynk mobile app and create a project, add your base and 3 sensors as devices and email yourself the auth codes and put them in the sketchs.
* Create a new folder in your library dir called 'wifi_credentials' and create a new file called 'wifi_credentials.h' and copy the example below:

```cpp
/**************************************************************
 *           Settings - Wifi Credentials
 **************************************************************/

/*
   Wifi Credentials
*/
#define WIFI_SSID               "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_PASS               "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
```

Gallery:

![Garduino Hardware Photos](http://community.blynk.cc/uploads/default/original/2X/c/c79fb86800d6eb1a4f1ece925e627c7784e115f3.jpg)
![Garduino Hardware Photos](http://community.blynk.cc/uploads/default/original/2X/a/a61e43ef0505f88af899689d2f9f1c8d6a1409af.jpg)
![Garduino Hardware Photos](http://community.blynk.cc/uploads/default/original/2X/2/29079ce2982ebcda917d74fa72503f8df075900e.JPG)
![Garduino Hardware Photos](http://community.blynk.cc/uploads/default/original/2X/6/69f62f34ed21964702e4e03e3a36e9dc05da3f79.JPG)
![Garduino Hardware Photos](http://community.blynk.cc/uploads/default/original/2X/5/5627ae738fb28d322260eff2d59e155107be2b30.JPG)
