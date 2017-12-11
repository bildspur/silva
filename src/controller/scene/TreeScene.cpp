//
// Created by Florian on 28.11.17.
//

#include <controller/sensor/light/LightSensor.h>
#include "TreeScene.h"

TreeScene::TreeScene(LightSensor *lightSensor, Tree *tree) : BaseScene("TreeScene", tree) {
    this->lightSensor = lightSensor;
    this->rangeFinder = new AutoRangeFinder<uint16_t>(AUTO_RANGE_SIZE);
    this->rangeTimer = new Timer(AUTO_RANGE_FREQ);
}

void TreeScene::setup() {
    BaseScene::setup();

    for(auto i = 0; i < tree->getSize(); i++)
    {
        auto leaf = tree->getLeaf(i);

        // turn off light and dim in (smooth intro)
        leaf->turnOff(false);
        leaf->turnOn();
    }
}

void TreeScene::loop() {
    BaseScene::loop();

    updateLife();
}

void TreeScene::updateLife() {
    // use light sensor to change life value (0-255)
    auto luminosity = lightSensor->getLuminosity();

    if(rangeTimer->elapsed())
        updateAutoRange(luminosity);

    // add delta to life
    auto average = rangeFinder->getHigh() - rangeFinder->getLow();

    // todo: use life value together with distance to turn on and off leafs

    lastLuminosity = luminosity;
}

void TreeScene::updateAutoRange(uint16_t luminosity) {
    rangeFinder->addMeasurement(luminosity);
    rangeFinder->calculate();
}