//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_BASESCENE_H
#define SILVA_BASESCENE_H


#include <controller/BaseController.h>
#include <model/Leaf.h>

typedef Leaf* LeafPtr;

class BaseScene : public BaseController {
private:

protected:
    LeafPtr *leafs;

public:
    explicit BaseScene(LeafPtr *leafs);

    void setup() override;

    void loop() override;
};


#endif //SILVA_BASESCENE_H
