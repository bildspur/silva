//
// Created by Florian on 30.11.17.
//

#include "OscDebugger.h"

OscController *OscDebugger::osc;

void OscDebugger::send(OSCMessage &msg) {
    osc->sendMessage(msg);
}

void OscDebugger::send(const char *route, const char *value) {
    OSCMessage msg(route);
    msg.add(value);
    send(msg);
}

void OscDebugger::send(const char *route, int value) {
    OSCMessage msg(route);
    msg.add(value);
    send(msg);
}

void OscDebugger::send(const char *route, float value) {
    OSCMessage msg(route);
    msg.add(value);
    send(msg);
}
