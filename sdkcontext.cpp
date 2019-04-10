#include "sdkcontext.h"
#include <QDebug>

#define PRINTERR qDebug()<<"err.code = "<<err.code<<" err.err_msg = "<<err.err_msg;
/**
 * @brief 构造函数
 */
SDKContext::SDKContext()
{
}
/**
 * @brief 析构函数
 */
SDKContext::~SDKContext()
{
}
/**
 * @brief 初始化上下文服务
 * @param addr IP地址
 * @param port 端口号
 * @return 上下文
 */
ELT_CTX SDKContext::SDKCreate(const char *addr, int port)
{
    ctx = elt_create_ctx(addr,port);
    if(NULL == ctx){
        qDebug()<<"elt_create_ctx failed.";
    }
    //qDebug()<<"elt_create_ctx success.";
    return ctx;
}
/**
 * @brief 登录服务
 * @param ctx 上下文
 * @return 成功与失败
 */
bool SDKContext::SDKLogin(ELT_CTX ctx)
{
    int ret = elt_login(ctx);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_login success.";
        return true;
    }else if(ELT_FAILURE == ret)
        qDebug()<<"elt_login failure.";
    else if(ELT_ERROR == ret)
        qDebug()<<"elt_login error.";
    else
        qDebug()<<"elt_login other status.";
    return false;
}
/**
 * @brief 退出服务
 * @param ctx 上下文
 * @return  成功与失败
 */
bool SDKContext::SDKLogOut(ELT_CTX ctx)
{
    int ret = elt_logout(ctx);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_logout success.";
        return true;
    }else if(ELT_FAILURE == ret)
        qDebug()<<"elt_logout failure.";
    else if(ELT_ERROR == ret)
        qDebug()<<"elt_logout error.";
    else
        qDebug()<<"elt_logout other status.";
    return false;
}
/**
 * @brief 销毁服务
 * @param ctx 上下文
 * @return 成功与失败
 */
bool SDKContext::SDKDestroy(ELT_CTX ctx)
{
    int ret = elt_destroy_ctx(ctx);
    if(ELT_SUCCESS == ret){
        //qDebug()<<"elt_destroy success.";
        return true;
    }else if(ELT_FAILURE == ret)
        qDebug()<<"elt_destroy failure.";
    else if(ELT_ERROR == ret)
        qDebug()<<"elt_destroy error.";
    else
        qDebug()<<"elt_destroy other status.";
    return false;
}
