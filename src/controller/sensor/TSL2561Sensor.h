//
// Created by Florian on 29.11.17.
//

#ifndef SILVA_TSL2561SENSOR_H
#define SILVA_TSL2561SENSOR_H


#include <TSL2561.h>
#include "LightSensor.h"

class TSL2561Sensor : public LightSensor {
private:
    TSL2561 *tsl = new TSL2561(TSL2561_ADDR_FLOAT);

    uint16_t luminostiy = 0;

    Timer *timer;

public:
    explicit TSL2561Sensor(unsigned int updateFrequency = 250);

    void setup() override;
    void loop() override;

    void measure() override;

    uint16_t getLuminosity() override;

    uint8_t normalize(uint16_t value) override;
};


#endif //SILVA_TSL2561SENSOR_H
