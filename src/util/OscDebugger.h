//
// Created by Florian on 30.11.17.
//

#ifndef SILVA_OSCDEBUGGER_H
#define SILVA_OSCDEBUGGER_H


#include <controller/network/OscController.h>

class OscDebugger {
public:
    static OscController *osc;

    static void send(OSCMessage &msg);

    static void send(const char *route, const char *value);

    static void send(const char *route, int value);

    static void send(const char *route, float value);
};


#endif //SILVA_OSCDEBUGGER_H
