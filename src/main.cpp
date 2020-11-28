#include <Arduino.h>
#include <ESP8266WebServer.h>

#include "./DeviceConfiguration.h"
#include "./NetworkBase/NetworkBase.h"
#include "./DeviceHardware.h"

// Network global settings and objects
char *hostname = (char *)"multimedia-outlet-relay";
NetworkBase *network;
ESP8266WebServer server(80);

// Device description objects
const unsigned int numberOfActions = 2U;
DeviceDescription deviceDescripton;
ActionDescription actionsDescriptions[numberOfActions];

void defineDevice()
{
  strcpy(deviceDescripton.hostname, hostname);
  strcpy(deviceDescripton.circuitId, (char *)"a9506610-e23a-42e1-999f-88c9c367183e");
  strcpy(deviceDescripton.defaultName, (char *)"MultimediaOutletRelay");

  ActionDescription turnOn;
  strcpy(turnOn.actionId, (char *)"62cff706-1183-4354-8628-5b2d2f608a3e");
  strcpy(turnOn.defaultName, (char *)"Turn On");
  turnOn.isDefault = (bool)false;
  turnOn.pin = 13;
  strcpy(turnOn.url, (char *)"/relay-on");
  actionsDescriptions[0] = turnOn;
  server.on(
      actionsDescriptions[0].url,
      HTTP_GET,
      [&]() {
        DeviceHardware::turnOnOutlet(&actionsDescriptions[0]);
        server.send(200, "text/html", "1"); 
      });

  ActionDescription turnOff;
  strcpy(turnOff.actionId, (char *)"3e8c8b40-1014-4e8e-8501-a808f7c01ddc");
  strcpy(turnOff.defaultName, (char *)"Turn Off");
  turnOff.isDefault = (bool)false;
  turnOn.pin = 13;
  strcpy(turnOff.url, (char *)"/relay-off");
  actionsDescriptions[1] = turnOff;
  server.on(
      actionsDescriptions[1].url,
      HTTP_GET,
      [&]() {
        DeviceHardware::turnOffOutlet(&actionsDescriptions[1]);
        server.send(200, "text/html", "1"); 
      });
}

void setup()
{
  Serial.begin(115200);

  Serial.println("Setting up network settings");
  boolean reset = (bool)false;
  network = new NetworkBase(hostname, reset);

  Serial.println("Setting up device description objects");
  defineDevice();

  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  network->handleLoop();
  server.handleClient();
}