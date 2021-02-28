/**************************************************************************/
/*!
    @file     PayloadManager.h
    @author   Erika Gili & Davide di Domenico

    v1.0  - First release
*/
/**************************************************************************/
#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

#include "../PayloadManager/PayloadManager.h"
#include "DeviceConfiguration.h"

class Device
{

public:
  Device(NetworkConfiguration *networkConfiguration, DeviceDescription *deviceDescription);
  void mqttClientLoop();
  void makeProvisioningRequest(char *deviceProvisioninPayload);
  // void getProvisioningPayload(char *payload, ApplianceDescription applianceDescription, FeatureDescription featuresDescriptions[], unsigned int noOfFeatures);
  // void getTelemetryPayload(char *payload, ApplianceDescription applianceDescription, FeatureDescription featureDescription);
  // void getCommandResponsePayload(char *payload, const char *correlationId, bool success, float currentFeatureStatus);

private:
  WiFiClient espClient;
  PubSubClient *mqttClient;
  NetworkConfiguration *networkConfiguration;
  DeviceDescription *deviceDescription;
  PayloadManager *payloadManager;

  void connectMqtt();
  void callback(char *topic, byte *payload, unsigned int length);
  void sendDeviceProvisioningPayload();

  void turnOnOutlet(ActionDescription *actionDescription);
  void turnOffOutlet(ActionDescription *actionDescription);
};

#endif