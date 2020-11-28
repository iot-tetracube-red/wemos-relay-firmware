#include <Arduino.h>

#include "./NetworkBase/NetworkBase.h"

// Network global settings and objects
char *hostname = (char *)"MultimediaOutletRelay";
NetworkBase *network;

void setup()
{
  Serial.begin(115200);

  Serial.println("Setting up network settings");
  boolean reset = (bool)false;
  network = new NetworkBase(hostname, reset);
}

void loop()
{
  network->handleLoop();
}