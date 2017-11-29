#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <util/PlatformConstants.h>
#include <controller/BaseController.h>
#include <controller/network/NetworkController.h>
#include <controller/network/OTAController.h>
#include <controller/network/OscController.h>
#include <controller/renderer/MCPRenderer.h>
#include <controller/scene/TreeScene.h>
#include <controller/sensor/LightSensor.h>
#include <controller/sensor/TSL2561Sensor.h>

// global
#define LEAF_COUNT 25
#define MCP_COUNT 2

#define LIGHT_SENSOR_UPDATE_FREQ 250

#define MIN_BRIGHTNESS 0
#define MAX_BRIGHTNESS 255

// serial
#define BAUD_RATE 115200

// network
#define DEVICE_NAME "silva-master"

#define SSID_NAME "silva"
#define SSID_PASSWORD "SilvaZauberwald"

#define OTA_PASSWORD "bildspur"
#define OTA_PORT 8266

#define OSC_OUT_PORT 9000
#define OSC_IN_PORT 8000

// typedefs
typedef BaseController* BaseControllerPtr;
typedef Leaf* LeafPtr;
typedef BaseScene* ScenePtr;

// variables
LeafPtr leafs[LEAF_COUNT];

// controllers
auto network = NetworkController(DEVICE_NAME, SSID_NAME, SSID_PASSWORD);
auto ota = OTAController(DEVICE_NAME, OTA_PASSWORD, OTA_PORT);
auto osc = OscController(OSC_IN_PORT, OSC_OUT_PORT);
auto mcp = MCPRenderer(MCP_COUNT, leafs, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
LightSensor *lightSensor = new TSL2561Sensor(LIGHT_SENSOR_UPDATE_FREQ);

// scenes
auto interactionScene = TreeScene(lightSensor, leafs);

ScenePtr activeScene = &interactionScene;

// controller list
BaseControllerPtr controllers[] = {
        &network,
        &ota,
        &osc,
        &mcp,
        lightSensor,
        activeScene
};

void setup() {
    Serial.begin(BAUD_RATE);

    // setup wire
    Wire.begin();

    // setup leafs
    for(uint8_t i = 0; i < LEAF_COUNT; i++)
    {
        leafs[i] = new Leaf(i);
    }

    // setup controllers
    for (auto &controller : controllers) {
        controller->setup();
    }

    // setup handlers
    osc.onMessageReceived([](OSCMessage &msg) {
        Serial.println("osc message received!");
    });

    // add osc mdns
    MDNS.addService("osc", "udp", OSC_IN_PORT);

    Serial.println("setup finished!");
}

void loop() {
    // loop controllers
    for (auto &controller : controllers) {
        controller->loop();
    }
}