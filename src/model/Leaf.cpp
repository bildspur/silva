//
// Created by Florian on 27.11.17.
//

#include "Leaf.h"

Leaf::Leaf(uint8_t id, uint8_t distance) {
    this->id = id;
    this->distance = distance;
}

void Leaf::update() {
    brightness.update();
}

void Leaf::setBrightness(uint8_t value) {
    brightness.setTarget(value);
}

uint8_t Leaf::getBrightness() {
    return static_cast<uint8_t>(brightness.getInt());
}

uint8_t Leaf::getId() {
    return id;
}
