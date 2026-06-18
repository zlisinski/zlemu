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
        return this->memory[addr];
    }

    return this->wram[addr & 0x1FFF];
}


void Memory::WriteByte(uint16_t addr, uint8_t value)
{
    if (addr < 0xC000)
        throw std::runtime_error(std::format("Write to ROM {:04X} {:02X}", addr, value));

    this->wram[addr & 0x1FFF] = value;

    if ((addr & 0x1FFF) == 0x1FFC)
    {
        LogMemory("Write to RAM select register NYI %02X", value);
    }
    else if ((addr & 0xFF00) >= 0xFFFD)
    {
        MapPage((addr & 0xFF00) - 0xFFFD, value);
    }
}


void Memory::SetBios(const std::vector<uint8_t> &data)
{
    bios = data;
}


void Memory::SetRom(const std::vector<uint8_t> &data)
{
    rom = data;
}


void Memory::Reset()
{
    memory.fill(0);
    wram.fill(0);

    if (!bios.empty())
        memcpy(&memory[0], &bios[0], std::min(bios.size(), memory.size()));
    else
        memcpy(&memory[0], &rom[0], std::min(rom.size(), memory.size()));
}


void Memory::SetMemoryControlRegister(uint8_t value)
{
    LogMemory("memoryControlRegister=%02X", value);

    // All bits are active 0.
    // If the cartridge slot was just enabled.
    if (!Bytes::TestBit<6>(value) && Bytes::TestBit<6>(memoryControlRegister))
    {
        memcpy(&memory[0], &rom[0], std::min(rom.size(), memory.size()));
    }

    memoryControlRegister = value;
}


void Memory::MapPage(uint8_t dest, uint8_t src)
{
    constexpr uint16_t pageSize = 0x4000;
    uint16_t srcOffset = src * pageSize;
    uint16_t destOffset = dest * pageSize;

    if (srcOffset > rom.size())
    {
        LogError("Attempting to map bad page %04X of rom size %04X", srcOffset, rom.size());
        return;
    }

    LogMemory("Mapping ROM page %u to bank %u", src, dest);

    // The first 1K of bank 0 is not paged.
    if (dest == 0)
        memcpy(&memory[0x400], &rom[srcOffset + 0x400], pageSize - 0x400);
    else
        memcpy(&memory[destOffset], &rom[srcOffset], pageSize);
}


}
