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

#include "../PayloadManager/PayloadManager.h"
#include "DeviceConfiguration.h"

class SmartHubClient {

  public:
      SmartHubClient(String smartHubServer, PayloadManager *payloadManager);
      void makeProvisioningRequest(DeviceDescription *deviceDescription, ActionDescription *actionDescriptions, unsigned int numberOfActions);
     // void getProvisioningPayload(char *payload, ApplianceDescription applianceDescription, FeatureDescription featuresDescriptions[], unsigned int noOfFeatures);
     // void getTelemetryPayload(char *payload, ApplianceDescription applianceDescription, FeatureDescription featureDescription);
     // void getCommandResponsePayload(char *payload, const char *correlationId, bool success, float currentFeatureStatus);
  
  private:
    String smartHubServer;
    HTTPClient *httpClient;
    PayloadManager *payloadManager;
};

#endif
