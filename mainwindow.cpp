#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStringList>
#include <QFile>
#include "sdkcontext.h"
#include "sdkkinematic.h"
#include "ioservice.h"
#include "varservice.h"
#include "paramservice.h"
#include "movementservice.h"
#include "servoservice.h"

#define IP "192.168.1.200"
#define PORT 8055
#define PRINTERR qDebug()<<"err.code = "<<err.code<<" err.err_msg = "<<err.err_msg;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief 初始化上下文测试
 */
void MainWindow::on_pushButton_clicked()
{
    int ret ;
    ELT_CTX ctx;
    for(int i = 0 ; i < 10000; i++){
        ctx = elt_create_ctx(IP,PORT);
        if(NULL == ctx){
            qDebug()<<i<<"\telt_create_ctx failed.";
        }else{
            qDebug()<<i<<"\telt_create_ctx success.";
        }
        ret = elt_destroy_ctx(ctx);
        if(ELT_SUCCESS == ret){
            qDebug()<<i<<"\telt_destroy_ctx success.";
        }else if(ELT_FAILURE == ret){
            qDebug()<<i<<"\telt_destroy_ctx failed.";
        }else{
            qDebug()<<i<<"\telt_destroy_ctx other status.";
        }
    }
}

void MainWindow::on_loginTestButton_clicked()
{
    ELT_CTX ctx;
    int ret;
    for(int i = 0; i < 2; i++){
        ctx = elt_create_ctx(IP,PORT);
        if(NULL == ctx){
            qDebug()<<"elt_create_ctx failed.";
        }else{
            qDebug()<<"elt_create_ctx success.";
        }
        ret = elt_login(ctx);
        if(ELT_FAILURE == ret){
            qDebug()<<"elt_login failed."<<" ret = "<<ret;
        }else if(ELT_SUCCESS == ret){
            qDebug()<<"elt_login success."<<" ret = "<<ret;
        }else if(ELT_ERROR == ret){
            qDebug()<<"elt_login error."<<" ret = "<<ret;
        }else{
            qDebug()<<"elt_login other status"<<" ret = "<<ret;
        }
        Sleep(1000);
        ret = elt_logout(ctx);
        if(ELT_FAILURE == ret){
            qDebug()<<"elt_logout failed. ret = "<<ret;
        }else if(ELT_ERROR == ret){
            qDebug()<<"elt_logout error. ret = "<<ret;
        }else if(ELT_SUCCESS == ret){
            qDebug()<<"elt_logout success. ret = "<<ret;
        }else{
            qDebug()<<"elt_logout other status. ret = "<<ret;
        }
        Sleep(1000);
        ret = elt_destroy_ctx(ctx);
        if(ELT_FAILURE == ret){
            qDebug()<<"elt_destroy_ctx failed. ret = "<<ret;
        }else if(ELT_ERROR == ret){
            qDebug()<<"elt_destroy_ctx error. ret = "<<ret;
        }else if(ELT_SUCCESS == ret){
            qDebug()<<"elt_destroy_ctx success. ret = "<<ret;
        }else{
            qDebug()<<"elt_destroy_ctx other status. ret = "<<ret;
        }
    }
}

/**
 * @brief 获取机械臂伺服状态测试
 */
void MainWindow::on_loginTestButton_2_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    elt_error err;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ServoService servoService;
    int status = 0;
    for(int i = 0; i < 1000; i++){
        if(servoService.getServoStatus(ctx)){
            if(servoService.setServoStatus(ctx,status)){
                status = (status == 0)?1:0;
                Sleep(1000);
            }else
                return;
        }else
            return;
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test get and set servo state success.";
}

/**
 * @brief MainWindow::获取伺服上下电状态测试
 */
