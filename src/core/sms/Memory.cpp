#include <format>

#include <core/Logger.h>
#include "Memory.h"


namespace Sms
{

constexpr uint16_t PageSize = 0x4000;


Memory::Memory()
{
}


uint8_t Memory::ReadByte(uint16_t addr) const
{
    if (addr < 0xC000)
    {
        if (isCartEnabled || isBiosEnabled)
            return this->memory[addr];
        return 0xFF;
    }

    return this->wram[addr & 0x1FFF];
}


void Memory::WriteByte(uint16_t addr, uint8_t value)
{
    if (addr < 0xC000)
    {
        if (addr < 0x8000 || !isSramEnabled)
        {
            //throw std::runtime_error(std::format("Write to ROM {:04X} {:02X}", addr, value));
            LogWarning("Write to ROM %04X %02X", addr, value);
            return;
        }
        this->memory[addr] = value;
        return;
    }

    this->wram[addr & 0x1FFF] = value;

    // Only perform mapping if cartridge slot enabled.
    if (addr >= 0xFFFC && isCartEnabled)
    {
        if (addr == 0xFFFC)
        {
            MapSram(Bytes::TestBit<3>(value));
        }
        else if (addr >= 0xFFFD)
        {
            MapRomBank(addr - 0xFFFD, value);
        }
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
    sram.fill(0);

    if (!bios.empty())
    {
        memcpy(&memory[0], &bios[0], std::min(bios.size(), memory.size()));
        memoryControlRegister = 0xE0; // 11100000
        isBiosEnabled = true;
        isCartEnabled = false;
    }
    else
    {
        memcpy(&memory[0], &rom[0], std::min(rom.size(), memory.size()));
        memoryControlRegister = 0xAB; // 10101011
        isBiosEnabled = false;
        isCartEnabled = true;
        wram[0] = 0xAB;
    }
}


void Memory::SetMemoryControlRegister(uint8_t value)
{
    memoryControlRegister = value;

    bool oldCartEnabled = isCartEnabled;
    bool oldBiosEnabled = isBiosEnabled;

    // All bits are active 0.
    isCartEnabled = !Bytes::TestBit<6>(value);
    isBiosEnabled = !Bytes::TestBit<3>(value);

    bool cartChanged = isCartEnabled ^ oldCartEnabled;
    bool biosChanged = isBiosEnabled ^ oldBiosEnabled;

    LogMemory("memoryControlRegister=%02X Cart=%d Bios=%d", value, isCartEnabled, isBiosEnabled);

    if (isCartEnabled && cartChanged)
    {
        // The cartridge slot was just enabled.
        LogMemory("Bios handoff to cartridge");
        memcpy(&memory[0], &rom[0], std::min(rom.size(), memory.size()));
    }
    else if (isBiosEnabled && biosChanged && !isCartEnabled)
    {
        // The bios was re-enabled.
        LogMemory("Bios take over from cartridge");
        memcpy(&memory[0], &bios[0], std::min(bios.size(), memory.size()));
    }
}


void Memory::MapRomBank(uint8_t dest, uint8_t src)
{
    if (dest == 2 && isSramEnabled)
    {
        LogWarning("Attempting to map ROM to page 2 when SRAM is active");
        return;
    }

    constexpr uint16_t pageSize = 0x4000;
    uint32_t srcOffset = (src * pageSize) & (rom.size() - 1);
    uint32_t destOffset = dest * pageSize;

    LogMemory("Mapping ROM bank %u to memory page %u", src, dest);

    // The first 1K of bank 0 is not paged.
    if (dest == 0)
        memcpy(&memory[0x400], &rom[srcOffset + 0x400], pageSize - 0x400);
    else
        memcpy(&memory[destOffset], &rom[srcOffset], pageSize);
}


void Memory::MapSram(bool enabled)
{
    uint8_t *page2 = &memory[0x8000];
    uint8_t *oldBank = &sram[PageSize * currentSramBank];
    currentSramBank = Bytes::GetBit<2>(wram[0x1FFC]);
    uint8_t *newBank = &sram[PageSize * currentSramBank];

    if (enabled != isSramEnabled)
    {
        isSramEnabled = enabled;

        if (enabled)
        {
            // SRAM is replacing ROM.
            LogMemory("Mapping SRAM bank %u to memory page 2", currentSramBank);
            memcpy(page2, newBank, PageSize);
        }
        else
        {
            // ROM is replacing SRAM. Backup SRAM, then map ROM.
            memcpy(oldBank, page2, PageSize);
            MapRomBank(2, wram[0x1FFF]);
        }
    }
    else if (enabled)
    {
        // SRAM bank is changing, save the current bank before changing.
        LogMemory("Mapping SRAM bank %u to memory page 2", currentSramBank);
        memcpy(oldBank, page2, PageSize);
        memcpy(page2, newBank, PageSize);
    }
}


}
