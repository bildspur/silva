#include <Arduino.h>
#include <ESP8266mDNS.h>
#include "util/PlatformConstants.h"

// serial
#define BAUD_RATE 115200

// network
#define OSC_LOCAL_PORT 8000

#define OTA_PORT 8266

void setup() {
    Serial.begin(BAUD_RATE);

    // add osc mdns
    MDNS.addService("osc", "udp", OSC_LOCAL_PORT);
}

void loop() {
}