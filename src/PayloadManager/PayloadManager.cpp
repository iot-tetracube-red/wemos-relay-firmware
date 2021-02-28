#include "PayloadManager.h"

PayloadManager::PayloadManager()
{
}

void PayloadManager::getCommandResponsePayload(char *payload, ActionDescription *actionDescription)
{
    size_t capacity = 500;

    DynamicJsonDocument jsonDocument(capacity);
    jsonDocument["circuitId"] = actionDescription->id;
    jsonDocument["success"] = (bool)true;

    serializeJson(jsonDocument, payload, capacity);
}

void PayloadManager::getProvisioningPayload(char *payload, DeviceDescription *deviceDescription)
{
    StaticJsonDocument<500> jsonDocument;
    jsonDocument["id"] = deviceDescription->id;
    jsonDocument["name"] = deviceDescription->name;
    jsonDocument["feedback-topic"] = deviceDescription->feedbackTopic;

    JsonArray features = jsonDocument.createNestedArray("features");
    for (unsigned int featureCounter = 0; featureCounter < deviceDescription->numberOfFeatures; featureCounter++)
    {
        FeatureDescription currentFeature = deviceDescription->features[featureCounter];
        JsonObject feature = features.createNestedObject();
        feature["id"] = currentFeature.id;
        feature["name"] = currentFeature.name;
        feature["feature_type"] = currentFeature.featureType;
        feature["value"] = currentFeature.value;

        JsonArray actions = feature.createNestedArray("actions");
        for (unsigned int actionCounter = 0; actionCounter < currentFeature.numberOfActions; actionCounter++)
        {
            ActionDescription currentAction = currentFeature.actions[actionCounter];
            JsonObject action = actions.createNestedObject();
            action["id"] = currentAction.id;
            action["name"] = currentAction.name;
            action["trigger_topic"] = currentAction.triggerTopic;
        }
    }

    serializeJson(jsonDocument, payload, 500);
    Serial.println(payload);
}

void PayloadManager::getActionResponsePayload(char *payload)
{
    StaticJsonDocument<500> jsonDocument;
    jsonDocument["success"] = "true";
    serializeJson(jsonDocument, payload, 500);
}