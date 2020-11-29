#include "PayloadManager.h"

PayloadManager::PayloadManager()
{
}

void PayloadManager::getCommandResponsePayload(char *payload, ActionDescription *actionDescription)
{
    size_t capacity = 500;

    DynamicJsonDocument jsonDocument(capacity);
    jsonDocument["circuitId"] = actionDescription->actionId;
    jsonDocument["success"] = (bool)true;

    serializeJson(jsonDocument, payload, capacity);
}

void PayloadManager::getProvisioningPayload(char *payload,
                                            DeviceDescription *deviceDescription,
                                            ActionDescription actionDescriptions[],
                                            unsigned int numberOfActions)
{
    StaticJsonDocument<500> jsonDocument;
    jsonDocument["id"] = deviceDescription->circuitId;
    jsonDocument["default_name"] = deviceDescription->defaultName;
    jsonDocument["hostname"] = deviceDescription->hostname;

    JsonArray actions = jsonDocument.createNestedArray("actions");
    for (unsigned int i = 0; i < numberOfActions; i++)
    {
        JsonObject action = actions.createNestedObject();
        action["id"] = actionDescriptions[i].actionId;
        action["default_name"] = actionDescriptions[i].defaultName;
        action["is_default"] = actionDescriptions[i].isDefault ? "true" : "false";
        action["topic"] = actionDescriptions[i].topic;
    }

    serializeJson(jsonDocument, payload, 500);
}