//
// Created by Florian on 30.11.17.
//

#include <EEPROM.h>
#include <util/OscDebugger.h>
#include "Tree.h"

Tree::Tree(uint16_t size, LeafPtr *leafs) {
    this->size = size;
    this->leafs = leafs;
}

uint16_t Tree::getSize() {
    return size;
}

LeafPtr *Tree::getLeafs() {
    return leafs;
}

LeafPtr Tree::getLeaf(uint16_t index) {
    assert(index >= 0 && index < size);
    return leafs[index];
}

LeafPtr Tree::getLeaf(int index) {
    return getLeaf(static_cast<uint16_t>(index));
}

void Tree::loadLeafs() {
    initLeafs();

    // setup eeprom
    EEPROM.begin(EEPROM_SIZE);

    // load from eeprom check size and create
    uint16_t storedSize = 0;
    EEPROM.get(EEPROM_SIZE_ADDR, storedSize);

    // if size does not match reinit
    if(storedSize != size)
        return;

    // read distance and set it to leafs
    for(auto i = 0; i < size; i++)
    {
        uint8_t distance = 0;
        EEPROM.get(EEPROM_DATA_ADDR + i, distance);
        leafs[i]->setDistance(distance);
    }

    EEPROM.end();
}

void Tree::saveLeafs() {
    EEPROM.begin(EEPROM_SIZE);

    // save size
    EEPROM.put(EEPROM_SIZE_ADDR, size);

    // save leaf distances
    for(auto i = 0; i < size; i++)
    {
        EEPROM.put(EEPROM_DATA_ADDR + i, leafs[i]->getDistance());
    }

    EEPROM.end();
}

void Tree::initLeafs() {
    for (uint8_t i = 0; i < size; i++) {
        leafs[i] = new Leaf(i);
    }
}
