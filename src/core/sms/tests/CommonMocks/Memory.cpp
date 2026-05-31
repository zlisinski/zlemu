#include "Memory.h"

namespace Sms
{


Memory::Memory()
{
}


uint8_t Memory::ReadByte(uint16_t addr) const
{
    return memory[addr];
}


void Memory::WriteByte(uint16_t addr, uint8_t value)
{
    memory[addr] = value;
}


uint8_t Memory::ReadPort(uint8_t port) const
{
    return portData[port];
}


void Memory::WritePort(uint8_t port, uint8_t value)
{
    portData[port] = value;
}


}
