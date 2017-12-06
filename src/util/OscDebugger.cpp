//
// Created by Florian on 30.11.17.
//

#include "OscDebugger.h"

OscController *OscDebugger::osc;

void OscDebugger::send(OSCMessage &msg) {
    osc->sendMessage(msg);
}

void OscDebugger::send(const char *route, const char *value) {
    osc->send(route, value);
}

void OscDebugger::send(const char *route, int value) {
    osc->send(route, value);
}

void OscDebugger::send(const char *route, float value) {
    osc->send(route, value);
}
