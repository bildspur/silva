//
// Created by Florian on 06.12.17.
//

#ifndef SILVA_PCA9685RENDERER_H
#define SILVA_PCA9685RENDERER_H


#include <PCA9685.h>
#include "LightRenderer.h"

#define PCA_PIN_COUNT 13

class PCA9685Renderer : public LightRenderer {
private:
    typedef PCA9685 *PCA9685Ptr;

    uint8_t deviceCount;

    PCA9685Ptr *devices;

public:
    PCA9685Renderer(uint8_t deviceCount, Tree *tree, float minBrightness = 0.0f, float maxBrightness = 1.0f);

    void setup() override;

    void loop() override;

    void render(LeafPtr leaf) override ;
};


#endif //SILVA_PCA9685RENDERER_H
