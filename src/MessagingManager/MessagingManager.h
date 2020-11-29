/**************************************************************************/
/*!
    @file     MessagingManager.h
    @author   Erika Gili & Davide di Domenico

    v1.0  - First release
*/
/**************************************************************************/
#ifndef MESSAGINGMANAGER_H
#define MESSAGINGMANAGER_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "../PayloadManager/PayloadManager.h"
#include "../DeviceConfiguration.h"

class MessagingManager
{

public:
    MessagingManager(PubSubClient *mqttClient,
                     DeviceDescription *deviceDescription,
                     ActionDescription actionsDescriptions[],
                     unsigned int numberOfAvailableActions);

    void initializeMQTTMessaging();
    //void generateCommandTopics();
    //void sendApplianceProvisioningMessage();
    //void sendTelemetryData(unsigned int featureIndex);

private:
    //int computeApplianceProvisioningPayloadSize();
    //void executeCommand(char *featureId, const char *command, const char *correlationId);
    void callback(char *topic, byte *payload, unsigned int length);

    char *feedbackTopic;
    unsigned int numberOfAvailableActions;
    PubSubClient *mqttClient;
    PayloadManager *payloadManager;
    DeviceDescription *deviceDescription;
    ActionDescription *actionsDescriptions;
};

#endif