//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_NETWORKCONTROLLER_H
#define SILVA_NETWORKCONTROLLER_H

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <IPAddress.h>

#include <controller/BaseController.h>

class NetworkController : public BaseController {
private:
    const char *deviceName;
    const char *ssid;
    const char *password;

    void setupAP();
    void setupMDNS();

public:
    NetworkController(const char *deviceName, const char *ssid, const char *password);

    void setup() override;
    void loop() override;

    void printNetworkInformation();
};


#endif //SILVA_NETWORKCONTROLLER_H
