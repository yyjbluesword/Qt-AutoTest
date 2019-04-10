#include "ioservice.h"
#include <QDebug>

#define PRINTERR qDebug()<<"err.code = "<<err.code<<" err.err_msg = "<<err.err_msg;

IOService::IOService()
{

}
/**
 * @brief 获取输入与设置输出测试
 * @param ctx
 * @return
 */
bool IOService::InOutputTest(ELT_CTX ctx)
{
    int ret,status;
    elt_error err;
    //Input数据测试
    for(int i = -1; i < 129; i++){
        ret = elt_get_input(ctx, i, &status, &err);
        if(i == -1 || i == 128){
            if(ELT_ERROR == ret){
                qDebug()<<"Test Input("<<i<<") OK.";
                PRINTERR;
            }else{
                qDebug()<<"Test Input(-1) Error. ret = "<<ret;
                return false;
            }
        }else{
            if(ELT_SUCCESS == ret){
                //qDebug()<<"Test Input("<<i<<") OK.";
            }else if(ELT_FAILURE == ret){
                qDebug()<<"Test Input("<<i<<") Failed.";
                PRINTERR;
                return false;
            }else if(ELT_ERROR == ret){
                qDebug()<<"Test Input("<<i<<") Error.";
                PRINTERR;
                return false;
            }else{
                qDebug()<<"Test Input("<<i<<") other status.";
                PRINTERR;
                return false;
            }
        }
    }
    qDebug()<<"Get Input Data success.";
    //设置与读取Output数据测试
    for(int i = 0; i < 2; i++){
        status = (i == 0 ? 0 : 1);
        for(int j = -1; j < 129; j++){
            ret = elt_set_output(ctx,j,status,&err);
            if(j == -1 || j == 128){
                if(ELT_ERROR == ret){
                    qDebug()<<"setOutput("<<j<<") OK.";
                    PRINTERR;
                }else{
                    qDebug()<<"setOutput("<<j<<") Error. ret = "<<ret;
                    return false;
                }
            }else{
                if(ELT_SUCCESS == ret){
                    //qDebug()<<"setOutput("<<j<<") OK.";
                }else if(ELT_FAILURE == ret){
                    qDebug()<<"setOutput("<<j<<") Failed.";
                    PRINTERR;
                    return false;
                }else if(ELT_ERROR == ret){
                    qDebug()<<"setOutput("<<j<<") Error.";
                    PRINTERR;
                    //return false;
                }else{
                    qDebug()<<"setOutput("<<j<<") other status.";
                    PRINTERR;
                    return false;
                }
            }
            status = (status == 0 ? 1 : 0);
        }
        Sleep(5000);
        //获取输出口数据测试
        status = (i == 0 ? 0 : 1);
        int retVal;
        for(int j = -1; j < 129; j++){
            ret = elt_get_output(ctx, j, &retVal,&err);
            if(j == -1 || j == 128){
                if(ELT_ERROR == ret){
                    qDebug()<<"getOutput("<<j<<") OK.";
                    PRINTERR;
                }else{
                    qDebug()<<"getOutput("<<j<<") Error. ret = "<<ret;
                    return false;
                }
            }else{
                if(ELT_SUCCESS == ret){
                    if(retVal != status){
                        qDebug()<<"relVal Output("<<j<<")= "<<retVal<<" preVal Output("<<j<<")= "<<status;
                    }
                    //qDebug()<<"setOutput("<<j<<") OK.";
                }else if(ELT_FAILURE == ret){
                    qDebug()<<"setOutput("<<j<<") Failed.";
                    PRINTERR;
                    return false;
                }else if(ELT_ERROR == ret){
                    qDebug()<<"getOutput("<<j<<") Error.";
                    PRINTERR;
                    //return false;
                }else{
                    qDebug()<<"getOutput("<<j<<") other status.";
                    PRINTERR;
                    return false;
                }
            }
            status = (status == 0 ? 1 : 0);
        }
    }
    return true;
}
/**
 * @brief 获取虚拟输入测试
 * @return 成功与失败
 */
