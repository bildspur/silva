//
// Created by Florian on 29.11.17.
//

#include "LightSensor.h"

LightSensor::LightSensor(unsigned int updateFrequency) {
    timer = new Timer(updateFrequency);
}

void LightSensor::setup() {
    BaseController::setup();
}

void LightSensor::loop() {
    BaseController::loop();

    // read value
    if(timer->elapsed())
    {
        measure();
    }
}

uint16_t LightSensor::getLuminosity() {
    return luminosity;
}

uint8_t LightSensor::normalize(uint16_t value) {
    return static_cast<uint8_t>(map(value, 0, 65535, 0, 255));
}

void LightSensor::measure() {

}