void MainWindow::on_ServoStatusTest_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    elt_error err;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ServoService servoService;
    int status = 0;
    for(int i = 0; i < 1000; i++){
        if(servoService.getMotorStatus(ctx)){
            if(servoService.syncMotorStatus(ctx)){
                Sleep(1000);
            }else
                return;
        }else
            return;
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test get and sync motor state success.";
}

/**
 * @brief 获取机器人状态测试
 */
void MainWindow::on_robotStatus_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    elt_error err;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    MovementService movementService;
    for(int i = 0; i < 1000; i++){
        if(paramService.getRobotStatus(ctx) != -1){
            (i%2 == 0)? movementService.robotPause(ctx) : movementService.robotRun(ctx);
            Sleep(1000);
        }else{
            return;
        }
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test get robot state success.";
}

/**
 * @brief 设置路点运动时最大关节速度
 */
void MainWindow::on_wayPointMaxJointSpeed_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    MovementService movementService;
    double dspeed = ui->wayPointMaxJointSpeedText->text().toDouble();
    qDebug()<<dspeed;
    if(!movementService.robotSetWayPointMaxJointSpeed(ctx,dspeed)){
        qDebug()<<"set Way Point Max Joint Speed failed.";
        return;
    }else{
        qDebug()<<"set Way Point Max Joint Speed success.";
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test set way point max joint speed success.";
}

/**
 * @brief 添加路点信息测试
 */
void MainWindow::on_addWayPoint_clicked()
{
    static int flag = 1;
    flag = (flag == 0) ? 1: 0;
    ELT_CTX ctx;
    int ret;
    elt_error err;
    ctx = elt_create_ctx(IP,PORT);
    if(NULL == ctx){
        qDebug()<<"elt_create_ctx failed.";
        return;
    }else{
        qDebug()<<"elt_create_ctx success.";
    }
    ret = elt_login(ctx);
    if(ELT_SUCCESS == ret){
        qDebug()<<"elt_login success.";
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_login error.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_login failure.";
    }else{
        qDebug()<<"elt_login other status. ret = "<<ret;
    }
    ////////////////////////////////////////////////////////
    /// \brief wayPointArray
    QFile file("f://pointData.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Open file failed.";
        return;
    }
    qDebug()<<"Open File success.";
    QTextStream txtInput(&file);
    QString lineStr;
    elt_robot_pos pos;
    QString tmp;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        QStringList list = lineStr.split(",");
        if(list.length() == 8){
            for(int i = 0;i < 8; i++)
                pos[i] = list.at(i).toDouble();
            qDebug()<<pos;
            ret = elt_add_waypoint(ctx,pos,&err);
            if(ELT_SUCCESS == ret){
                qDebug()<<"elt_add_waypoint success.";
            }else if(ELT_FAILURE == ret){
                qDebug()<<"elt_add_waypoint failed.";
                PRINTERR;
                break;
            }else if(ELT_ERROR == ret){
                qDebug()<<"elt_add_waypoint err.";
                PRINTERR;
                break;
            }else{
                qDebug()<<"elt_add_waypoint other status.";
                break;
            }
        }
    }
    file.close();
    ////////////////////////////////////////////////////////
    ret = elt_logout(ctx);
    if(ELT_SUCCESS == ret){
        qDebug()<<"elt_logout success.";
    }else if(ELT_ERROR ==  ret){
        qDebug()<<"elt_logout error.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_logout failure.";
    }else{
        qDebug()<<"elt_logout other status. ret = "<<ret;
    }
    ret = elt_destroy_ctx(ctx);
    if(ELT_SUCCESS == ret){
        qDebug()<<"elt_destroy_ctx success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_destroy_ctx failure.";
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_destroy_ctx error.";
    }else{
        qDebug()<<"elt_destroy_ctx other status.";
    }
}

/**
 * @brief 轨迹运动测试
 */
