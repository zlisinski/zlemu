#ifndef ZLEMU_CORE_SMS_TIMER_H
#define ZLEMU_CORE_SMS_TIMER_H

#include <core/Zlemu.h>


namespace Sms
{


class Interrupt;
class Vdp;


class Timer
{
public:
    Timer(Interrupt *interrupt, Vdp *vdp);

    void AddCycles(uint32_t cycles);

protected:
    uint64_t counter = 0;
};


}

#endif
