//
// Created by Florian on 10.12.17.
//

#ifndef AUTORANGEFINDER_AUTORANGEFINDER_H
#define AUTORANGEFINDER_AUTORANGEFINDER_H


#include <cstdint>
#include "CircularBuffer.h"
#include <limits>

template<typename T>

class AutoRangeFinder {
private:
    CircularBuffer<T> *buffer;

    uint16_t size;

    T low = std::numeric_limits<T>::max();
    T high = std::numeric_limits<T>::min();

    uint16_t addCounter = 0;

public:
    explicit AutoRangeFinder(uint16_t size);

    void calculate();

    void addMeasurement(T value);

    T getLow() const;

    T getHigh() const;
};

#endif //AUTORANGEFINDER_AUTORANGEFINDER_H
