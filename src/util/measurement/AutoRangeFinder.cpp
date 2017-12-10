//
// Created by Florian on 10.12.17.
//

#include <cmath>
#include "AutoRangeFinder.h"

template<typename T>
AutoRangeFinder<T>::AutoRangeFinder(uint16_t size) {
    this->size = size;
    this->buffer = new CircularBuffer<T>(size);
}

template<typename T>
void AutoRangeFinder<T>::calculate() {
    T low = std::numeric_limits<T>::max();
    T high = std::numeric_limits<T>::min();

    auto iterationSize = (addCounter < size) ? addCounter : size;

    for (auto i = 0; i < iterationSize; i++) {
        auto value = buffer->read(i);
        if (value < low)
            low = value;

        if (value > high)
            high = value;;
    }

    this->low = low;
    this->high = high;
}

template<typename T>
void AutoRangeFinder<T>::addMeasurement(T value) {
    buffer->write(value);

    if (addCounter < size)
        addCounter++;
}

template<typename T>
T AutoRangeFinder<T>::getLow() const {
    return low;
}

template<typename T>
T AutoRangeFinder<T>::getHigh() const {
    return high;
}

template
class AutoRangeFinder<uint8_t>;

template
class AutoRangeFinder<uint16_t>;

template
class AutoRangeFinder<uint32_t>;

template
class AutoRangeFinder<uint64_t>;

template
class AutoRangeFinder<float_t>;

template
class AutoRangeFinder<double_t>;

template
class AutoRangeFinder<short>;

template
class AutoRangeFinder<int>;

template
class AutoRangeFinder<long>;