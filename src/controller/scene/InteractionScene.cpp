//
// Created by Florian on 28.11.17.
//

#include "InteractionScene.h"

InteractionScene::InteractionScene(LightSensor *lightSensor, LeafPtr *leafs) : BaseScene(leafs) {
    this->lightSensor = lightSensor;
}

void InteractionScene::setup() {
    BaseScene::setup();
}

void InteractionScene::loop() {
    BaseScene::loop();
}
