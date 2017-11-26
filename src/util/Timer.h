//
// Created by Florian on 15.11.17.
//

#ifndef SILVA_TIMER_H
#define SILVA_TIMER_H

#include <Arduino.h>

class Timer {
private:
    unsigned long previousMillis = 0;
    unsigned long waitTime;

public:
    explicit Timer(unsigned long waitTime);

    boolean elapsed();
};


#endif //SILVA_TIMER_H
