#include "Timer.h"
#include "Vdp.h"


namespace Sms
{


Timer::Timer(Vdp* vdp) :
    vdp(vdp)
{

}


void Timer::AddCycles(uint32_t cycles)
{
    counter += cycles;

    // Here "cycles" are CPU t-cycles. There are 3 master clock cycles per cpu t-cycle.
    vdp->Run(cycles * 3);
}


}
