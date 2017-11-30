//
// Created by Florian on 28.11.17.
//

#include "BaseScene.h"

BaseScene::BaseScene(Tree *tree) {
    this->tree = tree;
}

void BaseScene::setup() {
    BaseController::setup();
}

void BaseScene::loop() {
    BaseController::loop();

    // update leafs
    for(auto i = 0; i < tree->getSize(); i++)
    {
        tree->getLeaf(i)->update();
    }
}