#ifndef DEVICECONFIGURATION_H
#define DEVICECONFIGURATION_H

#define NO_WIFI_CONNECTION "no_wifi_connection"
#define CONNECTING_WIFI "connecting_wifi"
#define CONNECTED_MQTT "connected_mqtt"

struct NetworkConfiguration
{
  char *hostName;
  char *smartHubServer;
  char *mqttHost;
  char *mqttBrokerUser;
  char *mqttBrokerPassword;
  int mqttBrokerPort;
  char *networkStatus;
};

struct ActionDescription
{
  String id;
  String name;
  String triggerTopic;
};

struct FeatureDescription
{
  String id;
  String name;
  String featureType;
  float value;
  unsigned int numberOfActions;
  ActionDescription *actions;
};

struct DeviceDescription
{
  String id;
  String name;
  char *feedbackTopic;
  unsigned int numberOfFeatures;
  FeatureDescription *features;
};

#endif