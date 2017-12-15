//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_INTERACTIONSCENE_H
#define SILVA_INTERACTIONSCENE_H


#include <controller/sensor/light/LightSensor.h>
#include <util/measurement/AutoRangeFinder.h>
#include <MovingAverage.h>
#include "BaseScene.h"

#define MOVING_AVERAGE_FREQ (1000 * 30)

#define LIFE_MIN 0
#define LIFE_MAX 255
#define LIFE_EASING 0.01

#define STAR_LEAF_OFF 0.15

#define TREE_LUX_THRESHOLD 3.0

class TreeScene : public BaseScene {
private:
    LightSensor *lightSensor;

    EasingValue *life;

    bool firstLoop = true;

    Timer* averageTimer;
    MovingAverage *average;

public:
    explicit TreeScene(LightSensor *lightSensor, Tree *tree);

    void setup() override;

    void loop() override;

    void updateLife();

    void updateLeafs();

    void applyStarPattern(LeafPtr leaf);

    int getLife() const;

    MovingAverage::real getAverage();

    uint16_t getThreshold();
};


#endif //SILVA_INTERACTIONSCENE_H
