//
// Created by Florian on 06.12.17.
//

#ifndef SILVA_FLOATUTIL_H
#define SILVA_FLOATUTIL_H


class FloatUtil {
protected:
    FloatUtil();

public:
    static float map(float value, float minIn, float maxIn, float minOut, float maxOut);
};


#endif //SILVA_FLOATUTIL_H
