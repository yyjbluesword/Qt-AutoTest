#ifndef SDKCONTEXT_H
#define SDKCONTEXT_H
#include "elt_robot.h"

class SDKContext
{
public:
    SDKContext();
    ~SDKContext();
    ELT_CTX SDKCreate(const char *addr, int port);
    bool SDKLogin(ELT_CTX ctx);
    bool SDKLogOut(ELT_CTX ctx);
    bool SDKDestroy(ELT_CTX ctx);
private:
    ELT_CTX ctx;
    elt_error err;
};

#endif // SDKCONTEXT_H
