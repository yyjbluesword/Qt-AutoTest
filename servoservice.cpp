#include "servoservice.h"
#include <QDebug>

#define PRINTERR qDebug()<<"err.code = "<<err.code<<" err.err_msg = "<<err.err_msg;

ServoService::ServoService()
{

}
/**
 * @brief 获取机械臂伺服状态
 * @param ctx 上下文
 * @return 成功或失败
 */
bool ServoService::getServoStatus(ELT_CTX ctx)
{
    int ret, status;
    elt_error err;
    ret = elt_get_servo_status(ctx, &status, &err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_servo_status success.";
        qDebug()<<"Servo status = "<<status;
        return true;
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_servo_status failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_servo_status error.";
        PRINTERR;
    }else{
        qDebug()<<"elt_get_servo_status other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
/**
 * @brief 获取机械臂上下电状态
 * @param ctx 上下文
 * @return 成功与失败
 */
bool ServoService::getMotorStatus(ELT_CTX ctx)
{
    int ret, status;
    elt_error err;
    ret = elt_get_motor_status(ctx, &status, &err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_motor_status success.";
        qDebug()<<"Motor status = "<<status;
        return true;
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_motor_status failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_motor_status error.";
        PRINTERR;
    }else{
        qDebug()<<"elt_get_motor_status other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
/**
 * @brief 设置伺服使能状态
 * @param ctx 上下文
 * @return 成功或失败
 */
bool ServoService::setServoStatus(ELT_CTX ctx, int status)
{
    int ret;
    elt_error err;
    ret = elt_set_servo_status(ctx, status, &err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_set_servo_status success.";
        return true;
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_set_servo_status failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_set_servo_status error.";
        PRINTERR;
    }else{
        qDebug()<<"elt_set_servo_status other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
/**
 * @brief 同步伺服编码器数据
 * @param ctx 上下文
 * @return 成功或失败
 */
bool ServoService::syncMotorStatus(ELT_CTX ctx)
{
    int ret;
    elt_error err;
    ret = elt_sync_motor_status(ctx, &err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_sync_motor_status success.";
        return true;
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_sync_motor_status failure.";
        PRINTERR;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_sync_motor_status error.";
        PRINTERR;
    }else{
        qDebug()<<"elt_sync_motor_status other status.";
        PRINTERR;
        qDebug()<<"ret = "<<ret;
    }
    return false;
}