void MainWindow::on_trackMove_clicked()
{
    static int flag = 1;
    flag = (flag == 0) ? 1: 0;
    ELT_CTX ctx;
    int ret;
    elt_error err;
    ctx = elt_create_ctx(IP,PORT);
    if(NULL == ctx){
        qDebug()<<"elt_create_ctx failed.";
        return;
    }else{
        qDebug()<<"elt_create_ctx success.";
    }
    ret = elt_login(ctx);
    if(ELT_SUCCESS == ret){
        qDebug()<<"elt_login success.";
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_login error.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_login failure.";
    }else{
        qDebug()<<"elt_login other status. ret = "<<ret;
    }
    ////////////////////////////////////////////////////////
    int iMoveType,iPL;
    iMoveType = ui->moveTypeText->text().toInt();
    iPL = ui->plValueText->text().toInt();
    ret = elt_track_move(ctx,iMoveType,iPL,&err);
    if(ELT_SUCCESS == ret){
        qDebug()<<"elt_track_move success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_track_move failed.";
        PRINTERR;
        return;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_track_move err.";
        PRINTERR;
        return;
    }else{
        qDebug()<<"elt_track_move other status.";
        return;
    }
    ////////////////////////////////////////////////////////
    ret = elt_logout(ctx);
    if(ELT_SUCCESS == ret){
        qDebug()<<"elt_logout success.";
    }else if(ELT_ERROR ==  ret){
        qDebug()<<"elt_logout error.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_logout failure.";
    }else{
        qDebug()<<"elt_logout other status. ret = "<<ret;
    }
    ret = elt_destroy_ctx(ctx);
    if(ELT_SUCCESS == ret){
        qDebug()<<"elt_destroy_ctx success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_destroy_ctx failure.";
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_destroy_ctx error.";
    }else{
        qDebug()<<"elt_destroy_ctx other status.";
    }
}

/**
 * @brief 清除路点功能测试
 */
void MainWindow::on_clearWayPoint_clicked()
{
    static int flag = 1;
    flag = (flag == 0) ? 1: 0;
    ELT_CTX ctx;
    int ret;
    elt_error err;
    ctx = elt_create_ctx(IP,PORT);
    if(NULL == ctx){
        qDebug()<<"elt_create_ctx failed.";
        return;
    }else{
        qDebug()<<"elt_create_ctx success.";
    }
    ret = elt_login(ctx);
    if(ELT_SUCCESS == ret){
        qDebug()<<"elt_login success.";
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_login error.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_login failure.";
    }else{
        qDebug()<<"elt_login other status. ret = "<<ret;
    }
    ////////////////////////////////////////////////////////
    ret = elt_clear_waypoint(ctx,&err);
    if(ELT_SUCCESS == ret){
        qDebug()<<"elt_clear_waypoint success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_clear_waypoint failed.";
        PRINTERR;
        return;
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_clear_waypoint err.";
        PRINTERR;
        return;
    }else{
        qDebug()<<"elt_clear_waypoint other status.";
        return;
    }
    ////////////////////////////////////////////////////////
    ret = elt_logout(ctx);
    if(ELT_SUCCESS == ret){
        qDebug()<<"elt_logout success.";
    }else if(ELT_ERROR ==  ret){
        qDebug()<<"elt_logout error.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_logout failure.";
    }else{
        qDebug()<<"elt_logout other status. ret = "<<ret;
    }
    ret = elt_destroy_ctx(ctx);
    if(ELT_SUCCESS == ret){
        qDebug()<<"elt_destroy_ctx success.";
    }else if(ELT_FAILURE == ret){
        qDebug()<<"elt_destroy_ctx failure.";
    }else if(ELT_ERROR == ret){
        qDebug()<<"elt_destroy_ctx error.";
    }else{
        qDebug()<<"elt_destroy_ctx other status.";
    }
}

/**
 * @brief 获取机器人当前位置信息测试
 */
void MainWindow::on_getRobotPos_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    for(int i = 0; i < 1000; i++){
        if(paramService.getRobotPos(ctx)){
            Sleep(1000);
        }else{
            qDebug()<<"test get robot pos failed.";
            return;
        }
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test get robot pos success.";
}

