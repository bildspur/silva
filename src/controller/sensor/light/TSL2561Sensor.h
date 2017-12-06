//
// Created by Florian on 29.11.17.
//

#ifndef SILVA_TSL2561SENSOR_H
#define SILVA_TSL2561SENSOR_H


#include <TSL2561.h>
#include "LightSensor.h"

class TSL2561Sensor : public LightSensor {
private:
    TSL2561 *lightMeter = new TSL2561(TSL2561_ADDR_FLOAT);

public:
    explicit TSL2561Sensor(unsigned int updateFrequency = 250);

    void setup() override;
    void loop() override;

    void measure() override;

    uint16_t getLuminosity() override;

    uint8_t normalize(uint16_t value) override;
};


#endif //SILVA_TSL2561SENSOR_H
