//
// Created by Florian on 29.11.17.
//

#ifndef SILVA_BH1750LIGHTSENSOR_H
#define SILVA_BH1750LIGHTSENSOR_H


#include <BH1750.h>
#include "LightSensor.h"

#define BH1750_ADDR_FLOAT 0x23

class BH1750Sensor : public LightSensor {
private:
    BH1750 *lightMeter = new BH1750(BH1750_ADDR_FLOAT);

public:
    explicit BH1750Sensor(unsigned int updateFrequency = 250);

    void setup() override;
    void loop() override;

    void measure() override;

    uint16_t getLuminosity() override;

    uint8_t normalize(uint16_t value) override;
};


#endif //SILVA_BH1750LIGHTSENSOR_H
