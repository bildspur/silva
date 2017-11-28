//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_INTERACTIONSCENE_H
#define SILVA_INTERACTIONSCENE_H


#include <controller/sensor/LightSensor.h>
#include "BaseScene.h"

class InteractionScene : public BaseScene {
private:
    LightSensor *lightSensor;

public:
    explicit InteractionScene(LightSensor *lightSensor, LeafPtr *leafs);

    void setup() override;

    void loop() override;
};


#endif //SILVA_INTERACTIONSCENE_H
