#ifndef GLOBAL_H
#define GLOBAL_H

// #include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// #include <ESP32Time.h>
// #include <Arduino_JSON.h>


//-----------Define Wifi STA Settings---------------------------//
const char* ssid = "Basement";
const char* password = "4K@60Fps!";
bool WIFI_ACTIVE = false;

//-----------Define Web Server Settings---------------------//
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

//-----------Define Configuration Object--------------------//
// JSONVar configuration;

//-----------Define Firebase Settings---------------------//
// String API_KEY = "AIzaSyAHGBRwSC2iqkvoLZlx_fdFcJfG68t0H-4";
// String DATABASE_URL = "https://solarrtdb-default-rtdb.asia-southeast1.firebasedatabase.app/";
// bool signupOK = false;

//-----------Define NTP Client Settings---------------------//
// ESP32Time rtc;
// const char* ntpServer1 = "pool.ntp.org";
// const char* ntpServer2 = "time.nist.gov";
// const long  gmtOffset_sec = 18000;
// const int   daylightOffset_sec = 0;
// bool TIME_TRIGGER = false;

//-----------Define Non BLocking Timers---------------------//
// unsigned long timeClientPrevMillis = 0;
// const long timeClientUpdateInterval = 1000;

unsigned long wifiMonitorPrevMillis = 0;
unsigned long wifiMonitorUpdateInterval = 30000;

#endif
