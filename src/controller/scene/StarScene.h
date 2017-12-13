//
// Created by Florian on 13.12.17.
//

#ifndef SILVA_STARSCENE_H
#define SILVA_STARSCENE_H


#include "BaseScene.h"

class StarScene : public BaseScene {
private:
    float randomOnFactor = 0.95;
    float randomOffFactor = 0.8;
    float fadeSpeed = 0.01;

public:
    StarScene(Tree *tree);

    void setup() override;

    void loop() override;

    bool isRandomCalled(float factor);
};


#endif //SILVA_STARSCENE_H
