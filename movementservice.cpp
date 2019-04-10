#include "movementservice.h"
#include <QDebug>

#define PRINTERR qDebug()<<"err.code = "<<err.code<<" err.err_msg = "<<err.err_msg;

MovementService::MovementService()
{

}

/**
 * @brief 运行机器人测试
 * @param ctx 上下文
 * @return 成功或失败
 */
bool MovementService::robotRun(ELT_CTX ctx)
{
    int ret;
    elt_error err;
    ret = elt_run(ctx, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_run failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_run error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_run success.";
        return true;
    }else{
        qDebug()<<"elt_run other status.";
        PRINTERR;
    }
    return false;
}
/**
 * @brief 机器人暂停测试
 * @param ctx 上下文
 * @return 成功或失败
 */
bool MovementService::robotPause(ELT_CTX ctx)
{
    int ret;
    elt_error err;
    ret = elt_pause(ctx,&err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_pause failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_pause error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_pause success.";
        return true;
    }else{
        qDebug()<<"elt_pause other status.";
        PRINTERR;
    }
    return false;
}
/**
 * @brief 停止机器人测试
 * @param ctx 上下文
 * @return 成功或失败
 */
bool MovementService::robotStop(ELT_CTX ctx)
{
    int ret;
    elt_error err;
    ret = elt_stop(ctx,&err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_stop failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_stop error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_stop success.";
        return true;
    }else{
        qDebug()<<"elt_stop other status.";
        PRINTERR;
    }
    return false;
}

/**
 * @brief 机器人关节运动
 * @param target_pos_array
 * @param speed
 * @return
 */
bool MovementService::robotJointMove(ELT_CTX ctx, elt_robot_pos target_pos_array, double speed)
{
    int ret;
    elt_error err;
    ret = elt_joint_move(ctx, target_pos_array, speed, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_joint_move failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_joint_move error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_joint_move success.";
        return true;
    }else{
        qDebug()<<"elt_joint_move other status.";
        PRINTERR;
    }
    return false;
}
/**
 * @brief 机器人直线运动测试
 * @param ctx 上下文
 * @param target_pos_array 目标点
 * @param speed 运行速度
 * @return 成功或失败
 */
bool MovementService::robotLineMove(ELT_CTX ctx, elt_robot_pos target_pos_array, double speed)
{
    int ret;
    elt_error err;
    ret = elt_line_move(ctx,target_pos_array, speed, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_line_move failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_line_move error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_line_move success.";
        return true;
    }else{
        qDebug()<<"elt_line_move other status.";
        PRINTERR;
    }
    return false;
}

/**
 * @brief 机器人圆弧运动测试
 * @param ctx 上下文
 * @param middle_target_pos_array 中间点
 * @param target_pos_array 结束点
 * @param speed 运行速度 mm/s
 * @return 成功与失败
 */
bool MovementService::robotArcMove(ELT_CTX ctx, elt_robot_pos middle_target_pos_array, elt_robot_pos target_pos_array, double speed)
{
    int ret;
    elt_error err;
    ret = elt_arc_move(ctx, middle_target_pos_array, target_pos_array, speed, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_arc_move failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_arc_move error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_arc_move success.";
        return true;
    }else{
        qDebug()<<"elt_arc_move other status.";
        PRINTERR;
    }
    return false;
}
/**
 * @brief 机器人旋转运动
 * @param ctx 上下文
 * @param target_pos_array 目标点
 * @param speed 运行速度
 * @return 成功与失败
 */
bool MovementService::robotRotateMove(ELT_CTX ctx, elt_robot_pos target_pos_array, double speed)
{
    int ret;
    elt_error err;
    ret = elt_rotate_move(ctx, target_pos_array, speed, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_rotate_move failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_rotate_move error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_rotate_move success.";
        return true;
    }else{
        qDebug()<<"elt_rotate_move other status.";
        PRINTERR;
    }
    return false;
}
/**
 * @brief 设置路点运动时最大关节速度
 * @param ctx
 * @param speed
 * @return
 */
bool MovementService::robotSetWayPointMaxJointSpeed(ELT_CTX ctx, double speed)
{
    int ret;
    elt_error err;
    ret = elt_set_waypoint_max_joint_speed(ctx, speed, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_set_waypoint_max_joint_speed failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_set_waypoint_max_joint_speed error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_set_waypoint_max_joint_speed success.";
        return true;
    }else{
        qDebug()<<"elt_set_waypoint_max_joint_speed other status.";
        PRINTERR;
    }
    return false;
}
/**
 * @brief 设置路点运动最大直线速度
 * @param ctx 上下文
 * @param speed 速度
 * @return 设置成功与失败
 */
bool MovementService::robotSetWayPointMaxLineSpeed(ELT_CTX ctx, double speed)
{
    int ret;
    elt_error err;
    ret = elt_set_waypoint_max_line_speed(ctx, speed, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_set_waypoint_max_line_speed failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_set_waypoint_max_line_speed error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_set_waypoint_max_line_speed success.";
        return true;
    }else{
        qDebug()<<"elt_set_waypoint_max_line_speed other status.";
        PRINTERR;
    }
    return false;
}
/**
 * @brief 设置路点运动旋转角最大速度
 * @param ctx 上下文
 * @param speed 速度
 * @return 设置成功与失败
 */
bool MovementService::robotSetWayPointMaxRotateSpeed(ELT_CTX ctx, double speed)
{
    int ret;
    elt_error err;
    ret = elt_set_waypoint_max_rotate_speed(ctx, speed, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_set_waypoint_max_rotate_speed failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_set_waypoint_max_rotate_speed error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_set_waypoint_max_rotate_speed success.";
        return true;
    }else{
        qDebug()<<"elt_set_waypoint_max_rotate_speed other status.";
        PRINTERR;
    }
    return false;
}
/**
 * @brief 添加路点功能测试
 * @param ctx 上下文
 * @param pos 位置信息
 * @return 添加成功与失败
 */
bool MovementService::robotAddWaypoint(ELT_CTX ctx, elt_robot_pos pos)
{
    int ret;
    elt_error err;
    ret = elt_add_waypoint(ctx, pos, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_add_waypoint failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_add_waypoint error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_add_waypoint success.";
        return true;
    }else{
        qDebug()<<"elt_add_waypoint other status.";
        PRINTERR;
    }
    return false;
}
