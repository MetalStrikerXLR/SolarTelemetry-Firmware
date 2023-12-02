#ifndef CORE_NETWORK_H
#define CORE_NETWORK_H

#include <WiFi.h>

void initWifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print("Trying to Connect to SSID --> ");
    Serial.println(ssid);
  }

  IPAddress selfIP = WiFi.localIP();

  Serial.print("SolarTelemetry Monitor available @ ");
  Serial.println(selfIP);
  WIFI_ACTIVE = true;
}

void manageNetwork()
{
  unsigned long currentMillis = millis();

  // if WiFi is down, try reconnecting every
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - wifiMonitorPrevMillis >= wifiMonitorUpdateInterval))
  {
    WIFI_ACTIVE = false;

    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);

    wifiMonitorPrevMillis = currentMillis;
  }

  if ((WIFI_ACTIVE == false) && (WiFi.status() == WL_CONNECTED))
  {
    Serial.print("Reconnected, Solar Monitor available @ ");
    Serial.println(WiFi.localIP());
    WIFI_ACTIVE = true;
  }
}

#endif
