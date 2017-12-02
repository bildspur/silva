//
// Created by Florian on 02.12.17.
//

#ifndef SILVA_HEARTBEAT_H
#define SILVA_HEARTBEAT_H


#include <functional>
#include <controller/BaseController.h>
#include <util/Timer.h>

class Heartbeat : public BaseController {
private:
    typedef std::function<void()> HeartbeatHandler;

    HeartbeatHandler onHeartbeatCallback;
    Timer *timer;

public:
    explicit Heartbeat(unsigned long waitTime);

    void onHeartbeat(HeartbeatHandler onHeartbeatCallback);

    void setup() override;

    void loop() override;

    void sendHeartbeat();
};


#endif //SILVA_HEARTBEAT_H
