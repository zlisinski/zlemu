#include "Interrupt.h"
#include "Timer.h"


namespace Sms
{


Timer::Timer(Interrupt *interrupt, Vdp* vdp) :
    interrupt(interrupt),
    vdp(vdp)
{

}


void Timer::AddCycles(uint32_t cycles)
{
    counter += cycles;

    // Do enough to get a somewhat correct vblank interrupt.
    // The VDP runs at 1.5x the speed of the CPU, so use cycles*3/2.
    hCountDouble += (cycles * 3);
    if ((hCountDouble >> 1) > 342)
    {
        hCountDouble = 0;
        vCount++;
        if (vCount == 192)
        {
            interrupt->RequestInterrupt();
        }
        else if (vCount == 263)
        {
            vCount = 0;
        }
    }
}


}
