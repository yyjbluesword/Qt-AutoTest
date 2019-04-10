#include "sdkkinematic.h"
#include <QDebug>
#define PRINTERR qDebug()<<"err.code = "<<err.code<<" err.err_msg = "<<err.err_msg;
/**
 * @brief 构造函数
 */
SDKKinematic::SDKKinematic()
{

}
/**
 * @brief 析构函数
 */
SDKKinematic::~SDKKinematic()
{

}
/**
 * @brief 逆解函数
 * @param ctx 上下文
 * @return
 */
bool SDKKinematic::inverseKinematic(ELT_CTX ctx)
{
    elt_robot_pos response_pos_array,pos_array;
    elt_robot_pose pose_array;
    elt_error err;
    //获取机器人当前位姿
    int ret = elt_get_robot_pose(ctx,pose_array,&err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_robot_pose success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_robot_pose failed.";
        PRINTERR;
        return false;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_robot_pose error.";
        PRINTERR;
        return false;
    }else{
        qDebug()<<"elt_get_robot_pose other status.";
        PRINTERR;
        return false;
    }
    //获取机器人当前关节角度
    ret = elt_get_robot_pos(ctx,pos_array,&err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_robot_pos success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_robot_pos failed.";
        PRINTERR;
        return false;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_robot_pos error.";
        PRINTERR;
        return false;
    }else{
        qDebug()<<"elt_get_robot_pos other status.";
        PRINTERR;
        return false;
    }
    //逆解变换位姿到关节角度
    ret = elt_inverse_kinematic(ctx,pose_array,response_pos_array,&err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_inverse_kinematic success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_inverse_kinematic failed.";
        PRINTERR;
        return false;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_inverse_kinematic error.";
        PRINTERR;
        return false;
    }else{
        qDebug()<<"elt_inverse_kinematic other status.";
        PRINTERR;
        return false;
    }
    //比较变换前后值数据
    bool flag = true;
    for(int i = 0; i < AXIS_COUNT; i++){
        if(abs(response_pos_array[i] - pos_array[i]) > 0.01)
            flag = false;
    }
    if(!flag){
        qDebug()<<"inverseKinematic calicate error.";
        qDebug()<<"realData = "<<pos_array[0]<<pos_array[1]<<pos_array[2]<<pos_array[3]<<pos_array[4]<<pos_array[5]<<pos_array[6]<<pos_array[7];
        qDebug()<<"respData = "<<response_pos_array[0]<<response_pos_array[1]<<response_pos_array[2]<<response_pos_array[3]<<response_pos_array[4]<<response_pos_array[5]<<response_pos_array[6]<<response_pos_array[7];
        return false;
    }else{
        qDebug()<<"inverseKinematic calicate success";
        qDebug()<<"realData = "<<pos_array[0]<<pos_array[1]<<pos_array[2]<<pos_array[3]<<pos_array[4]<<pos_array[5]<<pos_array[6]<<pos_array[7];
        qDebug()<<"respData = "<<response_pos_array[0]<<response_pos_array[1]<<response_pos_array[2]<<response_pos_array[3]<<response_pos_array[4]<<response_pos_array[5]<<response_pos_array[6]<<response_pos_array[7];
    }
    return true;
}
/**
 * @brief 正解函数
 * @param ctx 上下文
 * @return
 */
