#include "Bus.h"


namespace Sms
{


Bus::Bus(Memory *memory, Vdp *vdp)
{
    (void)memory;
    (void)vdp;
}


uint8_t Bus::ReadPort(uint8_t port) const
{
    return portData[port];
}


void Bus::WritePort(uint8_t port, uint8_t value)
{
    portData[port] = value;
}


}
