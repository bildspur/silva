//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_OSCCONTROLLER_H
#define SILVA_OSCCONTROLLER_H


#include <controller/BaseController.h>

class OscController : public BaseController {
private:

public:
    void setup() override;
    void loop() override;
};


#endif //SILVA_OSCCONTROLLER_H
