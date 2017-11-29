//
// Created by Florian on 29.11.17.
//

#include "BH1750Sensor.h"

BH1750Sensor::BH1750Sensor(unsigned int updateFrequency) : LightSensor(updateFrequency) {

}

void BH1750Sensor::setup() {
    LightSensor::setup();

    lightMeter->begin(BH1750_CONTINUOUS_LOW_RES_MODE);
}

void BH1750Sensor::loop() {
    LightSensor::loop();
}

void BH1750Sensor::measure() {
    LightSensor::measure();

    luminostiy = lightMeter->readLightLevel();
}

uint16_t BH1750Sensor::getLuminosity() {
    return LightSensor::getLuminosity();
}

uint8_t BH1750Sensor::normalize(uint16_t value) {
    return LightSensor::normalize(value);
}
