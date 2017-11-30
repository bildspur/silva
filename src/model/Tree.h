//
// Created by Florian on 30.11.17.
//

#ifndef SILVA_TREE_H
#define SILVA_TREE_H

#include <assert.h>
#include "Leaf.h"

typedef Leaf* LeafPtr;

class Tree {
private:
    LeafPtr *leafs;

    uint16_t size;

public:
    Tree(uint16_t size, LeafPtr *leafs);

    uint16_t getSize();

    LeafPtr *getLeafs();

    LeafPtr getLeaf(uint16_t index);

    LeafPtr getLeaf(int index);
};


#endif //SILVA_TREE_H
