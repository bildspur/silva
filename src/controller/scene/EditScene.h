//
// Created by Florian on 02.12.17.
//

#ifndef SILVA_EDITSCENE_H
#define SILVA_EDITSCENE_H


#include <util/Timer.h>
#include <OSCMessage.h>
#include <controller/network/OscController.h>
#include "BaseScene.h"

class EditScene : public BaseScene {
private:
    uint16_t leafIndex = 0;

    Timer *timer;
    OscController *osc;

public:
    explicit EditScene(Tree *tree, OscController *osc, unsigned long uiInterval);

    void setup() override;

    void loop() override;

    void updateUI(bool timerReset = true);

    void selectLeaf(uint16_t index);

    void nextLeaf();

    void lastLeaf();

    void markLeaf(uint16_t index);

    Leaf *getSelectedLeaf();
};


#endif //SILVA_EDITSCENE_H
