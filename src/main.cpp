#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "./DeviceConfiguration.h"
#include "./NetworkBase/NetworkBase.h"
#include "./DeviceHardware.h"
#include "./SmartHubClient/SmartHubClient.h"
#include "./PayloadManager/PayloadManager.h"

// Network global settings and objects
String hostname = "multimedia-outlet-relay";
NetworkBase *network;
WiFiClient espClient;
ESP8266WebServer server(80);

// Device description objects
const unsigned int numberOfActions = 2U;
NetworkConfiguration networkConfiguration;
DeviceDescription deviceDescription;
ActionDescription actionsDescriptions[numberOfActions];
PayloadManager *payloadManager;
DeviceHardware *deviceHardware;
SmartHubClient *smartHubClient;

void handleTurnOutletOn()
{
  deviceHardware->turnOnOutlet(&actionsDescriptions[0]);
  char payload[500];
  payloadManager->getActionResponsePayload(payload);
  server.send(200, "application/json", payload);
}

void handleTurnOutletOff()
{
  deviceHardware->turnOffOutlet(&actionsDescriptions[1]);
  char payload[500];
  payloadManager->getActionResponsePayload(payload);
  server.send(200, "application/json", payload);
}

void handleNotFound(){
  server.send(404, "text/plain", "Not found");
}


void defineDevice()
{
  networkConfiguration.hostName = hostname;
  networkConfiguration.smartHubServer = "192.168.1.87:8080";

  deviceDescription.hostname = hostname;
  deviceDescription.circuitId = "a9506610-e23a-42e1-999f-88c9c367183e";
  deviceDescription.defaultName = "MultimediaOutletRelay";

  ActionDescription turnOn;
  turnOn.actionId = "62cff706-1183-4354-8628-5b2d2f608a3e";
  turnOn.defaultName = "Turn On";
  turnOn.pin = 13;
  turnOn.url = "/switch/on";
  actionsDescriptions[0] = turnOn;
  server.on(turnOn.url, handleTurnOutletOn);

  ActionDescription turnOff;
  turnOff.actionId = "3e8c8b40-1014-4e8e-8501-a808f7c01ddc";
  turnOff.defaultName = "Turn Off";
  turnOff.pin = 13;
  turnOff.url = "/switch/off";
  actionsDescriptions[1] = turnOff;
  server.on(turnOff.url, handleTurnOutletOff);
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

  WiFi.hostname(hostname);
  payloadManager = new PayloadManager();

  Serial.println("Setting up device description objects");
  deviceHardware = new DeviceHardware();
  defineDevice();
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  smartHubClient = new SmartHubClient(networkConfiguration.smartHubServer, payloadManager);
  smartHubClient->makeProvisioningRequest(&deviceDescription, actionsDescriptions, numberOfActions);
}

void loop()
{
  network->handleLoop();
  server.handleClient();
}