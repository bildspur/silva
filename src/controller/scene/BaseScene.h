//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_BASESCENE_H
#define SILVA_BASESCENE_H


#include <controller/BaseController.h>
#include <model/Leaf.h>
#include <model/Tree.h>

class BaseScene : public BaseController {
private:

protected:
    Tree *tree;

public:
    explicit BaseScene(Tree *tree);

    void setup() override;

    void loop() override;
};


#endif //SILVA_BASESCENE_H
