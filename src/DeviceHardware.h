#ifndef DEVICEHARDWARE_H
#define DEVICEHARDWARE_H

#include <Arduino.h>

#include "DeviceConfiguration.h"

class DeviceHardware
{

public:
    DeviceHardware();
    static void turnOnOutlet(ActionDescription *actionDescription);
    static void turnOffOutlet(ActionDescription *actionDescription);
};

#endif