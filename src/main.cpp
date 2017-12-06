#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <util/PlatformConstants.h>
#include <controller/BaseController.h>
#include <controller/network/NetworkController.h>
#include <controller/network/OTAController.h>
#include <controller/network/OscController.h>
#include <controller/renderer/MCPRenderer.h>
#include <controller/scene/TreeScene.h>
#include <controller/sensor/BH1750Sensor.h>
#include <util/OscDebugger.h>
#include <controller/network/Heartbeat.h>
#include <controller/scene/EditScene.h>
#include <controller/scene/SceneController.h>
#include <controller/renderer/PCA9685Renderer.h>

// global
#define LEAF_COUNT 8
#define MCP_COUNT 1

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

#define HEARTBEAT_TIME 3000
#define EDIT_UI_TIME 3000

#define FLOAT_COMPARE 0.5

// typedefs
typedef BaseController *BaseControllerPtr;
typedef Leaf *LeafPtr;

// variables
LeafPtr leafs[LEAF_COUNT];
auto tree = Tree(LEAF_COUNT, leafs);

// controllers
auto network = NetworkController(DEVICE_NAME, SSID_NAME, SSID_PASSWORD);
auto ota = OTAController(DEVICE_NAME, OTA_PASSWORD, OTA_PORT);
auto osc = OscController(OSC_IN_PORT, OSC_OUT_PORT);
auto heartbeat = Heartbeat(HEARTBEAT_TIME);

LightRenderer *renderer = new PCA9685Renderer(MCP_COUNT, &tree, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

// sensor
LightSensor *lightSensor = new BH1750Sensor(LIGHT_SENSOR_UPDATE_FREQ);

// scenes
auto isEditMode = false;
auto treeScene = TreeScene(lightSensor, &tree);
auto editScene = EditScene(&tree, &osc, EDIT_UI_TIME);

auto sceneController = SceneController(&treeScene);

// controller list
BaseControllerPtr controllers[] = {
        &network,
        &ota,
        &osc,
        renderer,
        &heartbeat,
        lightSensor,
        &sceneController
};

void handleOsc(OSCMessage &msg) {
    msg.dispatch("/silva/isEdit", [](OSCMessage &msg) {
        isEditMode = (msg.getFloat(0) > FLOAT_COMPARE);

        if (isEditMode)
            sceneController.setActiveScene(&editScene);
        else
            sceneController.setActiveScene(&treeScene);

        // setup scene
        sceneController.getActiveScene()->setup();
        heartbeat.sendHeartbeat();
    });

    // edit scene osc handlers
    if (isEditMode) {
        msg.dispatch("/silva/refresh", [](OSCMessage &msg) {
            editScene.updateUI();
        });

        msg.dispatch("/silva/next", [](OSCMessage &msg) {
            editScene.nextLeaf();
            editScene.updateUI();
        });

        msg.dispatch("/silva/last", [](OSCMessage &msg) {
            editScene.lastLeaf();
            editScene.updateUI();
        });

        msg.dispatch("/silva/selected/distance", [](OSCMessage &msg) {
            editScene.getSelectedLeaf()->setDistance(static_cast<uint8_t>(msg.getFloat(0)));
            editScene.updateUI();
        });

        msg.dispatch("/silva/save", [](OSCMessage &msg) {
            tree.saveLeafs();
            osc.send("/silva/status", "saved!");
        });
    }
}

void sendHeartbeat() {
    OSCMessage msg("/silva/isEdit");
    msg.add(isEditMode ? 1.0f : 0.0f);
    osc.sendMessage(msg);
}

void setup() {
    Serial.begin(BAUD_RATE);

    // setup wire
    Wire.begin(D2, D1);

    // setup osc debugger
    OscDebugger::osc = &osc;

    // setup leafs
    tree.loadLeafs();

    // setup controllers
    for (auto &controller : controllers) {
        controller->setup();
    }

    // setup handlers
    osc.onMessageReceived(handleOsc);
    heartbeat.onHeartbeat(sendHeartbeat);

    // add osc mdns
    MDNS.addService("osc", "udp", OSC_IN_PORT);

    Serial.println("setup finished!");
    osc.send("/silva/status", "setup finished!");
}

void loop() {
    // loop controllers
    for (auto &controller : controllers) {
        controller->loop();
    }
}