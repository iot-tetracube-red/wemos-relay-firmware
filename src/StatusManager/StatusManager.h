/**************************************************************************/
/*!
    @file     PayloadManager.h
    @author   Erika Gili & Davide di Domenico

    v1.0  - First release
*/
/**************************************************************************/
#ifndef STATUSMANAGER_H
#define STATUSMANAGER_H

#include <Arduino.h>

#include "DeviceConfiguration.h"

class StatusManager
{

public:
    StatusManager(NetworkConfiguration *networkConfiguration);
    void RunStatusManager();

private:
    NetworkConfiguration *networkConfiguration;

    const long interval = 1000;
    long currentMillins = 0;
    unsigned int redPin = 14;
    unsigned int greenPin = 13;
    unsigned int bluePin = 12;
    bool ledIsOn = false;
};

#endif