bool IOService::getVirtualInput(ELT_CTX ctx)
{
    int ret,status;
    elt_error err;
    //Input数据测试
    for(int i = -1; i < 401; i++){
        ret = elt_get_input(ctx, i, &status, &err);
        if(i == -1 || i == 400){
            if(ELT_ERROR == ret){
                qDebug()<<"Test VirtualInput("<<i<<") OK.";
                PRINTERR;
            }else{
                qDebug()<<"Test VirtualInput("<<-1<<") Error. ret = "<<ret;
                return false;
            }
        }else{
            if(ELT_SUCCESS == ret){
                //qDebug()<<"Test VirtualInput("<<i<<") OK.";
            }else if(ELT_FAILURE == ret){
                qDebug()<<"Test VirtualInput("<<i<<") Failed.";
                PRINTERR;
                return false;
            }else if(ELT_ERROR == ret){
                qDebug()<<"Test VirtualInput("<<i<<") Error.";
                PRINTERR;
                return false;
            }else{
                qDebug()<<"Test VirtualInput("<<i<<") other status.";
                PRINTERR;
                return false;
            }
        }
    }
    qDebug()<<"Get VirtualInput Data success.";
    return true;
}
/**
 * @brief 获取与设置虚拟输出测试
 * @param ctx 上下文
 * @return 成功或失败
 */
bool IOService::setGetVirtualOutput(ELT_CTX ctx)
{
    int ret,status;
    elt_error err;
    //设置与读取Output数据测试
    for(int i = 0; i < 2; i++){
        status = (i == 0 ? 0 : 1);
        for(int j = 399; j < 801; j++){
            ret = elt_set_virtual_output(ctx, j, status, &err);
            if(j == 399 || j == 800){
                if(ELT_ERROR == ret){
                    qDebug()<<"setVirtualOutput("<<j<<") OK.";
                    PRINTERR;
                }else{
                    qDebug()<<"setVirtualOutput("<<j<<") Error. ret = "<<ret;
                    return false;
                }
            }else{
                if(ELT_SUCCESS == ret){
                    //qDebug()<<"setVirtualOutput("<<j<<") OK.";
                }else if(ELT_FAILURE == ret){
                    qDebug()<<"setVirtualOutput("<<j<<") Failed.";
                    PRINTERR;
                    return false;
                }else if(ELT_ERROR == ret){
                    qDebug()<<"setVirtualOutput("<<j<<") Error.";
                    PRINTERR;
                    //return false;
                }else{
                    qDebug()<<"setVirtualOutput("<<j<<") other status.";
                    PRINTERR;
                    return false;
                }
            }
            status = (status == 0 ? 1 : 0);
        }
        Sleep(5000);
        //获取输出口数据测试
        status = (i == 0 ? 0 : 1);
        int retVal;
        for(int j = 399; j < 1538; j++){
            ret = elt_get_output(ctx, j, &retVal,&err);
            if(j == 399 || j == 1537){
                if(ELT_ERROR == ret){
                    qDebug()<<"getVirtualOutput("<<j<<") OK.";
                    PRINTERR;
                }else{
                    qDebug()<<"getVirtualOutput("<<j<<") Error. ret = "<<ret;
                    return false;
                }
            }else{
                if(ELT_SUCCESS == ret){
                    if(retVal != status && j > 399 && j < 1537){
                        qDebug()<<"relVal VirtualOutput("<<j<<")= "<<retVal<<" preVal VirtualOutput("<<j<<")= "<<status;
                    }
                }else if(ELT_FAILURE == ret){
                    qDebug()<<"getVirtualOutput("<<j<<") Failed.";
                    PRINTERR;
                    return false;
                }else if(ELT_ERROR == ret){
                    qDebug()<<"getVirtualOutput("<<j<<") Error.";
                    PRINTERR;
                    //return false;
                }else{
                    qDebug()<<"getVirtualOutput("<<j<<") other status.";
                    PRINTERR;
                    return false;
                }
            }
            status = (status == 0 ? 1 : 0);
        }
    }
    return true;
}
