#ifndef PARAMSERVICE_H
#define PARAMSERVICE_H
# include "elt_robot.h"


class ParamService
{
public:
    ParamService();
    int getRobotStatus(ELT_CTX ctx);
    bool getRobotMode(ELT_CTX ctx);
    bool getRobotPos(ELT_CTX ctx);
    bool getRobotPose(ELT_CTX ctx);
    bool getMotorSpeed(ELT_CTX ctx);
    bool getCurrentCoord(ELT_CTX ctx);
    bool getCycleMode(ELT_CTX ctx);
    bool getCurrentJobLine(ELT_CTX ctx);
    bool getCurrentEncode(ELT_CTX ctx);
    bool getToolNum(ELT_CTX ctx);
    bool getRobotTorques(ELT_CTX ctx);
};

#endif // PARAMSERVICE_H
