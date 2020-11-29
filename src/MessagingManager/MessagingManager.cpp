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

    char circuitIdChar[this->deviceDescription->circuitId.length() + 1];
    this->deviceDescription->circuitId.toCharArray(circuitIdChar, this->deviceDescription->circuitId.length() + 1);
    this->feedbackTopic = new char[60];
    strcpy(feedbackTopic, (char *)"device/feedback/");
    strcat(feedbackTopic, circuitIdChar);
    strcat(feedbackTopic, (char *)"\0");

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
    Serial.println("Subscribing to actions topics");
    for (unsigned int i = 0; i < this->numberOfAvailableActions; i++)
    {
        char actionTopicChar[this->actionsDescriptions[i].topic.length() + 1];
        this->actionsDescriptions[i].topic.toCharArray(actionTopicChar, this->actionsDescriptions[i].topic.length());
        bool subscribed = this->mqttClient->subscribe(actionTopicChar);
        Serial.println(subscribed);
    }
    Serial.println("Subscribing to feedback topic");
    this->mqttClient->subscribe(this->feedbackTopic);

    Serial.println("Getting device provisioning message");
    char payload[500];
    this->payloadManager->getProvisioningPayload(payload, this->deviceDescription, this->actionsDescriptions, numberOfAvailableActions);
    Serial.print("Publishing provisioning message: ");
    Serial.println(payload);

    mqttClient->publish((char *)"device/provisioning", payload);
}

void MessagingManager::callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived in topic [");
    Serial.print(topic);
    Serial.print("]");
    Serial.println();

    char body[length + 1];
    for (int i = 0; i < length; i++)
    {
        body[i] = ((char *)payload)[i];
    }
    strcat(body, (char *)"\0");
    Serial.print("With message ");
    Serial.println(body);

    if (strcmp(this->feedbackTopic, topic) == 0)
    {
        if (strcmp(body, "1") == 0)
        {
            Serial.println("Operation success");
        }
        else
        {
            Serial.print("Operation error");
        }
    }

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