/**
 * @brief 获取机器人当前位姿信息测试
 */
void MainWindow::on_getRobotPose_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    for(int i = 0; i < 1000; i++){
        if(paramService.getRobotPose(ctx)){
            Sleep(500);
        }else{
            qDebug()<<"test get robot pose failed.";
            return;
        }
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test get robot pose success.";
}

/**
 * @brief 获取机器人马达速度测试
 */
void MainWindow::on_getMotorSpeed_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    for(int i = 0; i < 1000; i++){
        if(paramService.getMotorSpeed(ctx)){
            Sleep(500);
        }else{
            qDebug()<<"test get motor speed failed.";
            return;
        }
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test get robot pose success.";
}

void MainWindow::on_getCurrentCoord_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    for(int i = 0; i < 1000; i++){
        if(paramService.getCurrentCoord(ctx)){
            Sleep(500);
        }else{
            qDebug()<<"test get current coord failed.";
            return;
        }
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test get current coord success.";
}

void MainWindow::on_getCycleMode_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    for(int i = 0; i < 1000; i++){
        if(paramService.getCycleMode(ctx)){
            Sleep(500);
        }else{
            qDebug()<<"test get cycle mode failed.";
            return;
        }
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test get current coord success.";
}

/**
 * @brief 获取机器人当前作业运行号测试
 */

void MainWindow::on_getCurrentJobLine_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    for(int i = 0; i < 1000; i++){
        if(paramService.getCurrentJobLine(ctx)){
            Sleep(500);
        }else{
            qDebug()<<"test get current job line failed.";
            return;
        }
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test get current job line success.";
}

/**
 * @brief 获取机器人当前编码器值列表测试
 */
void MainWindow::on_getCurrentEncode_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    for(int i = 0; i < 1000; i++){
        if(paramService.getCurrentEncode(ctx)){
            Sleep(500);
        }else{
            qDebug()<<"test get current encode failed.";
            return;
        }
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test get current encode success.";
}

/**
 * @brief 获取机器人当前工具号测试
 */
void MainWindow::on_getToolNum_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    for(int i = 0; i < 1000; i++){
        if(paramService.getToolNum(ctx)){
            Sleep(500);
        }else{
            qDebug()<<"test get tool num failed.";
            return;
        }
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test get tool num success.";
}

/**
 * @brief 获取机器人当前力矩信息测试
 */
void MainWindow::on_getRobotTorques_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    for(int i = 0; i < 1000; i++){
        if(paramService.getRobotTorques(ctx)){
            Sleep(500);
        }else{
            qDebug()<<"test get robot torques failed.";
            return;
        }
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test get robot torques success.";
}

void MainWindow::on_getRobotMode_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    MovementService movementService;
    for(int i = 0; i < 1000; i++){
        if(paramService.getRobotMode(ctx)){
            Sleep(1000);
        }else{
            qDebug()<<"test get robot mode failed.";
            return;
        }
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test get robot mode success.";
}

/**
 * @brief 关节运动测试
 */
void MainWindow::on_jointMove_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    elt_error err;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ServoService servoService;
    MovementService movementService;
    ParamService paramService;
    //打开伺服
    if(!servoService.setServoStatus(ctx,1))
        return;
    Sleep(1000);
    double  djointMoveSpeed = ui->jonitMoveSpeedValue->text().toDouble();
    QFile file("f://sdkJointMove.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Open file failed.";
        return;
    }
    qDebug()<<"Open File success.";
    QTextStream txtInput(&file);
    QString lineStr;
    elt_robot_pos pos;
    QString tmp;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        QStringList list = lineStr.split(",");
        if(list.length() == 8){
            for(int i = 0;i < 8; i++)
                pos[i] = list.at(i).toDouble();
            if(!movementService.robotJointMove(ctx,pos,djointMoveSpeed)){
                qDebug()<<"robotJointMove failed.";
                return;
            }
            //elt_joint_move(ctx,pos,djointMoveSpeed,&err);
            int state;
            while(1){
                Sleep(300);
                state = paramService.getRobotStatus(ctx);
                if(state == -1)
                    goto error;
                if(state == 0)
                    break;
            }
        }
    }
    error:
    file.close();
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test elt_joint_move success.";
}

