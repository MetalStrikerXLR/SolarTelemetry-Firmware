#include <Arduino.h>
#include "Global.h"
#include "CoreNetwork.h"
#include "CoreWebServer.h"
#include "CoreMQTT.h"
#include "CoreSolarTelemetry.h"
// #include "time.h"


// ******************************************  Setup  ******************************************
void setup()
{
  //Set up USB Serial Monitor
  Serial.begin(115200);
  while (!Serial);

  //Set up Telemetry Serial Connection
  Serial2.begin(2400, SERIAL_8N1);
  Serial2.setTimeout(10000);
  while (!Serial2);

  //Initialize ESP File System
  initFS();
  
  // Initialize Network
  initWifi();

  //Initialize WebSocket and Web Server
  initWebSocket();
  initServer();

  // rtc.setTime(1609459200);  // 1st Jan 2021 00:00:00
  // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
  // struct tm timeinfo;
  // if (getLocalTime(&timeinfo)){
  //   rtc.setTimeStruct(timeinfo); 
  // }

  delay(3000);
}

// ******************************************  Loop  ******************************************
void loop() {
  yield();

  inverter_send("QPIGS");

  if (Serial2.available())
  {
    stringOne = Serial2.readStringUntil('\r');

    // (NAK handle ???    // not accepted command message from inverter
    if (stringOne.substring(0, 3) != "(NAK" )
    {
      Serial.println (stringOne.substring(0, stringOne.length() - 2));
      QPIGS_val();
      QPIGS_print();
      delay(1000);
    }
  }
  stringOne = "";

  // Monitor and manage Network
  manageNetwork();

  // Manage Web Server Clients
  ws.cleanupClients();
}
