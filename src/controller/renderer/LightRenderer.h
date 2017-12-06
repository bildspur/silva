//
// Created by Florian on 06.12.17.
//

#ifndef SILVA_LIGHTRENDERER_H
#define SILVA_LIGHTRENDERER_H


#include <controller/BaseController.h>
#include <model/Tree.h>

class LightRenderer : public BaseController {
protected:
    explicit LightRenderer(Tree *tree, float minBrightness = 0.0f, float maxBrightness = 1.0f);

    Tree *tree;

    float minBrightness;
    float maxBrightness;

public:
    void setup() override;

    void loop() override;

    virtual void render(LeafPtr leaf);
};


#endif //SILVA_LIGHTRENDERER_H
