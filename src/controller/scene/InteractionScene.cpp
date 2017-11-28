//
// Created by Florian on 28.11.17.
//

#include "InteractionScene.h"

InteractionScene::InteractionScene(LightSensor *lightSensor, LeafPtr *leafs) : BaseScene(leafs) {
    this->lightSensor = lightSensor;
}

void InteractionScene::setup() {
    BaseScene::setup();

    // todo: turn off light and dimm in (nice intro)
}

void InteractionScene::loop() {
    BaseScene::loop();

    // todo: use light sensor to change life value (0-255)
    // todo: use life value together with distance to turn on and off leafs
}
