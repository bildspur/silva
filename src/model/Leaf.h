//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_LEAF_H
#define SILVA_LEAF_H


#include <c_types.h>
#include <util/EasingValue.h>

#define MIN_DISTANCE 0
#define MAX_DISTANCE 255

#define EASING_SPEED 0.05

class Leaf {
private:
    uint8_t id;

    uint8_t distance;

    EasingValue brightness = EasingValue(0.0, EASING_SPEED);

public:
    explicit Leaf(uint8_t id, uint8_t distance = 0);

    void update();

    void setBrightness(uint8_t value, bool easing = true);

    uint8_t getBrightness();

    uint8_t getId();
};


#endif //SILVA_LEAF_H
