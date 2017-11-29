//
// Created by Florian on 28.11.17.
//

#include "TreeScene.h"

TreeScene::TreeScene(LightSensor *lightSensor, LeafPtr *leafs) : BaseScene(leafs) {
    this->lightSensor = lightSensor;
}

void TreeScene::setup() {
    BaseScene::setup();

    for(auto i = 0; i < sizeof(leafs); i++)
    {
        auto leaf = leafs[i];

        // turn off light and dim in (smooth intro)
        leaf->setBrightness(0, false);
        leaf->setBrightness(255);
    }
}

void TreeScene::loop() {
    BaseScene::loop();

    // todo: use light sensor to change life value (0-255)
    // todo: use life value together with distance to turn on and off leafs
}
