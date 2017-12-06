//
// Created by Florian on 28.11.17.
//

#include <controller/sensor/LightSensor.h>
#include "TreeScene.h"

TreeScene::TreeScene(LightSensor *lightSensor, Tree *tree) : BaseScene("TreeScene", tree) {
    this->lightSensor = lightSensor;
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

    // use light sensor to change life value (0-255)
    auto luminosity = lightSensor->getLuminosity();
    auto delta = lightSensor->normalize(lastLuminosity - luminosity);

    // add delta to life


    // todo: use life value together with distance to turn on and off leafs

    lastLuminosity = luminosity;
}
