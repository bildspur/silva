//
// Created by Florian on 15.12.17.
//

#include "PerformanceScene.h"

PerformanceScene::PerformanceScene(Tree *tree) : BaseScene("PerformanceScene", tree) {

}

void PerformanceScene::setup() {
    BaseScene::setup();

    // turn off all lights
    for(auto i = 0; i < tree->getSize(); i++)
    {
        auto leaf = tree->getLeaf(i);

        // turn off light
        leaf->turnOff(false);
    }
}

void PerformanceScene::loop() {
    BaseScene::loop();


}
