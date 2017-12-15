//
// Created by Florian on 28.11.17.
//

#include <controller/sensor/light/LightSensor.h>
#include "TreeScene.h"
#include "StarScene.h"

TreeScene::TreeScene(LightSensor *lightSensor, Tree *tree) : BaseScene("TreeScene", tree) {
    this->lightSensor = lightSensor;
    this->averageTimer = new Timer(MOVING_AVERAGE_FREQ);
    this->life = new EasingValue(LIFE_MAX, LIFE_EASING);

    this->average = new MovingAverage();
}

void TreeScene::setup() {
    BaseScene::setup();

    for (auto i = 0; i < tree->getSize(); i++) {
        auto leaf = tree->getLeaf(i);

        // turn off light and dim in (smooth intro)
        leaf->turnOff(false);
        leaf->turnOn();
    }

    // reset first loop
    firstLoop = true;
}

void TreeScene::loop() {
    BaseScene::loop();

    updateLife();
    updateLeafs();
}

void TreeScene::updateLife() {
    // use light sensor to change life value (0-255)
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

    // ma threshold
    auto threshold = getThreshold();

    if (luminosity < threshold)
        life->setTarget(LIFE_MIN);
    else
        life->setTarget(LIFE_MAX);

    life->update();
}

void TreeScene::updateLeafs() {
    // use life value together with distance to turn on and off leafs
    for (auto i = 0; i < tree->getSize(); i++) {
        auto leaf = tree->getLeaf(i);

        if (leaf->getDistance() <= life->get()) {
            //leaf->turnOn();
            applyStarPattern(leaf);
        } else {
            leaf->turnOff();
        }
    }
}

int TreeScene::getLife() const {
    return life->getInt();
}

MovingAverage::real TreeScene::getAverage() {
    return average->get();
}

void TreeScene::applyStarPattern(LeafPtr leaf) {
// check if leaf is on
    if (leaf->getBrightness() > (STAR_LEAF_OFF + 0.1)) {
        if (StarScene::isRandomCalled(RANDOM_OFF_FACTOR))
            leaf->setBrightness(STAR_LEAF_OFF);
    } else {
        if (StarScene::isRandomCalled(RANDOM_ON_FACTOR))
            leaf->setBrightness(static_cast<float>(random(static_cast<long>(STAR_LEAF_OFF * 100), 100) / 100.0));
    }
}

uint16_t TreeScene::getThreshold() {
    return static_cast<uint16_t>(average->get() / TREE_LUX_THRESHOLD);
}
