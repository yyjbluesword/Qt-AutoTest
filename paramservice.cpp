#include "paramservice.h"
#include <QDebug>

#define PRINTERR qDebug()<<"err.code = "<<err.code<<" err.err_msg = "<<err.err_msg;

ParamService::ParamService()
{

}
/**
 * @brief 获取机器人当前状态测试
 * @param ctx 上下文
 * @return -1失败，当前状态
 */
int ParamService::getRobotStatus(ELT_CTX ctx)
{
    int ret, state;
    elt_error err;
    ret = elt_get_robot_state(ctx, &state, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_robot_state failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_robot_state error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_robot_state success.";
        //qDebug()<<"state = "<<state;
        return state;
    }else{
        qDebug()<<"elt_get_robot_state other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return -1;
}
/**
 * @brief 获取机器人模式测试
 * @param ctx 上下文
 * @return 成功或失败
 */
bool ParamService::getRobotMode(ELT_CTX ctx)
{
    int ret, mode;
    elt_error err;
    ret = elt_get_robot_mode(ctx, &mode, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_robot_mode failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_robot_mode error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_robot_state success.";
        //qDebug()<<"mode = "<<mode;
        return true;
    }else{
        qDebug()<<"elt_get_robot_mode other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
/**
 * @brief 获取机器人位置信息测试
 * @param ctx 上下文
 * @return 成功或失败
 */
bool ParamService::getRobotPos(ELT_CTX ctx)
{
    int ret;
    elt_robot_pos pos_array;
    elt_error err;
    ret = elt_get_robot_pos(ctx, pos_array, &err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_robot_pos success.";
        qDebug()<<pos_array[0]<<pos_array[1]<<pos_array[2]<<pos_array[3]
                <<pos_array[4]<<pos_array[5]<<pos_array[6]<<pos_array[7];
        return true;
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_robot_pos failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_robot_pos error.";
        PRINTERR;
    }else{
        qDebug()<<"elt_get_robot_pos other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
/**
 * @brief 获取机器人位姿信息测试
 * @param ctx
 * @return
 */
bool ParamService::getRobotPose(ELT_CTX ctx)
{
    int ret;
    elt_robot_pose pose_array;
    elt_error err;
    ret = elt_get_robot_pose(ctx, pose_array, &err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_robot_pose success.";
        qDebug()<<pose_array[0]<<pose_array[1]<<pose_array[2]
                <<pose_array[3]<<pose_array[4]<<pose_array[5];
        return true;
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_robot_pose failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_robot_pose error.";
        PRINTERR;
    }else{
        qDebug()<<"elt_get_robot_pose other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
/**
 * @brief 获取马达速度测试
 * @param ctx 上下文
 * @return 成功或失败
 */
bool ParamService::getMotorSpeed(ELT_CTX ctx)
{
    int ret;
    elt_motor_speed speed_array;
    elt_error err;
    ret = elt_get_motor_speed(ctx, speed_array, &err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_motor_speed success.";
        qDebug()<<speed_array[0]<<speed_array[1]<<speed_array[2]<<speed_array[3]
                <<speed_array[4]<<speed_array[5]<<speed_array[6]<<speed_array[7];
        return true;
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_motor_speed failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_motor_speed error.";
        PRINTERR;
    }else{
        qDebug()<<"elt_get_motor_speed other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
/**
 * @brief 获取当前坐标系测试
 * @param ctx 上下文
 * @return 成功或失败
 */
bool ParamService::getCurrentCoord(ELT_CTX ctx)
{
    int ret, coord;
    elt_error err;
    ret = elt_get_current_coord(ctx, &coord, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_current_coord failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_current_coord error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_current_coord success.";
        qDebug()<<"coord = "<<coord;
        return true;
    }else{
        qDebug()<<"elt_get_current_coord other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
/**
 * @brief 获取当前循环模式测试
 * @param ctx 上下文
 * @return 成功或失败
 */
bool ParamService::getCycleMode(ELT_CTX ctx)
{
    int ret, mode;
    elt_error err;
    ret = elt_get_cycle_mode(ctx,&mode, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_cycle_mode failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_cycle_mode error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_cycle_mode success.";
        qDebug()<<"mode = "<<mode;
        return true;
    }else{
        qDebug()<<"elt_get_cycle_mode other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
/**
 * @brief 获取当前作业号行
 * @param ctx 上下文
 * @return 成功或失败
 */
bool ParamService::getCurrentJobLine(ELT_CTX ctx)
{
    int ret, line_no;
    elt_error err;
    ret = elt_get_current_job_line(ctx, &line_no, &err);
    if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_current_job_line failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_current_job_line error.";
        PRINTERR;
    }else if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_current_job_line success.";
        qDebug()<<"line_no = "<<line_no;
        return true;
    }else{
        qDebug()<<"elt_get_current_job_line other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
/**
 * @brief 获取当前编码器值列表测试
 * @param ctx 上下文
 * @return 成功或失败
 */
bool ParamService::getCurrentEncode(ELT_CTX ctx)
{
    int ret;
    elt_robot_encode encode_array;
    elt_error err;
    ret = elt_get_current_encode(ctx, encode_array, &err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_current_encode success.";
        qDebug()<<encode_array[0]<<encode_array[1]<<encode_array[2]<<encode_array[3]
                <<encode_array[4]<<encode_array[5]<<encode_array[6]<<encode_array[7];
        return true;
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_current_encode failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_current_encode error.";
        PRINTERR;
    }else{
        qDebug()<<"elt_get_current_encode other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
/**
 * @brief 获取当前工具号
 * @param ctx 上下文
 * @return 成功或失败
 */
bool ParamService::getToolNum(ELT_CTX ctx)
{
    int ret, tool_num;
    elt_error err;
    ret = elt_get_tool_number(ctx, &tool_num, &err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_tool_number success.";
        qDebug()<<"tool_num = "<<tool_num;
        return true;
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_tool_num failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_tool_num error.";
        PRINTERR;
    }else{
        qDebug()<<"elt_get_tool_num other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
/**
 * @brief 获取机器人力矩信息
 * @param ctx 上下文
 * @return 成功或失败
 */
bool ParamService::getRobotTorques(ELT_CTX ctx)
{
    int ret;
    elt_robot_torques torques;
    elt_error err;
    ret = elt_get_robot_torques(ctx, torques, &err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_robot_torques success.";
        qDebug()<<torques[0]<<torques[1]<<torques[2]<<torques[3]
                <<torques[4]<<torques[5]<<torques[6]<<torques[7];
        return true;
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_robot_torques failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_robot_torques error.";
        PRINTERR;
    }else{
        qDebug()<<"elt_get_robot_torques other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
