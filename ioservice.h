#ifndef IOSERVICE_H
#define IOSERVICE_H

#include "elt_robot.h"

class IOService
{
public:
    IOService();
    bool InOutputTest(ELT_CTX ctx);
    bool getVirtualInput(ELT_CTX ctx);
    bool setGetVirtualOutput(ELT_CTX ctx);
};

#endif // IOSERVICE_H
