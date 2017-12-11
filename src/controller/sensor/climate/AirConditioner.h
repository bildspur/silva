//
// Created by Florian on 06.12.17.
//

#ifndef SILVA_CLIMATECONTROLLER_H
#define SILVA_CLIMATECONTROLLER_H


#include <controller/BaseController.h>
#include <cstdint>
#include <util/Timer.h>
#include <DHT.h>

#define DHT_TYPE DHT22

class AirConditioner : public BaseController {
private:
    enum ConditionerState {
        HEATING, STEADY, COOLING
    };

    Timer *timer;

    ConditionerState state = STEADY;

    uint8_t heatPadPin;
    uint8_t fanPin;
    float desiredTemperature;
    float offset;

    DHT *dht;

    float heatIndex;

public:
    AirConditioner(uint8_t dhtPin, uint8_t heatPadPin, uint8_t fanPin, float desiredTemperature,
                   float temperatureOffset = 0.0f, unsigned long updateTime = 500);

    void setup() override;

    void loop() override;

    void measure();

    void updateState();

    float getHeatIndex() const;

    ConditionerState getState() const;
};


#endif //SILVA_CLIMATECONTROLLER_H
