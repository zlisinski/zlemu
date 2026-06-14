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

    return this->wram[addr & 0x1FFF];
}


void Memory::WriteByte(uint16_t addr, uint8_t value)
{
    if (addr < 0xC000)
        throw std::runtime_error(std::format("Write to ROM {:04X} {:02X}", addr, value));

    this->wram[addr & 0x1FFF] = value;
}


void Memory::SetMemoryControlRegister(uint8_t value)
{
    memoryControlRegister = value;
}


}
