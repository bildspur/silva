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

class TreeScene : public BaseScene {
private:
    LightSensor *lightSensor;

    AutoRangeFinder<uint16_t> *rangeFinder;
    Timer* rangeTimer;

    uint8_t life = 0;

    uint16_t lastLuminosity = 0;

public:
    explicit TreeScene(LightSensor *lightSensor, Tree *tree);

    void setup() override;

    void loop() override;

    void updateAutoRange(uint16_t luminosity);

    void updateLife();
};


#endif //SILVA_INTERACTIONSCENE_H