void MainWindow::on_lineMove_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    elt_error err;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ServoService servoService;
    MovementService movementService;
    ParamService paramService;
    //打开伺服
    if(!servoService.setServoStatus(ctx,1))
        return;
    Sleep(1000);
    double  djointMoveSpeed = ui->lineMoveSpeedValue->text().toDouble();
    QFile file("f://sdkLineMove.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Open file failed.";
        return;
    }
    qDebug()<<"Open File success.";
    QTextStream txtInput(&file);
    QString lineStr;
    elt_robot_pos pos;
    QString tmp;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        QStringList list = lineStr.split(",");
        if(list.length() == 8){
            for(int i = 0;i < 8; i++)
                pos[i] = list.at(i).toDouble();
            if(!movementService.robotLineMove(ctx,pos,djointMoveSpeed)){
                qDebug()<<"robotLineMove failed.";
                return;
            }
            int state;
            while(1){
                Sleep(300);
                state = paramService.getRobotStatus(ctx);
                if(state == -1)
                    goto error;
                if(state == 0)
                    break;
            }
        }
    }
    error:
    file.close();
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test elt_line_move success.";
}

/**
 * @brief 圆弧运动测试
 */
void MainWindow::on_arcMove_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    elt_error err;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ServoService servoService;
    MovementService movementService;
    ParamService paramService;
    //打开伺服
    if(!servoService.setServoStatus(ctx,1))
        return;
    Sleep(1000);
    double  darcMoveSpeed = ui->arcMoveSpeedValue->text().toDouble();
    QFile file("f://sdkArcMove.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Open file failed.";
        return;
    }
    qDebug()<<"Open File success.";
    QTextStream txtInput(&file);
    QString lineStr;
    elt_robot_pos pos[4];
    QString tmp;
    int curNum = 0;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        QStringList list = lineStr.split(",");
        if(list.length() == 8){
            for(int i = 0;i < 8; i++)
                pos[curNum][i] = list.at(i).toDouble();
            curNum++;
        }
    }
    file.close();
    if(!movementService.robotJointMove(ctx,pos[0],20))
        return;
    while(1){
        Sleep(300);
        int state = paramService.getRobotStatus(ctx);
        if(state == -1)
            return;
        if(state == 0)
            break;
    }
    if(!movementService.robotArcMove(ctx, pos[1], pos[2],darcMoveSpeed))
        return;
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test elt_arc_move success.";
}

/**
 * @brief 旋转运动测试
 */
void MainWindow::on_rotateMove_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    elt_error err;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ServoService servoService;
    MovementService movementService;
    ParamService paramService;
    //打开伺服
    if(!servoService.setServoStatus(ctx,1))
        return;
    Sleep(1000);
    double  drotateMoveSpeed = ui->rotateMoveSpeedValue->text().toDouble();
    QFile file("f://sdkRotateMove.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Open file failed.";
        return;
    }
    qDebug()<<"Open File success.";
    QTextStream txtInput(&file);
    QString lineStr;
    elt_robot_pos pos[2];
    QString tmp;
    int curNum = 0;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        QStringList list = lineStr.split(",");
        if(list.length() == 8){
            for(int i = 0;i < 8; i++)
                pos[curNum][i] = list.at(i).toDouble();
            curNum++;
            if(curNum > 1)
                break;
        }
    }
    file.close();
    if(!movementService.robotJointMove(ctx,pos[0],20))
        return;
    while(1){
        Sleep(300);
        int state = paramService.getRobotStatus(ctx);
        if(state == -1)
            return;
        if(state == 0)
            break;
    }
    if(!movementService.robotRotateMove(ctx,pos[1],drotateMoveSpeed));
        return;
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test elt_arc_move success.";
}

