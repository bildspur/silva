//
// Created by Florian on 06.12.17.
//

#include "AirConditioner.h"

AirConditioner::AirConditioner(uint8_t dhtPin, uint8_t heatPadPin, uint8_t fanPin, float desiredTemperature,
                               float temperatureOffset, unsigned long updateTime) {
    this->heatPadPin = heatPadPin;
    this->fanPin = fanPin;
    this->desiredTemperature = desiredTemperature;
    this->offset = temperatureOffset;

    timer = new Timer(updateTime);
    dht = new DHT(dhtPin, DHT_TYPE);
}

void AirConditioner::setup() {
    BaseController::setup();

    dht->begin();

    pinMode(heatPadPin, OUTPUT);
    pinMode(fanPin, OUTPUT);

    // set everything to off
    updateState();
}

void AirConditioner::loop() {
    BaseController::loop();

    if (timer->elapsed()) {
        measure();
        updateState();
    }
}

void AirConditioner::updateState() {
    if (state == ConditionerState::STEADY) {
        analogWrite(heatPadPin, LOW);
        analogWrite(fanPin, LOW);
    }

    if (state == ConditionerState::HEATING) {
        analogWrite(heatPadPin, HIGH);
        analogWrite(fanPin, LOW);
    }

    if (state == ConditionerState::COOLING) {
        analogWrite(heatPadPin, LOW);
        analogWrite(fanPin, HIGH);
    }
}

void AirConditioner::measure() {
    // reset state
    state = ConditionerState::STEADY;

    float h = dht->readHumidity();
    float t = dht->readTemperature();

    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    heatIndex = static_cast<float>(dht->computeHeatIndex(t, h, false));

    // check if is range
    if (heatIndex < (desiredTemperature - offset))
        state = ConditionerState::HEATING;

    if (heatIndex > (desiredTemperature + offset))
        state = ConditionerState::COOLING;
}

float AirConditioner::getHeatIndex() const {
    return heatIndex;
}
