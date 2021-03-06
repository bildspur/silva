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
#include <controller/scene/StarScene.h>
#include <controller/scene/PerformanceScene.h>

// global
#define SILVA_DEBUG true

#define LEAF_COUNT 26
#define RENDER_DEVICE_COUNT 2

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

// climate
#define DHT_PIN D5
#define HEAT_PAD_PIN D7
#define FAN_PIN D6
#define DESIRED_TEMP 15.0
#define TEMP_OFFSET 0.0f
#define DHT_UPDATE_TIME 5000

// typedefs
typedef BaseController *BaseControllerPtr;
typedef Leaf *LeafPtr;

// variables
LeafPtr leafs[LEAF_COUNT];
auto tree = Tree(LEAF_COUNT, leafs);

// controllers
auto network = NetworkController(DEVICE_NAME, SSID_NAME, SSID_PASSWORD, WIFI_AP);
auto ota = OTAController(DEVICE_NAME, OTA_PASSWORD, OTA_PORT);
auto osc = OscController(OSC_IN_PORT, OSC_OUT_PORT);
auto heartbeat = Heartbeat(HEARTBEAT_TIME);
auto airConditioner = AirConditioner(DHT_PIN, HEAT_PAD_PIN, FAN_PIN, DESIRED_TEMP, TEMP_OFFSET, DHT_UPDATE_TIME);

LightRenderer *renderer = new PCA9685Renderer(RENDER_DEVICE_COUNT, &tree, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

// sensor
LightSensor *lightSensor = new BH1750Sensor(LIGHT_SENSOR_UPDATE_FREQ);

// scenes
auto treeScene = TreeScene(lightSensor, &tree);
auto editScene = EditScene(&tree, &osc, EDIT_UI_TIME);
auto starScene = StarScene(&tree);
auto performanceScene = PerformanceScene(lightSensor, &tree);

auto sceneController = SceneController(&treeScene);

// controller list
BaseControllerPtr controllers[] = {
        &network,
        &ota,
        &osc,
        renderer,
        &heartbeat,
        lightSensor,
        &airConditioner,
        &sceneController
};

bool isEditMode() {
    return sceneController.getActiveScene() == &editScene;
}

bool isTreeMode() {
    return sceneController.getActiveScene() == &treeScene;
}

void changeScene(BaseScene *scene)
{
    sceneController.setActiveScene(scene);

    // setup scene
    sceneController.getActiveScene()->setup();
    heartbeat.sendHeartbeat();
}

void handleOsc(OSCMessage &msg) {
    msg.dispatch("/silva/scene/tree", [](OSCMessage &msg) {
        changeScene(&treeScene);
    });

    msg.dispatch("/silva/scene/edit", [](OSCMessage &msg) {
        changeScene(&editScene);
    });

    msg.dispatch("/silva/scene/stars", [](OSCMessage &msg) {
        changeScene(&starScene);
    });

    msg.dispatch("/silva/scene/performance", [](OSCMessage &msg) {
        changeScene(&performanceScene);
    });

    msg.dispatch("/silva/range/clear", [](OSCMessage &msg) {
        // do nothing
    });

    msg.dispatch("/silva/debug/refresh", [](OSCMessage &msg) {
        osc.send("/silva/debug/hic", airConditioner.getHeatIndex());
        osc.send("/silva/debug/life", treeScene.getLife());
        osc.send("/silva/debug/lux", lightSensor->getLuminosity());
        osc.send("/silva/debug/threshold", treeScene.getThreshold());
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

        msg.dispatch("/silva/select", [](OSCMessage &msg) {
            auto leafIndex = static_cast<uint8_t>(msg.getFloat(0));

            // bound check
            if(leafIndex >= 0 && leafIndex < tree.getSize()) {
                editScene.selectLeaf(leafIndex);
                editScene.updateUI();
            }
        });

        msg.dispatch("/silva/update", [](OSCMessage &msg) {
            auto leafIndex = static_cast<uint8_t>(msg.getFloat(0));
            auto distance = static_cast<uint8_t>(msg.getFloat(1));

            // bound check
            if(leafIndex >= 0 && leafIndex < tree.getSize()) {
                // update current leaf
                editScene.selectLeaf(leafIndex);
                editScene.getSelectedLeaf()->setDistance(distance);
                editScene.updateUI();
            }
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

    if(SILVA_DEBUG)
    {
        Serial.print("[AC] State: ");
        Serial.print(airConditioner.getState());

        Serial.print(" Temperature: ");
        Serial.println(airConditioner.getHeatIndex());

        Serial.print("[LUX] Luminosity: ");
        Serial.println(lightSensor->getLuminosity());

        Serial.print("[LED] 0");
        Serial.println(leafs[0]->getBrightness());

        Serial.print("[LIFE]: ");
        Serial.println(treeScene.getLife());

        Serial.print("[EMA] Threshold: ");
        Serial.println(treeScene.getThreshold());

        Serial.print("[MA]: ");
        Serial.println(treeScene.getAverage());

        Serial.println("================");
    }
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