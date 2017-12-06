//
// Created by Florian on 06.12.17.
//

#include "StatusLed.h"

StatusLed::StatusLed(uint8_t pin) {
    this->pin = pin;
}

void StatusLed::setup() {
    BaseController::setup();
    pinMode(pin, OUTPUT);
    turnOff();
}

void StatusLed::loop() {
    BaseController::loop();

    if(isBlinking && timer->elapsed())
    {
        if(isLedOn)
            turnOff();
        else
            turnOn();
        isLedOn = !isLedOn;
    }
}

void StatusLed::blink() {
    blink(DEFAULT_LED_RATE);
}

void StatusLed::blink(unsigned long rate) {
    isBlinking = true;
    timer->setWaitTime(rate);
}

void StatusLed::turnOn() {
    isBlinking = false;
    isLedOn = true;
    write(LED_MAX_FREQ);
}

void StatusLed::turnOff() {
    isBlinking = false;
    isLedOn = false;
    write(LED_MIN_FREQ);
}

void StatusLed::write(uint8_t frequency) {
    analogWrite(pin, frequency);
}
