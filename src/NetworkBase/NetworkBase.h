/**************************************************************************/
/*!
    @file     NetworkBase.h
    @author   Erika Gili & Davide di Domenico

    v1.0  - First release
*/
/**************************************************************************/
#ifndef NETWORKBASE_H
#define NETWORKBASE_H

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

class NetworkBase {
  
  public: 
    NetworkBase(char* hostname, boolean reset);
    
    void handleLoop(void);
    void setupWebServer();
  
  private:
    void configOTA();
    char *hostname;
  
};

#endif