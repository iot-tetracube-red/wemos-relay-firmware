#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "./DeviceConfiguration.h"
#include "./NetworkBase/NetworkBase.h"
#include "./DeviceHardware.h"
#include "./SmartHubClient/SmartHubClient.h"
#include "./MessagingManager/MessagingManager.h"

// Network global settings and objects
String hostname = "multimedia-outlet-relay";
NetworkBase *network;
WiFiClient espClient;
PubSubClient client(espClient);

// Device description objects
const unsigned int numberOfActions = 2U;
NetworkConfiguration networkConfiguration;
DeviceDescription deviceDescripton;
ActionDescription actionsDescriptions[numberOfActions];
MessagingManager *messagingManager;

void defineDevice()
{
  networkConfiguration.mqttClientName = hostname;
  networkConfiguration.mqttBrokerServer = (char *)"192.168.1.252";
  networkConfiguration.mqttBrokerUser = (char *)"mqtt-device";
  networkConfiguration.mqttBrokerPassword = (char *)"mqtt-device-password";
  networkConfiguration.mqttBrokerPort = 1883;

  deviceDescripton.hostname = hostname;
  deviceDescripton.circuitId = "a9506610-e23a-42e1-999f-88c9c367183e";
  deviceDescripton.defaultName = "MultimediaOutletRelay";

  ActionDescription turnOn;
  turnOn.actionId = "62cff706-1183-4354-8628-5b2d2f608a3e";
  turnOn.defaultName = "Turn On";
  turnOn.isDefault = (bool)false;
  turnOn.pin = 13;
  turnOn.topic = "multimedia-outlet-relay/relay/on";
  actionsDescriptions[0] = turnOn;

  ActionDescription turnOff;
  turnOff.actionId = "3e8c8b40-1014-4e8e-8501-a808f7c01ddc";
  turnOff.defaultName = "Turn Off";
  turnOff.isDefault = (bool)false;
  turnOff.pin = 13;
  turnOff.topic = "multimedia-outlet-relay/relay/off";
  actionsDescriptions[1] = turnOff;
}

void doMqttConnection()
{
  Serial.print("Attempting to connect to broker: ");
  Serial.print(networkConfiguration.mqttBrokerServer);
  Serial.print(":");
  Serial.println(networkConfiguration.mqttBrokerPort);

  char brokerServerChar[networkConfiguration.mqttBrokerServer.length() + 1];
  networkConfiguration.mqttBrokerServer.toCharArray(brokerServerChar, networkConfiguration.mqttBrokerServer.length() + 1);
  client.setServer(brokerServerChar, networkConfiguration.mqttBrokerPort);
  client.setBufferSize(2048);

  char mqttClientNameChar[networkConfiguration.mqttClientName.length() + 1];
  networkConfiguration.mqttClientName.toCharArray(mqttClientNameChar, networkConfiguration.mqttClientName.length() + 1);
  char mqttUserChar[networkConfiguration.mqttBrokerUser.length() + 1];
  networkConfiguration.mqttBrokerUser.toCharArray(mqttUserChar, networkConfiguration.mqttBrokerUser.length() + 1);
  char mqttPasswordUser[networkConfiguration.mqttBrokerPassword.length() + 1];
  networkConfiguration.mqttBrokerPassword.toCharArray(mqttPasswordUser, networkConfiguration.mqttBrokerPassword.length() + 1);
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT...");

    if (client.connect(mqttClientNameChar, mqttUserChar, mqttPasswordUser))
    {
      Serial.println("Connected to MQTT");
      messagingManager->initializeMQTTMessaging();
    }
    else
    {
      Serial.println("Failed to connect to MQTT, retry in 2 secs...");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup()
{
  Serial.begin(115200);

  Serial.println("Setting up network settings");
  boolean reset = (bool)false;
  char hostnameChar[hostname.length() + 1];
  hostname.toCharArray(hostnameChar, hostname.length() + 1);
  network = new NetworkBase(hostnameChar, reset);

  Serial.println("Waiting for WiFi connection stable");
  delay(1000);

  Serial.println("Setting up device description objects");
  defineDevice();
  messagingManager = new MessagingManager(&client, &deviceDescripton, actionsDescriptions, numberOfActions);
}

void loop()
{
  network->handleLoop();
  if (!client.connected())
  {
    doMqttConnection();
  }
  client.loop();
}