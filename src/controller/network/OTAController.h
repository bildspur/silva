//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_OTACONTROLLER_H
#define SILVA_OTACONTROLLER_H

#include <ArduinoOTA.h>
#include <controller/BaseController.h>

class OTAController : public BaseController {
private:
    char *deviceName;
    char *password;
    uint8_t port;

    void setupOTAOnError();

    void setupOTAOnProgress();

    void setupOTAOnEnd();

    void setupOTAOnStart();

    void setupOTAAuth();

public:
    OTAController(char *deviceName, char *password, uint8_t port);

    void setup() override;

    void loop() override;
};


#endif //SILVA_OTACONTROLLER_H
