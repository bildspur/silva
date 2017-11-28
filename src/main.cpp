#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <controller/BaseController.h>
#include <controller/network/NetworkController.h>
#include <controller/network/OTAController.h>
#include <controller/network/OscController.h>
#include "util/PlatformConstants.h"

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

// variables

// controllers
auto network = NetworkController(DEVICE_NAME, SSID_NAME, SSID_PASSWORD);
auto ota = OTAController(DEVICE_NAME, OTA_PASSWORD, OTA_PORT);
auto osc = OscController(OSC_IN_PORT, OSC_OUT_PORT);

BaseControllerPtr controllers[] = {
        &network,
        &ota,
        &osc
};

void setup() {
    Serial.begin(BAUD_RATE);

    // setup controllers
    for (auto &controller : controllers) {
        controller->setup();
    }

    // add osc mdns
    MDNS.addService("osc", "udp", OSC_IN_PORT);
}

void loop() {
    // loop controllers
    for (auto &controller : controllers) {
        controller->loop();
    }
}