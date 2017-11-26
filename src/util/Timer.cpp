//
// Created by Florian on 15.11.17.
//

#include "Timer.h"

Timer::Timer(unsigned long waitTime) {
    this->waitTime = waitTime;
}

boolean Timer::elapsed() {
    unsigned long currentMillis = millis();
    bool result = currentMillis - previousMillis >= waitTime;

    if(result)
        previousMillis = currentMillis;

    return result;
}