void MainWindow::on_wayPointMaxLineSpeed_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    MovementService movementService;
    double dspeed = ui->wayPointMaxJointSpeedText->text().toDouble();
    qDebug()<<dspeed;
    if(!movementService.robotSetWayPointMaxLineSpeed(ctx,dspeed)){
        qDebug()<<"set Way Point Max Line Speed failed.";
        return;
    }else{
        qDebug()<<"set Way Point Max Line Speed success.";
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test set way point max Line speed success.";
}

void MainWindow::on_wayPointMaxLineSpeed_2_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    ParamService paramService;
    MovementService movementService;
    double dspeed = ui->wayPointMaxJointSpeedText->text().toDouble();
    qDebug()<<dspeed;
    if(!movementService.robotSetWayPointMaxRotateSpeed(ctx,dspeed)){
        qDebug()<<"set Way Point Max Rotate Speed failed.";
        return;
    }else{
        qDebug()<<"set Way Point Max Rotate Speed success.";
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test set way point max Rotate speed success.";
}

/**
 * @brief 停止机器人测试
 */
void MainWindow::on_stopRobot_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    MovementService movementService;
    if(!movementService.robotStop(ctx))
            return;
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test set way point max joint speed success.";
}
/**
 * @brief 运行机器人测试
 */
void MainWindow::on_runRobot_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    MovementService movementService;
    for(int i = 0; i < 100; i++){
        if(movementService.robotRun(ctx)){
            Sleep(5000);
            if(movementService.robotPause(ctx)){
                Sleep(5000);
            }else
                return;
        }else
            return;
    }
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
    qDebug()<<"Test robot pause and run success.";
}
/**
 * @brief 逆解函数测试
 */
void MainWindow::on_inverseKinematic_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    SDKKinematic kinematic;
    kinematic.inverseKinematic(ctx);
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
}

void MainWindow::on_positiveKinematic_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    SDKKinematic kinematic;
    kinematic.positiveKinematic(ctx);
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
}

/**
 * @brief 变换用户坐标与基坐标测试
 */
void MainWindow::on_conventUserBase_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    int userNum = ui->userNumValue->text().toInt();
    SDKKinematic kinematic;
    kinematic.convertUserBase(ctx, userNum);
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
}

/**
 * @brief 数字量输入输出测试
 */
void MainWindow::on_digitalInOutput_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    IOService ioService;
    ioService.InOutputTest(ctx);
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
}
/**
 * @brief 获取虚拟输入测试
 */
void MainWindow::on_virtualInput_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    IOService ioService;
    ioService.getVirtualInput(ctx);
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
}
/**
 * @brief 虚拟输出测试
 */
void MainWindow::on_virtualOutput_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    IOService ioService;
    ioService.setGetVirtualOutput(ctx);
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
}
/**
 * @brief B变量测试
 */
void MainWindow::on_bVarValue_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    VarService varService;
    varService.setgetSysVarB(ctx);
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
}
/**
 * @brief 设置与获取I变量测试
 */
void MainWindow::on_iVarValue_clicked()
{
    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    VarService varService;
    varService.setgetSysVarI(ctx);
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
}

void MainWindow::on_dVarValue_clicked()
{

    ELT_CTX ctx;
    SDKContext context;
    ctx = context.SDKCreate(IP,PORT);
    if(NULL == ctx)
        return;
    if(!context.SDKLogin(ctx))
        return;
    VarService varService;
    varService.setgetSysVarD(ctx);
    if(!context.SDKLogOut(ctx))
        return;
    if(!context.SDKDestroy(ctx))
        return;
}
