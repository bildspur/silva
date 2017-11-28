//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_EASINGFLOAT_H
#define SILVA_EASINGFLOAT_H


class EasingFloat {
private:
    float value;
    float target;
    float easing;

public:
    explicit EasingFloat(float value = 0.0, float easing = 0.1);

    void update();

    float get();

     void set(float value);

    float setEasing(float easing);
};


#endif //SILVA_EASINGFLOAT_H
