//
// Created by Florian on 06.12.17.
//

#include "LightRenderer.h"

LightRenderer::LightRenderer(Tree *tree, float minBrightness, float maxBrightness) {
    this->tree = tree;
    this->minBrightness = minBrightness;
    this->maxBrightness = maxBrightness;
}

void LightRenderer::setup() {
    BaseController::setup();
}

void LightRenderer::loop() {
    BaseController::loop();

    for(auto i = 0; i < tree->getSize(); i++)
    {
        auto leaf = tree->getLeaf(i);
        render(leaf);
    }
}

void LightRenderer::render(LeafPtr leaf) {
    // send out data
}
