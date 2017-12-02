//
// Created by Florian on 02.12.17.
//

#include "Heartbeat.h"

Heartbeat::Heartbeat(unsigned long waitTime) {
    this->timer = new Timer(waitTime);
}

void Heartbeat::onHeartbeat(Heartbeat::HeartbeatHandler onHeartbeatCallback) {
    this->onHeartbeatCallback = onHeartbeatCallback;
}

void Heartbeat::setup() {
    BaseController::setup();
}

void Heartbeat::loop() {
    BaseController::loop();

    if(timer->elapsed())
        sendHeartbeat();
}

void Heartbeat::sendHeartbeat() {
    if (onHeartbeatCallback)
        onHeartbeatCallback();
}
