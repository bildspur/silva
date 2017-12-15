//
// Created by Florian on 15.12.17.
//

#ifndef SILVA_PERFORMANCESCENE_H
#define SILVA_PERFORMANCESCENE_H


#include "BaseScene.h"

class PerformanceScene : public BaseScene {
public:
    explicit PerformanceScene(Tree *tree);

    void setup() override;

    void loop() override;

};


#endif //SILVA_PERFORMANCESCENE_H
