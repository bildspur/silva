#include <Arduino.h>
#include <util/LogBook.h>
#include "util/PlatformConstants.h"

#define BAUD_RATE 115200

void setup() {
    LogBook::setup(BAUD_RATE);
}

void loop() {
}