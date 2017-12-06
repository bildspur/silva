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
#include <controller/status/StatusLed.h>

#define STA_MAX_DELAYS 100
#define STATUS_LED_PIN D8

class NetworkController : public BaseController {
private:
    const char *deviceName;
    const char *ssid;
    const char *password;

    WiFiMode_t wifiMode;

    StatusLed *statusLed = new StatusLed(STATUS_LED_PIN);

    void initSTA();
    void setupSTA();
    void setupAP();
    void setupMDNS();
    String getIPAddress();

public:
    NetworkController(const char *deviceName, const char *ssid, const char *password, WiFiMode_t wifiMode = WIFI_AP);

    void setup() override;
    void loop() override;

    void printNetworkInformation();
};


#endif //SILVA_NETWORKCONTROLLER_H
