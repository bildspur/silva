//
// Created by Florian on 28.11.17.
//

#include <cmath>
#include "EasingValue.h"

EasingValue::EasingValue(float value, float easing) {
    set(value);
    set(easing);
}

void EasingValue::update() {
    auto delta = target - value;
    value = delta * easing;
}

float EasingValue::get() {
    return value;
}

void EasingValue::set(float value) {
    this->value = value;
    this->target = value;
}

float EasingValue::setEasing(float easing) {
    this->easing = easing;
}

int EasingValue::getInt() {
    return static_cast<int>(round(value));
}

void EasingValue::setTarget(float value) {
    this->target = value;
}
