//
// Created by Florian on 28.11.17.
//

#include <Arduino.h>
#include "MCPRenderer.h"

MCPRenderer::MCPRenderer(uint8_t mcpCount, LeafPtr *leafs, uint8_t minBrightness, uint8_t maxBrightness) {
    this->mcpCount = mcpCount;
    this->leafs = leafs;
    this->minBrightness = minBrightness;
    this->maxBrightness = maxBrightness;

    this->mcps = new MCP23017Ptr[mcpCount];
}

void MCPRenderer::setup() {
    BaseController::setup();

    // setup mcps
    for(uint8_t i = 0; i < mcpCount; i++)
    {
        auto mcp = new Adafruit_MCP23017();
        mcp->begin(i);

        // init port mode for led control
        for(uint8_t j = 0; j < MCP_PIN_COUNT; j++)
        {
            mcp->pinMode(j, OUTPUT);
        }

        // add to list
        mcps[i] = mcp;
    }
}

void MCPRenderer::loop() {
    BaseController::loop();

    for(auto i = 0; i < sizeof(leafs) + 1; i++)
    {
        auto leaf = leafs[i];
        render(leaf);
    }
}

void MCPRenderer::render(LeafPtr leaf) {
    auto mcpIndex = static_cast<uint8_t>(leaf->getId() / MCP_PIN_COUNT);
    auto leafPin = static_cast<uint8_t>(leaf->getId() % MCP_PIN_COUNT);

    // get mcp and send output
    auto mcp = mcps[mcpIndex];
    auto value = static_cast<uint8_t>(map(leaf->getBrightness(), 0, 255, minBrightness, maxBrightness));
    mcp->digitalWrite(leafPin, value);
}
