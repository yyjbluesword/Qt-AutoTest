#include "varservice.h"
#include <QDebug>
#include <math.h>
#include <QTime>

#define PRINTERR qDebug()<<"err.code = "<<err.code<<" err.err_msg = "<<err.err_msg;

VarService::VarService()
{

}
/**
 * @brief 设置与获取B变量测试
 * @param ctx 上下文
 * @return 成功或失败
 */
bool VarService::setgetSysVarB(ELT_CTX ctx)
{
    int ret;
    elt_error err;
    int iValueArray[256];
    //B变量非法边界测试
    ret = elt_set_sysvar_b(ctx,-1,100,&err);
    if(ELT_ERROR == ret){
        qDebug()<<"Test Set B[-1] OK";
        PRINTERR;
    }else{
        qDebug()<<"Test Set B[-1] error. ret = "<<ret;
        PRINTERR;
        return false;
    }
    ret = elt_set_sysvar_b(ctx,256,100,&err);
    if(ELT_ERROR == ret){
        qDebug()<<"Test Set B[256] OK";
        PRINTERR;
    }else{
        qDebug()<<"Test Set B[256] error. ret = "<<ret;
        PRINTERR;
        return false;
    }
    //B变量值非法数据测试
    ret = elt_set_sysvar_b(ctx,0,-1,&err);
    if(ELT_ERROR == ret){
        qDebug()<<"TEST SET B[0]=-1 OK.";
        PRINTERR;
    }else{
        qDebug()<<"TEST SET B[0]=-1 ERROR. ret = "<<ret;
        PRINTERR;
        return false;
    }
    ret = elt_set_sysvar_b(ctx,0,(long int)(pow(2,16)),&err);
    if(ELT_ERROR == ret){
        qDebug()<<"TEST SET B[0] pow(2,16) SUCCESS. ";
    }else{
        qDebug()<<"TEST SET B[0] pow(2,16) ERROR. ret = "<<ret;
        PRINTERR;
        return false;
    }
    //设置与读取B变量测试
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i = 0; i < 256; i++){
        iValueArray[i] = qrand()%(long int)pow(2,16);
        ret = elt_set_sysvar_b(ctx,i,iValueArray[i],&err);
        if(ELT_SUCCESS == ret){
            //qDebug()<<"elt_set_sysver_b success.";
        }else if(ELT_FAILURE == ret){
            qDebug()<<"elt_set_sysvar_b failed.";
            PRINTERR;
            return false;
        }else if(ELT_ERROR == ret){
            qDebug()<<"elt_set_sysvar_b error.";
            PRINTERR;
            return false;
        }else{
            qDebug()<<"elt_set_sysvar_b other status.";
            PRINTERR;
            return false;
        }
    }
    Sleep(5000);
    //读取B变量值测试
    int value;
    for(int i = 0; i < 256; i++){
        ret = elt_get_sysvar_b(ctx,i,&value,&err);
        if(ELT_SUCCESS == ret){
            //qDebug()<<"elt_get_sysvar_b success.";
            if(value != iValueArray[i]){
                qDebug()<<"elt_get_sysvar_b failed.";
                qDebug()<<"Real B["<<i<<"] = "<<value<<", but Pormpt B["<<i<<"] = "<<iValueArray[i];
                return false;
            }
        }else if(ELT_FAILURE == ret){
            qDebug()<<"elt_get_sysvar_b failure. ";
            PRINTERR;
            return false;
        }else if(ELT_ERROR == ret){
            qDebug()<<"elt_get_sysvar_b error.";
            PRINTERR;
            return false;
        }else{
            qDebug()<<"elt_get_sysvar_b other status.";
            PRINTERR;
            return false;
        }
    }
    qDebug()<<"Test SetGet B Variable success.";
    return true;
}
/**
 * @brief 设置与获取I变量测试
 * @param ctx 上下文
 * @return 成功或失败
 */
