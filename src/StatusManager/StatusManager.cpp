#include "StatusManager.h"

StatusManager::StatusManager(NetworkConfiguration *networkConfiguration)
{
    this->networkConfiguration = networkConfiguration;
    pinMode(this->redPin, OUTPUT);
    digitalWrite(this->redPin, 0);
    pinMode(this->bluePin, OUTPUT);
    digitalWrite(this->bluePin, 0);
    pinMode(this->greenPin, OUTPUT);
    digitalWrite(this->greenPin, 0);

    this->RunStatusManager();
}

void StatusManager::RunStatusManager()
{
    digitalWrite(this->redPin, (strcmp(NO_WIFI_CONNECTION, this->networkConfiguration->networkStatus) == 0) ? 1 : 0);
    digitalWrite(this->bluePin, (strcmp(CONNECTING_WIFI, this->networkConfiguration->networkStatus) == 0) ? 1 : 0);
    digitalWrite(this->greenPin, (strcmp(CONNECTED_MQTT, this->networkConfiguration->networkStatus) == 0) ? 1 : 0);
}