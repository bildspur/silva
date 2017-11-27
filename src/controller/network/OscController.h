//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_OSCCONTROLLER_H
#define SILVA_OSCCONTROLLER_H


#include <controller/BaseController.h>
#include <cstdint>
#include <IPAddress.h>
#include <OSCMessage.h>
#include <WiFiUdp.h>

class OscController : public BaseController {
private:
    const IPAddress broadcastIP = IPAddress(255, 255, 255, 255);

    uint16_t inPort;
    uint16_t outPort;

    WiFiUDP Udp;

    void routeOSCMessage(OSCMessage &msg);

public:
    OscController(uint16_t inPort, uint16_t outPort);

    void setup() override;
    void loop() override;

    void sendMessage(OSCMessage &msg);
};


#endif //SILVA_OSCCONTROLLER_H
