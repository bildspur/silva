//
// Created by Florian on 02.12.17.
//

#include "EditScene.h"

EditScene::EditScene(Tree *tree, OscController *osc, unsigned long uiInterval) : BaseScene("EditScene", tree) {
    this->timer = new Timer(uiInterval);
    this->osc = osc;
}

void EditScene::setup() {
    BaseScene::setup();

    selectLeaf(leafIndex);
}

void EditScene::loop() {
    BaseScene::loop();

    if (timer->elapsed())
        updateUI();
}

void EditScene::updateUI() {
    LeafPtr leaf = tree->getLeaf(leafIndex);

    osc->send("/silva/selected/index", static_cast<float>(leafIndex));
    osc->send("/silva/selected/distance", static_cast<float>(leaf->getDistance()));
}

void EditScene::selectLeaf(uint16_t index) {
    leafIndex = index;
    markLeaf(leafIndex);
}

void EditScene::nextLeaf() {
    auto newIndex = static_cast<uint16_t>((leafIndex + 1) % tree->getSize());
    selectLeaf(newIndex);
}

void EditScene::lastLeaf() {
    uint16_t newIndex = 0;
    if (leafIndex == 0)
        newIndex = static_cast<uint16_t>(tree->getSize() - 1);
    else
        newIndex = static_cast<uint16_t>(leafIndex - 1);

    selectLeaf(newIndex);
}

Leaf *EditScene::getSelectedLeaf() {
    return tree->getLeaf(leafIndex);
}

void EditScene::markLeaf(uint16_t index) {
    for (auto i = 0; i < tree->getSize(); i++) {
        auto leaf = tree->getLeaf(i);

        // turn off light
        leaf->turnOff(false);
    }
    tree->getLeaf(index)->turnOn(false);
}
