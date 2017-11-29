//
// Created by Florian on 29.11.17.
//

#include "TSL2561Sensor.h"

TSL2561Sensor::TSL2561Sensor(unsigned int updateFrequency) {
    timer = new Timer(updateFrequency);
};

void TSL2561Sensor::setup() {
    LightSensor::setup();

    if (tsl->begin()) {
        Serial.println("Found light sensor!");
    } else {
        Serial.println("No light sensor found!");
    }

    // set gain
    tsl->setGain(TSL2561_GAIN_16X);

    // set timing
    tsl->setTiming(TSL2561_INTEGRATIONTIME_13MS);
}

void TSL2561Sensor::loop() {
    LightSensor::loop();
}

uint16_t TSL2561Sensor::getLuminosity() {
    return LightSensor::getLuminosity();
}

uint8_t TSL2561Sensor::normalize(uint16_t value) {
    return LightSensor::normalize(value);
}

void TSL2561Sensor::measure() {
    LightSensor::measure();
}