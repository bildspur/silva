//
// Created by Florian on 28.11.17.
//

#include <controller/sensor/light/LightSensor.h>
#include "TreeScene.h"

TreeScene::TreeScene(LightSensor *lightSensor, Tree *tree) : BaseScene("TreeScene", tree) {
    this->lightSensor = lightSensor;
    this->rangeFinder = new AutoRangeFinder<uint16_t>(AUTO_RANGE_SIZE);
    this->rangeTimer = new Timer(AUTO_RANGE_FREQ);
    this->life = new EasingValue(LIFE_MAX, LIFE_EASING);
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
    updateLeafs();
}

void TreeScene::updateLife() {
    // use light sensor to change life value (0-255)
    auto luminosity = lightSensor->getLuminosity();

    if(rangeTimer->elapsed())
        updateAutoRange(luminosity);

    // change life
    auto threshold = rangeFinder->getHigh() - rangeFinder->getLow();

    if(luminosity < threshold)
        life->setTarget(LIFE_MIN);
    else
        life->setTarget(LIFE_MAX);

    life->update();
    lastLuminosity = luminosity;
}

void TreeScene::updateAutoRange(uint16_t luminosity) {
    rangeFinder->addMeasurement(luminosity);
    rangeFinder->calculate();
}

void TreeScene::updateLeafs() {
    // use life value together with distance to turn on and off leafs
    for(auto i = 0; i < tree->getSize(); i++) {
        auto leaf = tree->getLeaf(i);

        if(life->get() < leaf->getDistance())
            leaf->turnOn();
        else
            leaf->turnOff();
    }
}
