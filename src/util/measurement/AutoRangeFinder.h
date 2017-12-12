//
// Created by Florian on 10.12.17.
//

#ifndef AUTORANGEFINDER_AUTORANGEFINDER_H
#define AUTORANGEFINDER_AUTORANGEFINDER_H


#include <cstdint>
#include "CircularBuffer.h"

#define ARF_LOW 0
#define ARF_HIGH 65535

template<typename T>

class AutoRangeFinder {
private:
    CircularBuffer<T> *buffer;

    uint16_t size;

    T low = ARF_HIGH;
    T high = ARF_LOW;

    uint16_t addCounter = 0;

public:
    explicit AutoRangeFinder(uint16_t size);

    void calculate();

    void addMeasurement(T value);

    T getLow() const;

    T getHigh() const;

    T getMidpoint() const;

    void clear();
};

#endif //AUTORANGEFINDER_AUTORANGEFINDER_H
