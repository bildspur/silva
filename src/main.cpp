#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <util/PlatformConstants.h>
#include <controller/BaseController.h>
#include <controller/network/NetworkController.h>
#include <controller/network/OTAController.h>
#include <controller/network/OscController.h>
#include <controller/renderer/MCPRenderer.h>
#include <controller/scene/TreeScene.h>
#include <controller/sensor/light/BH1750Sensor.h>
#include <util/OscDebugger.h>
#include <controller/network/Heartbeat.h>
#include <controller/scene/EditScene.h>
#include <controller/scene/SceneController.h>
#include <controller/renderer/PCA9685Renderer.h>
#include <controller/sensor/climate/AirConditioner.h>

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

#define SSID_NAME "Der Geraet"
#define SSID_PASSWORD ""

#define OTA_PASSWORD "bildspur"
#define OTA_PORT 8266

#define OSC_OUT_PORT 9000
#define OSC_IN_PORT 8000

#define HEARTBEAT_TIME 3000
#define EDIT_UI_TIME 3000

// climate
#define DHT_PIN D5
#define HEAT_PAD_PIN D6
#define FAN_PIN D7
#define DESIRED_TEMP 20.0
#define TEMP_OFFSET 1.0f
#define DHT_UPDATE_TIME 5000

// typedefs
typedef BaseController *BaseControllerPtr;
typedef Leaf *LeafPtr;

// variables
LeafPtr leafs[LEAF_COUNT];
auto tree = Tree(LEAF_COUNT, leafs);

// controllers
auto network = NetworkController(DEVICE_NAME, SSID_NAME, SSID_PASSWORD, WIFI_STA);
auto ota = OTAController(DEVICE_NAME, OTA_PASSWORD, OTA_PORT);
auto osc = OscController(OSC_IN_PORT, OSC_OUT_PORT);
auto heartbeat = Heartbeat(HEARTBEAT_TIME);
auto airConditioner = AirConditioner(DHT_PIN, HEAT_PAD_PIN, FAN_PIN, DESIRED_TEMP, TEMP_OFFSET, DHT_UPDATE_TIME);

LightRenderer *renderer = new PCA9685Renderer(MCP_COUNT, &tree, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

// sensor
LightSensor *lightSensor = new BH1750Sensor(LIGHT_SENSOR_UPDATE_FREQ);

// scenes
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
        &sceneController,
        &airConditioner
};

bool isEditMode() {
    return sceneController.getActiveScene() == &editScene;
}

bool isTreeMode() {
    return sceneController.getActiveScene() == &treeScene;
}

void handleOsc(OSCMessage &msg) {
    msg.dispatch("/silva/scene/tree", [](OSCMessage &msg) {
        sceneController.setActiveScene(&treeScene);

        // setup scene
        sceneController.getActiveScene()->setup();
        heartbeat.sendHeartbeat();
    });

    msg.dispatch("/silva/scene/edit", [](OSCMessage &msg) {
        sceneController.setActiveScene(&editScene);

        // setup scene
        sceneController.getActiveScene()->setup();
        heartbeat.sendHeartbeat();
    });

    // edit scene osc handlers
    if (isEditMode()) {
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
    osc.send("/silva/scene/active", sceneController.getActiveScene()->getName());
}

void setup() {
    Serial.begin(BAUD_RATE);

    // wait 3000 seconds for debugging
    delay(3000);

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