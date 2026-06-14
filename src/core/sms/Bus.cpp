#include <core/Logger.h>
#include "Bus.h"
#include "Memory.h"
#include "Vdp.h"


namespace Sms
{


Bus::Bus(Memory *memory, Vdp *vdp) :
    memory(memory),
    vdp(vdp)
{
}


uint8_t Bus::ReadPort(uint8_t port) const
{
    LogMemory("ReadPort(%02X)", port);

    switch (port & 0xC1)
    {
        case 0x00: // 0x00-0x3E even
        case 0x01: // 0x01-0x3F odd
            return 0xFF;

        case 0x40: // 0x40-0x7E even
            return vdp->GetVCounter();

        case 0x41: // 0x41-0x7F odd
            return vdp->GetHCounter();

        case 0x80: // 0x80-0xBE even
            return vdp->ReadData();

        case 0x81: // 0x81-0xBF odd
            return vdp->ReadControl();

        case 0xC0: // 0xC0-0xFE even
            // TODO: Return IO A/B
            return 0xFF;

        case 0xC1: // 0xC1-0xFF odd
            // TODO: Return IO B/Misc
            return 0xFF;

        default:
            return 0;
    }
}


void Bus::WritePort(uint8_t port, uint8_t value)
{
    LogMemory("WritePort(%02X, %02X)", port, value);

    switch (port & 0xC1)
    {
        case 0x00: // 0x00-0x3E even
            // TODO: Disable IO chip if bit is set
            memory->SetMemoryControlRegister(value);
            break;

        case 0x01: // 0x01-0x3F odd
            // TODO: Set IO control register
            break;

        case 0x40: // 0x40-0x7E even
        case 0x41: // 0x41-0x7F odd
            // TODO: Send data to Audio
            break;

        case 0x80: // 0x80-0xBE even
            vdp->WriteData(value);
            break;

        case 0x81: // 0x81-0xBF odd
            vdp->WriteControl(value);
            break;

        default:
            break;
    }
}


}
