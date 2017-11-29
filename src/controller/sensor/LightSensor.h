//
// Created by Florian on 29.11.17.
//

#ifndef SILVA_LIGHTSENSOR_H
#define SILVA_LIGHTSENSOR_H


#include <cstdint>
#include <util/Timer.h>
#include <controller/BaseController.h>

class LightSensor : public BaseController {
private:
    uint16_t luminostiy = 0;

    Timer *timer;

public:
    explicit LightSensor(unsigned int updateFrequency = 250);

    void setup() override;

    void loop() override;

    virtual void measure();

    virtual uint16_t getLuminosity();

    virtual uint8_t normalize(uint16_t value);
};

#endif //SILVA_LIGHTSENSOR_H
