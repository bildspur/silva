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

protected:
    explicit LightSensor(unsigned int updateFrequency = 250);

    uint16_t luminosity = 0;

    Timer *timer;

public:
    void setup() override;

    void loop() override;

    virtual void measure();

    virtual uint16_t getLuminosity();

    virtual uint8_t normalize(uint16_t value);
};

#endif //SILVA_LIGHTSENSOR_H
