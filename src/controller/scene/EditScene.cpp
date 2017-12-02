//
// Created by Florian on 02.12.17.
//

#include "EditScene.h"

EditScene::EditScene(Tree *tree, OscController *osc, unsigned long uiInterval) : BaseScene(tree) {
    this->timer = new Timer(uiInterval);
    this->osc = osc;
}

void EditScene::setup() {
    BaseScene::setup();

    selectLeaf(leafIndex);
}

void EditScene::loop() {
    BaseScene::loop();

    if(timer->elapsed())
        updateUI();
}

void EditScene::updateUI() {
    LeafPtr leaf = tree->getLeaf(leafIndex);

    osc->send("/silva/selected/index", static_cast<float>(leafIndex));
    osc->send("/silva/selected/distance", static_cast<float>(leaf->getDistance()));
}

void EditScene::selectLeaf(uint16_t index) {
    for(auto i = 0; i < tree->getSize(); i++)
    {
        auto leaf = tree->getLeaf(i);

        // turn off light
        leaf->setBrightness(0, false);
    }
    tree->getLeaf(index)->setBrightness(255, false);
    leafIndex = index;
}

void EditScene::nextLeaf() {
    leafIndex = static_cast<uint16_t>((leafIndex + 1) % tree->getSize());
}

void EditScene::lastLeaf() {
    if(leafIndex == 0)
        leafIndex = tree->getSize();
    else
        leafIndex = static_cast<uint16_t>(leafIndex - 1);
}
