/**************************************************************************/
/*!
    @file     PayloadManager.h
    @author   Erika Gili & Davide di Domenico

    v1.0  - First release
*/
/**************************************************************************/
#ifndef SMARTHUBCLIENT_H
#define SMARTHUBCLIENT_H

#include <Arduino.h>
#include <ESP8266HTTPClient.h> 

#include "DeviceConfiguration.h"

class SmartHubClient {

  public:
      SmartHubClient();
      
     // void getProvisioningPayload(char *payload, ApplianceDescription applianceDescription, FeatureDescription featuresDescriptions[], unsigned int noOfFeatures);
     // void getTelemetryPayload(char *payload, ApplianceDescription applianceDescription, FeatureDescription featureDescription);
     // void getCommandResponsePayload(char *payload, const char *correlationId, bool success, float currentFeatureStatus);
  
  private:
    HTTPClient *httpClient;
};

#endif