bool VarService::setgetSysVarI(ELT_CTX ctx)
{
    int ret;
    elt_error err;
    int iValueArray[256];
    //I变量非法边界测试
    ret = elt_set_sysvar_i(ctx,-1,100,&err);
    if(ELT_ERROR == ret){
        qDebug()<<"Test Set I[-1] OK";
        PRINTERR;
    }else{
        qDebug()<<"Test Set I[-1] error. ret = "<<ret;
        PRINTERR;
        //return false;
    }
    ret = elt_set_sysvar_i(ctx,256,100,&err);
    if(ELT_ERROR == ret){
        qDebug()<<"Test Set I[256] OK";
        PRINTERR;
    }else{
        qDebug()<<"Test Set I[256] error. ret = "<<ret;
        PRINTERR;
        return false;
    }
    //I变量值非法数据测试
    //qDebug()<<"-2^31-1 = "<<QString("%1").arg(-1*pow(2,31)-1,0,'f',0)<<" -2^31 = "<<QString("%1").arg(-1*pow(2,31),0,'f',0);
    ret = elt_set_sysvar_i(ctx,0,(-1*pow(2,31)-1),&err);
    if(ELT_ERROR == ret){
        qDebug()<<"TEST SET I[0]=-1 OK.";
        PRINTERR;
    }else{
        qDebug()<<"TEST SET I[0]=-1 ERROR. ret = "<<ret;
        PRINTERR;
        //return false;
    }
    ret = elt_set_sysvar_i(ctx,0,(long int)(pow(2,31)),&err);
    if(ELT_ERROR == ret){
        qDebug()<<"TEST SET I[0] pow(2,31) SUCCESS. ";
    }else{
        qDebug()<<"TEST SET I[0] pow(2,31) ERROR. ret = "<<ret;
        PRINTERR;
        //return false;
    }
    //设置与读取I变量测试
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i = 0; i < 256; i++){
        iValueArray[i] = qrand()%(long int)pow(2,31);
        if(i%2)
            iValueArray[i] *= -1;
        ret = elt_set_sysvar_i(ctx,i,iValueArray[i],&err);
        if(ELT_SUCCESS == ret){
            //qDebug()<<"elt_set_sysver_i success.";
        }else if(ELT_FAILURE == ret){
            qDebug()<<"elt_set_sysvar_i failed.";
            PRINTERR;
            return false;
        }else if(ELT_ERROR == ret){
            qDebug()<<"elt_set_sysvar_i error.";
            PRINTERR;
            return false;
        }else{
            qDebug()<<"elt_set_sysvar_i other status.";
            PRINTERR;
            return false;
        }
    }
    Sleep(5000);
    //读取B变量值测试
    int value;
    for(int i = 0; i < 256; i++){
        ret = elt_get_sysvar_i(ctx,i,&value,&err);
        if(ELT_SUCCESS == ret){
            //qDebug()<<"elt_get_sysvar_i success.";
            if(value != iValueArray[i]){
                qDebug()<<"elt_get_sysvar_i failed.";
                qDebug()<<"Real I["<<i<<"] = "<<value<<", but Pormpt I["<<i<<"] = "<<iValueArray[i];
                return false;
            }
        }else if(ELT_FAILURE == ret){
            qDebug()<<"elt_get_sysvar_i failure. ";
            PRINTERR;
            return false;
        }else if(ELT_ERROR == ret){
            qDebug()<<"elt_get_sysvar_i error.";
            PRINTERR;
            return false;
        }else{
            qDebug()<<"elt_get_sysvar_i other status.";
            PRINTERR;
            return false;
        }
    }
    qDebug()<<"Test SetGet I Variable success.";
    return true;
}
/**
 * @brief 设置与获取D变量测试
 * @param ctx 上下文
 * @return 成功或失败
 */
bool VarService::setgetSysVarD(ELT_CTX ctx)
{
    int ret;
    elt_error err;
    int iValueArray[256];
    double dValueArray[256];
    //D变量非法边界测试
    ret = elt_set_sysvar_d(ctx, -1, 100, &err);
    if(ELT_ERROR == ret){
        qDebug()<<"Test Set D[-1] OK";
        PRINTERR;
    }else{
        qDebug()<<"Test Set D[-1] error. ret = "<<ret;
        PRINTERR;
        return false;
    }
    ret = elt_set_sysvar_d(ctx,256,100,&err);
    if(ELT_ERROR == ret){
        qDebug()<<"Test Set D[256] OK";
        PRINTERR;
    }else{
        qDebug()<<"Test Set D[256] error. ret = "<<ret;
        PRINTERR;
        return false;
    }
    //D变量值非法数据测试(未测试)
    //设置与读取I变量测试
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i = 0; i < 256; i++){
        dValueArray[i] = (qrand()%(long int)pow(2,31))/10.0;
        if(i%2)
            dValueArray[i] *= -1;
        ret = elt_set_sysvar_d(ctx,i,dValueArray[i],&err);
        if(ELT_SUCCESS == ret){
            //qDebug()<<"elt_set_sysver_d success.";
        }else if(ELT_FAILURE == ret){
            qDebug()<<"elt_set_sysvar_d failed.";
            PRINTERR;
            return false;
        }else if(ELT_ERROR == ret){
            qDebug()<<"elt_set_sysvar_d error.";
            PRINTERR;
            return false;
        }else{
            qDebug()<<"elt_set_sysvar_d other status.";
            PRINTERR;
            return false;
        }
    }
    Sleep(5000);
    //读取D变量值测试
    double value;
    for(int i = 0; i < 256; i++){
        ret = elt_get_sysvar_d(ctx,i,&value,&err);
        if(ELT_SUCCESS == ret){
            //qDebug()<<"elt_get_sysvar_i success.";
            if(fabs(value - dValueArray[i]) > 0.01){
                qDebug()<<"elt_get_sysvar_d failed.";
                qDebug()<<"Real D["<<i<<"] = "<<value<<", but Pormpt D["<<i<<"] = "<<dValueArray[i];
                return false;
            }
        }else if(ELT_FAILURE == ret){
            qDebug()<<"elt_get_sysvar_d failure. ";
            PRINTERR;
            return false;
        }else if(ELT_ERROR == ret){
            qDebug()<<"elt_get_sysvar_d error.";
            PRINTERR;
            return false;
        }else{
            qDebug()<<"elt_get_sysvar_d other status.";
            PRINTERR;
            return false;
        }
    }
    qDebug()<<"Test SetGet D Variable success.";
    return true;
}
