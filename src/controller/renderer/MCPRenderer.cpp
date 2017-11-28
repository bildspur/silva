//
// Created by Florian on 28.11.17.
//

#include <Arduino.h>
#include "MCPRenderer.h"

MCPRenderer::MCPRenderer(uint8_t mcpCount, LeafPtr *leafs) {
    this->mcpCount = mcpCount;
    this->leafs = leafs;
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
        auto mcpIndex = static_cast<uint8_t>(leaf->getId() / MCP_PIN_COUNT);
        auto leafPin = static_cast<uint8_t>(leaf->getId() % MCP_PIN_COUNT);

        // get mcp and send output
        auto mcp = mcps[mcpIndex];
        mcp->digitalWrite(leafPin, leaf->getBrightness());
    }
}
