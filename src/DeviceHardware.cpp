#include "DeviceHardware.h"

DeviceHardware::DeviceHardware()
{
}

void DeviceHardware::turnOnOutlet(ActionDescription *actionDescription)
{
    Serial.println("Should turn on the outlet");
    digitalWrite(actionDescription->pin, 1);
}

void DeviceHardware::turnOffOutlet(ActionDescription *actionDescription)
{
    Serial.println("Should turn off the outlet");
    digitalWrite(actionDescription->pin, 0);
}
