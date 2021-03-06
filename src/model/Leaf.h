//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_LEAF_H
#define SILVA_LEAF_H


#include <c_types.h>
#include <util/EasingValue.h>

#define MIN_DISTANCE 0
#define MAX_DISTANCE 255

#define LEAF_MIN_BRIGHTNESS 0.0f
#define LEAF_MAX_BRIGHTNESS 1.0f

#define EASING_SPEED 0.1

class Leaf {
private:
    uint8_t id;

    uint8_t distance;

    EasingValue brightness = EasingValue(0.0, EASING_SPEED);

public:
    explicit Leaf(uint8_t id, uint8_t distance = 0);

    void update();

    void turnOn(bool easing = true);

    void turnOff(bool easing = true);

    void setBrightness(float value, bool easing = true);

    float getBrightness();

    void setDistance(uint8_t value);

    uint8_t getDistance();

    uint8_t getId();
};


#endif //SILVA_LEAF_H
