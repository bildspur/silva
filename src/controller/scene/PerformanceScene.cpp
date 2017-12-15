//
// Created by Florian on 15.12.17.
//

#include "PerformanceScene.h"

PerformanceScene::PerformanceScene(LightSensor *lightSensor, Tree *tree) : BaseScene("PerformanceScene", tree) {
    this->lightSensor = lightSensor;
    this->averageTimer = new Timer(MOVING_AVERAGE_FREQ);
    this->average = new MovingAverage();
}

void PerformanceScene::setup() {
    BaseScene::setup();

    // turn off all lights
    for(auto i = 0; i < tree->getSize(); i++)
    {
        auto leaf = tree->getLeaf(i);

        // turn off light
        leaf->turnOff(false);
    }

    // reset first loop
    firstLoop = true;
}

void PerformanceScene::loop() {
    BaseScene::loop();

    auto luminosity = lightSensor->getLuminosity();

    if (firstLoop)
        average->reset(luminosity);

    if (firstLoop || averageTimer->elapsed()) {
        // only update if is not under threshold (only high values count)
        if(luminosity >= getThreshold()) {
            average->update(luminosity);
        }
        firstLoop = false;
    }
}

uint16_t PerformanceScene::getThreshold() {
    return static_cast<uint16_t>(average->get() / PERFORMANCE_LUX_THRESHOLD);
}
