//
// Created by Florian on 15.12.17.
//

#include <util/FloatUtil.h>
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

    runPerformance();
}

void PerformanceScene::runPerformance()
{
    auto t = static_cast<float>(millis() / 1000.0);
    auto intensity = getLightIntensity();

    for(auto i = 0; i < tree->getSize(); i++)
    {
        auto leaf = tree->getLeaf(i);

        // calculate sinus value
        auto distanceRadians = FloatUtil::map(leaf->getDistance(), MIN_DISTANCE, MAX_DISTANCE, 0.0, TWO_PI);
        auto brightness = static_cast<float>(0.5*(1+sin(t * intensity + distanceRadians)));

        // directly set
        leaf->setBrightness(brightness, false);
    }
}

float PerformanceScene::getLightIntensity()
{
    return FloatUtil::limit(FloatUtil::map(lightSensor->getLuminosity(), 0.0, getAverage(), 0.0, 1.0), 0.0, 1.0);
}

uint16_t PerformanceScene::getAverage()
{
    return static_cast<uint16_t>(average->get());
}

uint16_t PerformanceScene::getThreshold() {
    return static_cast<uint16_t>(average->get() / PERFORMANCE_LUX_THRESHOLD);
}
