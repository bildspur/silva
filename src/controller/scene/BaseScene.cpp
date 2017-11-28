//
// Created by Florian on 28.11.17.
//

#include "BaseScene.h"

BaseScene::BaseScene(LeafPtr *leafs) {
    this->leafs = leafs;
}

void BaseScene::setup() {
    BaseController::setup();
}

void BaseScene::loop() {
    BaseController::loop();

    // update leafs
    for(auto i = 0; i < sizeof(leafs) + 1; i++)
    {
        leafs[i]->update();
    }
}