#ifndef ZLEMU_CORE_SMS_MEMORY_H
#define ZLEMU_CORE_SMS_MEMORY_H

#include <array>

#include "../Bytes.h"
#include "../Zlemu.h"


namespace Sms
{


class Memory
{
public:
    Memory();
    ~Memory() = default;

    uint8_t ReadByte(uint16_t addr) const;
    uint16_t ReadWord(uint16_t addr) const
    {
        uint8_t low = ReadByte(addr);
        uint8_t high = ReadByte(addr + 1);
        return Bytes::Make16Bit(high, low);
    }

    void WriteByte(uint16_t addr, uint8_t value);
    void WriteWord(uint16_t addr, uint16_t value)
    {
        WriteByte(addr, Bytes::GetByte<0>(value));
        WriteByte(addr + 1, Bytes::GetByte<1>(value));
    }


    void ClearMemory()
    {
        memory.fill(0);
    }

protected:
    std::array<uint8_t, 0x10000> memory = {0};
};


}

#endif