#ifndef MOVEMENTSERVICE_H
#define MOVEMENTSERVICE_H

#include "elt_robot.h"


class MovementService
{
public:
    MovementService();
    bool robotRun(ELT_CTX ctx);
    bool robotPause(ELT_CTX ctx);
    bool robotStop(ELT_CTX ctx);
    bool robotJointMove(ELT_CTX ctx, elt_robot_pos target_pos_array, double speed);
    bool robotLineMove(ELT_CTX ctx, elt_robot_pos target_pos_array, double speed);
    bool robotArcMove(ELT_CTX ctx, elt_robot_pos middle_target_pos_array, elt_robot_pos target_pos_array,double speed);
    bool robotRotateMove(ELT_CTX ctx, elt_robot_pos target_pos_array, double speed);
    bool robotSetWayPointMaxJointSpeed(ELT_CTX ctx, double speed);
    bool robotSetWayPointMaxLineSpeed(ELT_CTX ctx, double speed);
    bool robotSetWayPointMaxRotateSpeed(ELT_CTX ctx, double speed);
    bool robotAddWaypoint(ELT_CTX ctx,elt_robot_pos pos);
};

#endif // MOVEMENTSERVICE_H
