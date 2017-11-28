//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_BASESCENE_H
#define SILVA_BASESCENE_H


#include <controller/BaseController.h>
#include <util/PlatformConstants.h>

class BaseScene : public BaseController {
private:
    LeafPtr *leafs;

public:
    explicit BaseScene(LeafPtr *leafs);

    void setup() override;

    void loop() override;
};


#endif //SILVA_BASESCENE_H
