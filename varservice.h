#ifndef VARSERVICE_H
#define VARSERVICE_H
#include "elt_robot.h"

class VarService
{
public:
    VarService();
    bool setgetSysVarB(ELT_CTX ctx);
    bool setgetSysVarI(ELT_CTX ctx);
    bool setgetSysVarD(ELT_CTX ctx);
};

#endif // VARSERVICE_H
