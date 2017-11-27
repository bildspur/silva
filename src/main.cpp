#include <Arduino.h>
#include "util/PlatformConstants.h"

// serial
#define BAUD_RATE 115200

// network
#define OTA_PORT 8266

void setup() {
    Serial.begin(BAUD_RATE);
}

void loop() {
}