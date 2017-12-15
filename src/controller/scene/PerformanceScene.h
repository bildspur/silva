//
// Created by Florian on 15.12.17.
//

#ifndef SILVA_PERFORMANCESCENE_H
#define SILVA_PERFORMANCESCENE_H


#include <MovingAverage.h>
#include <util/Timer.h>
#include <controller/sensor/light/LightSensor.h>
#include "BaseScene.h"

#define MOVING_AVERAGE_FREQ (1000 * 30)
#define PERFORMANCE_LUX_THRESHOLD 3.0

class PerformanceScene : public BaseScene {
private:
    Timer* averageTimer;
    MovingAverage *average;

    bool firstLoop = true;

    LightSensor *lightSensor;

public:
    explicit PerformanceScene(LightSensor *lightSensor, Tree *tree);

    void setup() override;

    void loop() override;

    uint16_t getThreshold();

    float getLightIntensity();

    uint16_t getAverage();

    void runPerformance();
};


#endif //SILVA_PERFORMANCESCENE_H
