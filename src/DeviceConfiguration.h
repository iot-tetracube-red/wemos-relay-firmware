#ifndef DEVICECONFIGURATION_H
#define DEVICECONFIGURATION_H

struct DeviceDescription
{
  char circuitId[36];
  char defaultName[200];
  char hostname[200];
};

struct ActionDescription
{
  char actionId[36];
  char defaultName[200];
  bool isDefault;
  unsigned int pin;
  char url[200];
};

#endif