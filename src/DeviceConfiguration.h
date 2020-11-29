#ifndef DEVICECONFIGURATION_H
#define DEVICECONFIGURATION_H

struct NetworkConfiguration
{
  String mqttClientName;
  String mqttBrokerServer;
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
  bool isDefault;
  unsigned int pin;
  String topic;
};

#endif