//
// Created by Florian on 28.11.17.
//

#include "EasingFloat.h"

EasingFloat::EasingFloat(float value, float easing) {
    this->target = value;
    set(value);
    set(easing);
}

void EasingFloat::update() {
    auto delta = target - value;
    value = delta * easing;
}

float EasingFloat::get() {
    return value;
}

void EasingFloat::set(float value) {
    this->value = value;
}

float EasingFloat::setEasing(float easing) {
    this->easing = easing;
}
