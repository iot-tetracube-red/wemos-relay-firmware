/**************************************************************************/
/*!
    @file     PayloadManager.h
    @author   Erika Gili & Davide di Domenico

    v1.0  - First release
*/
/**************************************************************************/
#ifndef PAYLOADMANAGER_H
#define PAYLOADMANAGER_H

#include <cstring>
#include <Arduino.h>
#include <ArduinoJson.h>

#include "DeviceConfiguration.h"

class PayloadManager
{

public:
  PayloadManager();

  void getCommandResponsePayload(char *payload, ActionDescription *actionDescription);
  void getProvisioningPayload(char *payload,
                              DeviceDescription *deviceDescription,
                              ActionDescription actionDescriptions[],
                              unsigned int numberOfActions);
  // void getTelemetryPayload(char *payload, ApplianceDescription applianceDescription, FeatureDescription featureDescription);
  // void getCommandResponsePayload(char *payload, const char *correlationId, bool success, float currentFeatureStatus);

private:
};

#endif
