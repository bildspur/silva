//
// Created by Florian on 30.11.17.
//

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
