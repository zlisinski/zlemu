#ifndef ZLEMU_CORE_SMS_MEMORY_H
#define ZLEMU_CORE_SMS_MEMORY_H

#include <array>
#include <vector>

#include <core/Bytes.h>
#include <core/Zlemu.h>


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

    uint8_t ReadPort(uint8_t port) const;

    void WritePort(uint8_t port, uint8_t value);

    void ClearMemory()
    {
        ram.fill(0);
    }

    void SetBios(std::vector<uint8_t>&& data) {this->bios = std::move(data);}

protected:
    std::array<uint8_t, 0x2000> ram = {0};
    std::array<uint8_t, 0x100> portData = {0};
    std::vector<uint8_t> bios;
};


}

#endif