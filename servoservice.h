#ifndef SERVOSERVICE_H
#define SERVOSERVICE_H
#include "elt_robot.h"

class ServoService
{
public:
    ServoService();
    bool getServoStatus(ELT_CTX ctx);
    bool getMotorStatus(ELT_CTX ctx);
    bool setServoStatus(ELT_CTX ctx, int value);
    bool syncMotorStatus(ELT_CTX ctx);
};

#endif // SERVOSERVICE_H
