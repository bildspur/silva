//
// Created by Florian on 27.11.17.
//

#include <HardwareSerial.h>
#include "Leaf.h"

Leaf::Leaf(uint8_t id, uint8_t distance) {
    this->id = id;
    this->distance = distance;
}

void Leaf::update() {
    brightness.update();
}

void Leaf::setBrightness(float value, bool easing) {
    if (easing)
        brightness.setTarget(value);
    else
        brightness.set(value);
}

float Leaf::getBrightness() {
    return brightness.get();
}

uint8_t Leaf::getId() {
    return id;
}

void Leaf::setDistance(uint8_t value) {
    distance = value;
}

uint8_t Leaf::getDistance() {
    return distance;
}

void Leaf::turnOn(bool easing) {
    setBrightness(LEAF_MAX_BRIGHTNESS, easing);
}

void Leaf::turnOff(bool easing) {
    setBrightness(LEAF_MIN_BRIGHTNESS, easing);
}
