//
// Created by Florian on 29.11.17.
//

#ifndef SILVA_BH1750LIGHTSENSOR_H
#define SILVA_BH1750LIGHTSENSOR_H


#include "LightSensor.h"

class BH1750Sensor : public LightSensor {
private:
    uint16_t luminostiy = 0;

    Timer *timer;

public:
    explicit BH1750Sensor(unsigned int updateFrequency = 250);

    void setup() override;
    void loop() override;

    void measure() override;

    uint16_t getLuminosity() override;

    uint8_t normalize(uint16_t value) override;
};


#endif //SILVA_BH1750LIGHTSENSOR_H
