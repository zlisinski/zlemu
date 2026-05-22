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


}