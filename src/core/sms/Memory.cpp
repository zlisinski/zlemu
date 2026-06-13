#include <format>

#include <core/Logger.h>
#include "Memory.h"


namespace Sms
{


Memory::Memory()
{
}


uint8_t Memory::ReadByte(uint16_t addr) const
{
    if (addr < 0xC000)
    {
        return this->bios[addr];
    }

    return this->ram[addr & 0x1FFF];
}


void Memory::WriteByte(uint16_t addr, uint8_t value)
{
    if (addr < 0xC000)
        throw std::runtime_error(std::format("Write to ROM {:04X} {:02X}", addr, value));

    this->ram[addr & 0x1FFF] = value;
}


uint8_t Memory::ReadPort(uint8_t port) const
{
    LogMemory("ReadPort(%02X) = %02X", port, portData[port]);
    return portData[port];
}


void Memory::WritePort(uint8_t port, uint8_t value)
{
    LogMemory("WritePort(%02X, %02X)", port, value);
    portData[port] = value;
}


}
