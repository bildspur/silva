//
// Created by Florian on 10.12.17.
//

#include <cmath>
#include "CircularBuffer.h"

template<typename T>
CircularBuffer<T>::CircularBuffer(uint16_t size) {
    this->values = new T[size];
    this->index = 0;
    this->size = size;
}

template<typename Type>
uint16_t CircularBuffer<Type>::getSize() const {
    return size;
}

template<typename T>
void CircularBuffer<T>::write(uint16_t index, T value) {
    this->values[index] = value;
}

template<typename T>
void CircularBuffer<T>::write(T value) {
    write(index, value);
    index = static_cast<uint16_t>(divisorMod(index + 1, size));
}

template<typename T>
T CircularBuffer<T>::getValue(uint16_t index) const {
    return values[index];
}

template<typename T>
T CircularBuffer<T>::read(int index) const {
    auto deltaIndex = divisorMod((this->index - 1) - index, size);
    return getValue(static_cast<uint16_t>(deltaIndex));
}

template<typename T>
int CircularBuffer<T>::divisorMod(int a, int b) {
    return (b + (a % b)) % b;
}

template
class CircularBuffer<uint8_t>;

template
class CircularBuffer<uint16_t>;

template
class CircularBuffer<uint32_t>;

template
class CircularBuffer<uint64_t>;

template
class CircularBuffer<float_t>;

template
class CircularBuffer<double_t>;

template
class CircularBuffer<short>;

template
class CircularBuffer<int>;

template
class CircularBuffer<long>;