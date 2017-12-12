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
    auto threshold = rangeFinder->getMidpoint();

    // check midpoint same level
    if(threshold == 0)
        threshold = static_cast<uint16_t>(rangeFinder->getHigh() / 2);

    // hard workaround
    threshold = FIXED_THRESHOLD;

    if(luminosity < threshold)
        life->setTarget(LIFE_MIN);
    else
        life->setTarget(LIFE_MAX);

    life->update();
    lastLuminosity = luminosity;
}

void TreeScene::updateAutoRange(uint16_t luminosity) {
    // probability check for luminosity
    if(luminosity == ARF_HIGH)
        return;

    rangeFinder->addMeasurement(luminosity);
    rangeFinder->calculate();
}

void TreeScene::updateLeafs() {
    // use life value together with distance to turn on and off leafs
    for(auto i = 0; i < tree->getSize(); i++) {
        auto leaf = tree->getLeaf(i);

        if(leaf->getDistance() <= life->get())
            leaf->turnOn();
        else
            leaf->turnOff();
    }
}

int TreeScene::getLife() const {
    return life->getInt();
}

AutoRangeFinder<uint16_t> *TreeScene::getRangeFinder() const {
    return rangeFinder;
}
