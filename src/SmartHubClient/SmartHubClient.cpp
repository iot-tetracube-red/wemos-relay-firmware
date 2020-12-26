#include "SmartHubClient.h"

SmartHubClient::SmartHubClient(String smartHubServer,
                               PayloadManager *payloadManager)
{
    this->smartHubServer = smartHubServer;
    this->httpClient = new HTTPClient();
    this->payloadManager = payloadManager;
}

void SmartHubClient::makeProvisioningRequest(DeviceDescription *deviceDescription,
                                             ActionDescription *actionDescriptions,
                                             unsigned int numberOfActions)
{
    Serial.print("Calling for device provisioning: ");
    Serial.println("http://" + this->smartHubServer + "/devices/provisioning");
    char payload[500];
    this->payloadManager->getProvisioningPayload(payload, deviceDescription, actionDescriptions, numberOfActions);
    this->httpClient->begin("http://" + this->smartHubServer + "/devices/provisioning");
    this->httpClient->addHeader("Content-Type", "application/json");
    int httpResponseCode = this->httpClient->POST(payload);
    this->httpClient->end();
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode); 
}