//
// Created by Florian on 06.12.17.
//

#include <util/FloatUtil.h>
#include "PCA9685Renderer.h"

PCA9685Renderer::PCA9685Renderer(uint8_t deviceCount, Tree *tree, float minBrightness, float maxBrightness)
        : LightRenderer(tree,
                        minBrightness,
                        maxBrightness) {

    this->deviceCount = deviceCount;
    devices = new PCA9685Ptr[deviceCount];
}

void PCA9685Renderer::setup() {
    LightRenderer::setup();

// setup mcps
    for (uint8_t i = 0; i < deviceCount; i++) {
        auto device = new PCA9685(static_cast<uint8_t>(0x0 + i), PCA9685_MODE_N_DRIVER);
        device->setup();

        // add to list
        devices[i] = device;
    }
}

void PCA9685Renderer::loop() {
    LightRenderer::loop();
}

void PCA9685Renderer::render(LeafPtr leaf) {
    LightRenderer::render(leaf);

    auto deviceIndex = static_cast<uint8_t>(leaf->getId() / PCA_PIN_COUNT);
    auto leafPin = static_cast<uint8_t>(leaf->getId() % PCA_PIN_COUNT);

    // get device and send output
    auto device = devices[deviceIndex];

    // map global brightness
    auto brightness = FloatUtil::map(leaf->getBrightness(),
                                     LEAF_MIN_BRIGHTNESS, LEAF_MAX_BRIGHTNESS,
                                     minBrightness, maxBrightness);

    // de-normalise value
    auto pwmValue = FloatUtil::map(brightness,
                                   minBrightness, maxBrightness,
                                   0, PCA9685_MAX_VALUE);

    // send data
    device->getPin(leafPin).setValueAndWrite(static_cast<uint16_t>(round(pwmValue)));
}
