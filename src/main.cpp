#include <Arduino.h>

#include "NetworkBase/NetworkBase.h"
#include "config.h"
#include "DeviceConfiguration.h"
#include "Device/Device.h"
#include "StatusManager/StatusManager.h"

// Global objects
NetworkConfiguration networkConfiguration;
DeviceDescription deviceDescription;
NetworkBase *network;
Device *device;
StatusManager *statusManager;

void configureDevice()
{
    networkConfiguration.hostName = (char *)"multimedia-outlet-relay";
    networkConfiguration.mqttHost = (char *)MQTT_HOST;
    networkConfiguration.mqttBrokerPort = MQTT_PORT;
    networkConfiguration.mqttBrokerUser = (char *)MQTT_USER;
    networkConfiguration.mqttBrokerPassword = (char *)MQTT_PASSWORD;
    networkConfiguration.smartHubServer = (char *)SMART_HUB_HOST;
    networkConfiguration.networkStatus = (char *)NO_WIFI_CONNECTION;

    deviceDescription.id = "22cbfa35-142d-4e17-a579-66aa7f8cad00";
    deviceDescription.name = "multimedia outlet relay";
    deviceDescription.feedbackTopic = (char *)"devices/feedback/22cbfa35-142d-4e17-a579-66aa7f8cad00";
    deviceDescription.numberOfFeatures = 1;
    deviceDescription.features = new FeatureDescription[deviceDescription.numberOfFeatures];

    FeatureDescription relayFeature;
    relayFeature.id = "3253f251-3ab3-4987-8cdf-aa686de2b52b";
    relayFeature.featureType = "SWITCH";
    relayFeature.name = "Relay Switch";
    relayFeature.value = 0.0;
    relayFeature.numberOfActions = 2;
    relayFeature.actions = new ActionDescription[relayFeature.numberOfActions];
    deviceDescription.features[0] = relayFeature;

    ActionDescription turnOnAction;
    turnOnAction.id = "3253f251-3ab3-4987-8cdf-aa686de2b52b";
    turnOnAction.name = "TURN_ON";
    turnOnAction.triggerTopic = "devices/ce694f72-c12b-4e19-aa80-c3af37898615/feature/3253f251-3ab3-4987-8cdf-aa686de2b52b";
    relayFeature.actions[0] = turnOnAction;

    ActionDescription turnOffAction;
    turnOffAction.id = "7bb7f58e-68e3-4589-bbaf-e8e23b78e80a";
    turnOffAction.name = "TURN_OFF";
    turnOffAction.triggerTopic = "devices/ce694f72-c12b-4e19-aa80-c3af37898615/feature/7bb7f58e-68e3-4589-bbaf-e8e23b78e80a";
    relayFeature.actions[1] = turnOffAction;
}

void setup()
{
    Serial.begin(115200);

    Serial.println("Configuring device network");
    configureDevice();

    Serial.println("Initializing device status manager");
    statusManager = new StatusManager(&networkConfiguration);

    Serial.println("Starting network manager");
    networkConfiguration.networkStatus = (char *)CONNECTING_WIFI;
    network = new NetworkBase(networkConfiguration.hostName, (bool)false);
    statusManager->RunStatusManager();

    Serial.println("Waiting for WiFi connection stable");
    delay(500);

    device = new Device(&networkConfiguration, &deviceDescription);
}

void loop()
{
    statusManager->RunStatusManager();
    network->handleLoop();
    device->mqttClientLoop();
}