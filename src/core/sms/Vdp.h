#ifndef ZLEMU_CORE_SMS_VDP_H
#define ZLEMU_CORE_SMS_VDP_H

#include <array>

#include <core/Zlemu.h>


namespace Sms
{

class Interrupt;


class Vdp
{
public:
    Vdp(Interrupt *interrupt);

    void Run(uint32_t masterClocks);

    uint8_t GetHCounter() const {return hCounter;}
    uint8_t GetVCounter() const {return vCounter;}

    uint8_t ReadData();
    void WriteData(uint8_t data);

    uint8_t ReadControl();
    void WriteControl(uint8_t data);

protected:
    void DrawScanline();

    enum class ECode
    {
        ReadVram,
        WriteVram,
        WriteRegister,
        WriteCram
    };

    std::array<uint8_t, 0x4000> vram = {};
    std::array<uint8_t, 0x20> cram = {};

    uint16_t mclks = 0;

    // These are used by ports 7E/7F and jump backwards at some point.
    uint8_t hCounter = 0;
    uint8_t vCounter = 0;

    // These are the actual positions.
    uint16_t scanline = 0;
    uint16_t hPosition = 0;

    uint8_t dataRegister = 0;
    uint8_t statusRegister = 0;

    uint16_t commandWord = 0;
    bool firstByte = true;
    ECode codeRegister = ECode::ReadVram;
    uint16_t addressRegister = 0;

    uint8_t regModeControl1 = 0;              // 0x00
    uint8_t regModeControl2 = 0;              // 0x01
    uint8_t regNameTableBaseAddr = 0;         // 0x02
    uint8_t regColorTableBaseAddr = 0;        // 0x03
    uint8_t regBackgroundPatternBaseAddr = 0; // 0x04
    uint8_t regSpriteAttributeBaseAddr = 0;   // 0x05
    uint8_t regSpritePatternBaseAddr = 0;     // 0x06
    uint8_t regOverscanColor = 0;             // 0x07
    uint8_t regXScroll = 0;                   // 0x08
    uint8_t regYScroll = 0;                   // 0x09
    uint8_t regLineCounter = 0;               // 0x0A

    Interrupt *interrupt = nullptr;
};


}

#endif
