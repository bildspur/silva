//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_INTERACTIONSCENE_H
#define SILVA_INTERACTIONSCENE_H


#include <controller/sensor/light/LightSensor.h>
#include <util/measurement/AutoRangeFinder.h>
#include "BaseScene.h"

#define AUTO_RANGE_SIZE 60
#define AUTO_RANGE_FREQ (1000 * 30)

#define LIFE_MIN 0
#define LIFE_MAX 255
#define LIFE_EASING 0.1

class TreeScene : public BaseScene {
private:
    LightSensor *lightSensor;

    AutoRangeFinder<uint16_t> *rangeFinder;
    Timer* rangeTimer;

    EasingValue *life;

    uint16_t lastLuminosity = 0;

public:
    explicit TreeScene(LightSensor *lightSensor, Tree *tree);

    void setup() override;

    void loop() override;

    void updateAutoRange(uint16_t luminosity);

    void updateLife();

    void updateLeafs();
};


#endif //SILVA_INTERACTIONSCENE_H
