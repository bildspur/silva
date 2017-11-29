//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_INTERACTIONSCENE_H
#define SILVA_INTERACTIONSCENE_H


#include <controller/sensor/LightSensor.h>
#include "BaseScene.h"

class TreeScene : public BaseScene {
private:
    LightSensor *lightSensor;

    uint8_t life;

    uint16_t lastLuminosity;

public:
    explicit TreeScene(LightSensor *lightSensor, LeafPtr *leafs);

    void setup() override;

    void loop() override;
};


#endif //SILVA_INTERACTIONSCENE_H
