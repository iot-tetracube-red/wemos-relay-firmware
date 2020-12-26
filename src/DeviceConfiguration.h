#ifndef DEVICECONFIGURATION_H
#define DEVICECONFIGURATION_H

struct NetworkConfiguration
{
  String hostName;
  String smartHubServer;
  String mqttBrokerUser;
  String mqttBrokerPassword;
  int mqttBrokerPort;
};

struct DeviceDescription
{
  String circuitId;
  String defaultName;
  String hostname;
};

struct ActionDescription
{
  String actionId;
  String defaultName;
  unsigned int pin;
  String url;
};

#endif