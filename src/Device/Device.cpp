#include <ESP8266WiFi.h>

#include "Device.h"

Device::Device(NetworkConfiguration *networkConfiguration, DeviceDescription *deviceDescription)
{
    this->payloadManager = new PayloadManager();
    this->deviceDescription = deviceDescription;

    Serial.println("Intialize MQTT client");
    this->networkConfiguration = networkConfiguration;
    this->mqttClient = new PubSubClient(this->espClient);

    Serial.println("Setting up MQTT host");
    this->mqttClient->setServer(networkConfiguration->mqttHost, networkConfiguration->mqttBrokerPort);
    this->mqttClient->setBufferSize(4096);

    Serial.println("Setting MQTT callback");
    this->mqttClient->setCallback([&](char *topic, byte *payload, unsigned int length) {
        callback(topic, payload, length);
    });
}

void Device::sendDeviceProvisioningPayload()
{
    Serial.println("Preparing and sending provisioning message");
    char provisioningPayload[800];
    this->payloadManager->getProvisioningPayload(provisioningPayload, this->deviceDescription);
    this->makeProvisioningRequest(provisioningPayload);
}

void Device::turnOnOutlet(ActionDescription *actionDescription)
{
    Serial.println("Should turn on the outlet");
    digitalWrite(11, 1);
}

void Device::turnOffOutlet(ActionDescription *actionDescription)
{
    Serial.println("Should turn off the outlet");
    digitalWrite(11, 0);
}

void Device::mqttClientLoop()
{
    if (!this->mqttClient->connected())
    {
        Serial.println("No MQTT connection, reconnecting");
        this->connectMqtt();
    }
    else
    {
        this->mqttClient->loop();
    }
}

void Device::connectMqtt()
{
    Serial.print("Connecting to MQTT with ClientId ");
    Serial.println(networkConfiguration->hostName);
    bool connected = this->mqttClient->connect(networkConfiguration->hostName, networkConfiguration->mqttBrokerUser, networkConfiguration->mqttBrokerPassword);
    if (connected)
    {
        Serial.println("Connected to mqtt");
        this->networkConfiguration->networkStatus = (char *)CONNECTED_MQTT;
        Serial.println("Subscribing to feedback topic");
        this->mqttClient->subscribe(deviceDescription->feedbackTopic);
        this->sendDeviceProvisioningPayload();
    }
    else
    {
        this->networkConfiguration->networkStatus = (char *)CONNECTING_WIFI;
        Serial.print("Failed with state ");
        Serial.println(this->mqttClient->state());
        delay(2000);
    }
}

void Device::callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    Serial.print("Message:");
    for (unsigned int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }

    Serial.println();
    Serial.println("-----------------------");
}

void Device::makeProvisioningRequest(char *deviceProvisioningPayload)
{
    Serial.println("Publishing device provisioning");
    bool published = this->mqttClient->publish("devices/provisioning", deviceProvisioningPayload);
    Serial.print("Published: ");
    Serial.println(published);
    if (!published)
    {
        this->networkConfiguration->networkStatus = (char *)NO_WIFI_CONNECTION;
    }
}
