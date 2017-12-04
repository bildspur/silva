//
// Created by Florian on 28.11.17.
//

#include "BaseScene.h"

BaseScene::BaseScene(const char *name, Tree *tree) {
    this->name = name;
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

const char * BaseScene::getName() const {
    return name;
}