bool SDKKinematic::positiveKinematic(ELT_CTX ctx)
{
    elt_robot_pos pos_array;
    elt_robot_pose response_pose_array,pose_array;
    elt_error err;
    //获取机器人当前位姿
    int ret = elt_get_robot_pose(ctx,pose_array,&err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_robot_pose success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_robot_pose failed.";
        PRINTERR;
        return false;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_robot_pose error.";
        PRINTERR;
        return false;
    }else{
        qDebug()<<"elt_get_robot_pose other status.";
        PRINTERR;
        return false;
    }
    //获取机器人当前关节角度
    ret = elt_get_robot_pos(ctx,pos_array,&err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_robot_pos success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_robot_pos failed.";
        PRINTERR;
        return false;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_robot_pos error.";
        PRINTERR;
        return false;
    }else{
        qDebug()<<"elt_get_robot_pos other status.";
        PRINTERR;
        return false;
    }
    //正解变换位姿到直角角度
    ret = elt_positive_kinematic(ctx, pos_array, response_pose_array, &err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_positive_kinematic success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_positive_kinematic failed.";
        PRINTERR;
        return false;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_positive_kinematic error.";
        PRINTERR;
        return false;
    }else{
        qDebug()<<"elt_positive_kinematic other status.";
        PRINTERR;
        return false;
    }
    //比较变换前后值数据
    bool flag = true;
    for(int i = 0; i < ROBOT_POSE_SIZE; i++){
        if(abs(response_pose_array[i] - pose_array[i]) > 0.01)
            flag = false;
    }
    if(!flag){
        qDebug()<<"positiveKinematic calicate error.";
        qDebug()<<"realData = "<<pose_array[0]<<pose_array[1]<<pose_array[2]
               <<pose_array[3]<<pose_array[4]<<pose_array[5];
        qDebug()<<"respData = "<<response_pose_array[0]<<response_pose_array[1]<<response_pose_array[2]
               <<response_pose_array[3]<<response_pose_array[4]<<response_pose_array[5];
        return false;
    }else{
        qDebug()<<"positiveKinematic calicate success";
        qDebug()<<"realData = "<<pose_array[0]<<pose_array[1]<<pose_array[2]
               <<pose_array[3]<<pose_array[4]<<pose_array[5];
        qDebug()<<"respData = "<<response_pose_array[0]<<response_pose_array[1]<<response_pose_array[2]
               <<response_pose_array[3]<<response_pose_array[4]<<response_pose_array[5];
    }
    return true;
}
/**
 * @brief 转换用户坐标基坐标测试
 * @param ctx 上下文
 * @param userNum 转换用户坐标号
 * @return
 */
bool SDKKinematic::convertUserBase(ELT_CTX ctx, int userNum)
{
    elt_robot_pose response_pose_array,pose_array,pose1_array;
    elt_error err;
    //获取机器人当前位姿
    int ret = elt_get_robot_pose(ctx,pose_array,&err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_get_robot_pose success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_get_robot_pose failed.";
        PRINTERR;
        return false;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_get_robot_pose error.";
        PRINTERR;
        return false;
    }else{
        qDebug()<<"elt_get_robot_pose other status.";
        PRINTERR;
        return false;
    }
    //基坐标变换到用户坐标
    ret = elt_base2user(ctx,pose_array,userNum,response_pose_array,&err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_base2user success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_base2user failed.";
        PRINTERR;
        return false;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_base2user error.";
        PRINTERR;
        return false;
    }else{
        qDebug()<<"elt_base2user other status.";
        PRINTERR;
        return false;
    }
    //用户坐标变换到基坐标测试
    ret = elt_user2base(ctx,response_pose_array,userNum,pose1_array,&err);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_user2base success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_user2base failed.";
        PRINTERR;
        return false;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_user2base error.";
        PRINTERR;
        return false;
    }else{
        qDebug()<<"elt_user2base other status.";
        PRINTERR;
        return false;
    }
    //比较变换前后值数据
    bool flag = true;
    for(int i = 0; i < ROBOT_POSE_SIZE; i++){
        if(abs(pose_array[i] - pose1_array[i]) > 0.01)
            flag = false;
    }
    if(!flag){
        qDebug()<<"convertUserBase calicate error.";
        qDebug()<<"realData = "<<pose_array[0]<<pose_array[1]<<pose_array[2]
               <<pose_array[3]<<pose_array[4]<<pose_array[5];
        qDebug()<<"respData = "<<pose1_array[0]<<pose1_array[1]<<pose1_array[2]
               <<pose1_array[3]<<pose1_array[4]<<pose1_array[5];
        return false;
    }else{
        qDebug()<<"convertUserBase calicate success";
        qDebug()<<"realData = "<<pose_array[0]<<pose_array[1]<<pose_array[2]
               <<pose_array[3]<<pose_array[4]<<pose_array[5];
        qDebug()<<"respData = "<<pose1_array[0]<<pose1_array[1]<<pose1_array[2]
               <<pose1_array[3]<<pose1_array[4]<<pose1_array[5];
    }
    return true;
}
