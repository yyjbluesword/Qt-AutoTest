#ifndef SDKKINEMATIC_H
#define SDKKINEMATIC_H

#include "elt_robot.h"

class SDKKinematic
{
public:
    SDKKinematic();
    ~SDKKinematic();
    bool inverseKinematic(ELT_CTX ctx);
    bool positiveKinematic(ELT_CTX ctx);
    bool convertUserBase(ELT_CTX ctx, int userNum);
};

#endif // SDKKINEMATIC_H
