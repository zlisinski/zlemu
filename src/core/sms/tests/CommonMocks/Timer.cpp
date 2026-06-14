#include "Timer.h"


namespace Sms
{


Timer::Timer(Vdp *vdp)
{
    (void)vdp;
}


void Timer::AddCycles(uint32_t cycles)
{
    counter += cycles;
}


}
