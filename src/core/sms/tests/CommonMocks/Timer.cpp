#include "Timer.h"


namespace Sms
{


Timer::Timer(Interrupt *interrupt, Vdp *vdp)
{
    (void)interrupt;
    (void)vdp;
}


void Timer::AddCycles(uint32_t cycles)
{
    counter += cycles;
}


}
