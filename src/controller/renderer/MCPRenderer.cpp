//
// Created by Florian on 28.11.17.
//

#include "MCPRenderer.h"

MCPRenderer::MCPRenderer(uint8_t mcpCount, LeafPtr *leafs) {
    this->mcpCount = mcpCount;
    this->leafs = leafs;
    this->mcps = new MCP23017Ptr[mcpCount];
}

void MCPRenderer::setup() {
    BaseController::setup();

    // setup mcps
    for(auto i = 0; i < mcpCount; i++)
    {
        auto mcp = new Adafruit_MCP23017();
        mcp->begin(i);
        mcps[i] = mcp;
    }
}

void MCPRenderer::loop() {
    BaseController::loop();

    for(auto i = 0; i < sizeof(leafs) + 1; i++)
    {
        auto leaf = leafs[i];
    }
}
