//
// Created by Florian on 28.11.17.
//

#include <Arduino.h>
#include <util/FloatUtil.h>
#include "MCPRenderer.h"

MCPRenderer::MCPRenderer(uint8_t mcpCount, Tree *tree, float minBrightness, float maxBrightness)
        : LightRenderer(tree,
                        minBrightness,
                        maxBrightness) {

    this->mcpCount = mcpCount;
    this->mcps = new MCP23017Ptr[mcpCount];
}

void MCPRenderer::setup() {
    LightRenderer::setup();

    // setup mcps
    for (uint8_t i = 0; i < mcpCount; i++) {
        auto mcp = new Adafruit_MCP23017();
        mcp->begin(i);

        // init port mode for led control
        for (uint8_t j = 0; j < MCP_PIN_COUNT; j++) {
            mcp->pinMode(j, OUTPUT);
        }

        // add to list
        mcps[i] = mcp;
    }
}

void MCPRenderer::loop() {
    LightRenderer::loop();
}

void MCPRenderer::render(LeafPtr leaf) {
    LightRenderer::render(leaf);

    auto mcpIndex = static_cast<uint8_t>(leaf->getId() / MCP_PIN_COUNT);
    auto leafPin = static_cast<uint8_t>(leaf->getId() % MCP_PIN_COUNT);

    // get mcp and send output
    auto mcp = mcps[mcpIndex];

    // map global brightness
    auto brightness = FloatUtil::map(leaf->getBrightness(),
                                     LEAF_MIN_BRIGHTNESS, LEAF_MAX_BRIGHTNESS,
                                     minBrightness, maxBrightness);

    // de-normalise value
    auto pwmValue = FloatUtil::map(brightness,
                                   minBrightness, maxBrightness,
                                   0, MCP_MAX_VALUE);

    mcp->digitalWrite(leafPin, static_cast<uint8_t>(round(pwmValue)));
}
