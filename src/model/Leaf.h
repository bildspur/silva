//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_LEAF_H
#define SILVA_LEAF_H


#include <c_types.h>
#include <util/EasingValue.h>

#define MIN_DISTANCE 0
#define MAX_DISTANCE 255

#define MIN_BRIGHTNESS 0
#define MAX_BRIGHTNESS 255

class Leaf {
private:
    uint8_t id;

    uint8_t distance;

    EasingValue brightness = EasingValue(0.0, 0.1);

public:
    explicit Leaf(uint8_t id, uint8_t distance = 0);

    void update();

    void setBrightness(uint8_t value);
};


#endif //SILVA_LEAF_H
