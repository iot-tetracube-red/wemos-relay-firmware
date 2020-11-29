/**************************************************************************/
/*!
    @file     MessagingManager.cpp
    @author   Erika Gili & Davide di Domenico

    v1.0 - First release
*/
/**************************************************************************/
#include "MessagingManager.h"

MessagingManager::MessagingManager(PubSubClient *mqttClient,
                                   DeviceDescription *deviceDescription,
                                   ActionDescription actionsDescriptions[],
                                   unsigned int numberOfAvailableActions)
{
    this->mqttClient = mqttClient;
    this->numberOfAvailableActions = numberOfAvailableActions;
    this->deviceDescription = deviceDescription;
    this->actionsDescriptions = actionsDescriptions;

    this->mqttClient->setCallback([&](char *topic, byte *payload, unsigned int length) {
        return this->callback(topic, payload, length);
    });
    /* this->noOfFeatures = noOfFeatures;
  this->applianceDescription = applianceDescription;
  this->featuresDescriptions = featuresDescriptions;
  this->payloadManager = new PayloadManager();
  this->mqttClient->setCallback([&](char *topic, byte *payload, unsigned int length) {
    return this->callback(topic, payload, length);
  });*/
}

void MessagingManager::initializeMQTTMessaging()
{
    Serial.println("Getting device provisioning message");
    char payload[500];
    this->payloadManager->getProvisioningPayload(payload, this->deviceDescription, this->actionsDescriptions, numberOfAvailableActions);
    Serial.print("Publishing provisioning message: ");
    Serial.println(payload);

    mqttClient->publish((char *)"device/provisioning", payload);

    Serial.println("Subscribing to actions topics");
    for (unsigned int i = 0; i < this->numberOfAvailableActions; i++)
    {
        char p[this->actionsDescriptions[i].topic.length() + 1];
        strcpy(p, this->actionsDescriptions[i].topic.c_str());
        bool subscribed = this->mqttClient->subscribe(p);
        Serial.print("Subscribed: ");
        Serial.println(subscribed);
    }
}

void MessagingManager::callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived in topic [");
    Serial.print(topic);
    Serial.print("]");
    Serial.println();

    char *body = (char *)payload;
    Serial.print("With message ");
    Serial.println(body);

    /* StaticJsonDocument<500> jsonDocument;
    DeserializationError deserializationError = deserializeJson(jsonDocument, body);
    if (deserializationError)
    {
        Serial.println("Cannot deserialize json");
        return;
    }

    const char *command = jsonDocument["command"];
    const char *correlationId = jsonDocument["correlationId"];*/
    //this->executeCommand(topic, command, correlationId);
}