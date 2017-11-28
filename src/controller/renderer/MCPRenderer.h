//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_MCPRENDERER_H
#define SILVA_MCPRENDERER_H

#include <controller/BaseController.h>
#include <util/PlatformConstants.h>
#include <Adafruit_MCP23017.h>

#define MCP_PIN_COUNT 16

class MCPRenderer : public BaseController {
private:
    typedef Adafruit_MCP23017 *MCP23017Ptr;

    uint8_t mcpCount;

    LeafPtr *leafs;
    MCP23017Ptr *mcps;

public:
    explicit MCPRenderer(uint8_t mcpCount, LeafPtr *leafs);

    void setup() override;

    void loop() override;

    void render(LeafPtr leaf);
};


#endif //SILVA_MCPRENDERER_H
