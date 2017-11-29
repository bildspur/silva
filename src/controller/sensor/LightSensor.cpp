//
// Created by Florian on 28.11.17.
//

#include "LightSensor.h"

LightSensor::LightSensor(unsigned int updateFrequency) {
    timer = new Timer(updateFrequency);
};

void LightSensor::setup() {
    BaseController::setup();

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

void LightSensor::loop() {
    BaseController::loop();

    // read value
    if(timer->elapsed())
    {
        luminostiy =  tsl->getLuminosity(TSL2561_VISIBLE);
    }
}

uint16_t LightSensor::getLuminosity() {
    return luminostiy;
}

uint8_t LightSensor::normalize(uint16_t value) {
    return static_cast<uint8_t>(map(value, 0, 65535, 0, 255));
}