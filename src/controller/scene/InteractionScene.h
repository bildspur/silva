//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_INTERACTIONSCENE_H
#define SILVA_INTERACTIONSCENE_H


#include "BaseScene.h"

class InteractionScene : public BaseScene {
private:

public:
    explicit InteractionScene(LeafPtr *leafs);

    void setup() override;

    void loop() override;
};


#endif //SILVA_INTERACTIONSCENE_H
