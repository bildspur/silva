//
// Created by Florian on 06.12.17.
//

#ifndef SILVA_STATUSLED_H
#define SILVA_STATUSLED_H


#include <controller/BaseController.h>
#include <cstdint>
#include <util/Timer.h>

#define DEFAULT_LED_RATE 300
#define LED_MIN_FREQ 0
#define LED_MAX_FREQ 255

class StatusLed : public BaseController {
private:
    Timer *timer = new Timer(DEFAULT_LED_RATE);

    uint8_t pin;

    bool isBlinking = false;

    bool isLedOn = false;

public:
    StatusLed(uint8_t pin);

    void setup() override;

    void loop() override;

    void blink();

    void blink(unsigned long rate);

    void turnOn();

    void turnOff();
};


#endif //SILVA_STATUSLED_H
