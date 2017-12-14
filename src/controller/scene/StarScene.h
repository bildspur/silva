//
// Created by Florian on 13.12.17.
//

#ifndef SILVA_STARSCENE_H
#define SILVA_STARSCENE_H


#include "BaseScene.h"

#define RANDOM_ON_FACTOR 0.99
#define RANDOM_OFF_FACTOR 0.95

class StarScene : public BaseScene {
public:
    StarScene(Tree *tree);

    void setup() override;

    void loop() override;

    static bool isRandomCalled(float factor);
};


#endif //SILVA_STARSCENE_H
