//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_MCPRENDERER_H
#define SILVA_MCPRENDERER_H

#include <controller/BaseController.h>
#include <util/PlatformConstants.h>
#include <Adafruit_MCP23017.h>
#include <model/Tree.h>
#include "LightRenderer.h"

#define MCP_PIN_COUNT 16
#define MCP_MAX_VALUE 255

class MCPRenderer : public LightRenderer {
private:
    typedef Adafruit_MCP23017 *MCP23017Ptr;

    uint8_t mcpCount;
    MCP23017Ptr *mcps;

public:
    explicit MCPRenderer(uint8_t mcpCount, Tree *tree, float minBrightness = 0, float maxBrightness = 255);

    void setup() override;

    void loop() override;

    void render(LeafPtr leaf) override;
};


#endif //SILVA_MCPRENDERER_H
