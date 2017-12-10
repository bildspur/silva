//
// Created by Florian on 10.12.17.
//

#ifndef AUTORANGEFINDER_CIRCULARBUFFER_H
#define AUTORANGEFINDER_CIRCULARBUFFER_H


#include <cstdint>

template<typename T>
class CircularBuffer {
private:
    uint16_t size;
    uint16_t index = 0;

    T *values;

public:
    explicit CircularBuffer(uint16_t size);

    void write(uint16_t index, T value);

    void write(T value);

    uint16_t getSize() const;

    T getValue(uint16_t index) const;

    T read(int index) const;

    static int divisorMod(int a, int b);
};


#endif //AUTORANGEFINDER_CIRCULARBUFFER_H
