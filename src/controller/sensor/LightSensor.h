//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_LIGHTSENSOR_H
#define SILVA_LIGHTSENSOR_H


#include <controller/BaseController.h>
#include <cstdint>
#include <TSL2561.h>
#include <util/Timer.h>

class LightSensor : public BaseController {
private:
    TSL2561 *tsl = new TSL2561(TSL2561_ADDR_FLOAT);

    uint16_t luminostiy = 0;

    Timer *timer;

public:
    explicit LightSensor(unsigned int updateFrequency = 250);

    void setup() override;
    void loop() override;

    uint16_t getLuminosity();

    uint8_t normalize(uint16_t value);
};


#endif //SILVA_LIGHTSENSOR_H
