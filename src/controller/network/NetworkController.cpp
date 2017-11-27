//
// Created by Florian on 27.11.17.
//

#include "NetworkController.h"

NetworkController::NetworkController(char *deviceName, char *ssid, char *password) {
    this->deviceName = deviceName;
    this->ssid = ssid;
    this->password = password;
}

void NetworkController::setup() {
    BaseController::setup();

    WiFi.hostname(deviceName);

    setupAP();
    setupMDNS();

    printNetworkInformation();
}

void NetworkController::loop() {
    BaseController::loop();
}

void NetworkController::setupAP() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
}

void NetworkController::setupMDNS() {
    if (!MDNS.begin(deviceName)) {
        Serial.println("Error setting up MDNS responder!");
    }

    // Add service to MDNS-SD
    MDNS.addServiceTxt("osc", "udp", "mac", WiFi.macAddress());
}

void NetworkController::printNetworkInformation() {
    Serial.print("WiFi State: ");
    Serial.println(WiFi.status());

    Serial.print("Local IP address: ");
    Serial.println(WiFi.softAPIP().toString());

    Serial.print("Mac Address: ");
    Serial.println(WiFi.macAddress());
}
