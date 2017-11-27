//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_NETWORKCONTROLLER_H
#define SILVA_NETWORKCONTROLLER_H


#include <controller/BaseController.h>

class NetworkController : public BaseController {
private:

public:
    void setup() override;
    void loop() override;
};


#endif //SILVA_NETWORKCONTROLLER_H
