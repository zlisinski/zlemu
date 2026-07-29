#ifndef ZLEMU_CORE_SMS_VDP_H
#define ZLEMU_CORE_SMS_VDP_H

#include <array>

#include <core/Zlemu.h>


class DisplayInterface;

namespace Sms
{

class Interrupt;


class Vdp
{
public:
    Vdp(Interrupt *interrupt, DisplayInterface *displayInterface);

    void Run(uint32_t masterClocks);

    uint8_t GetHCounter() const {return hCounter;}
    uint8_t GetVCounter() const {return vCounter;}

    uint8_t ReadData();
    void WriteData(uint8_t data);

    uint8_t ReadControl();
    void WriteControl(uint8_t data);

protected:
    void SetScreenHeight();
    uint8_t GetPixelColor(uint16_t tile, uint8_t x, uint8_t y) const;
    uint8_t GetSpritePixelColor(uint8_t x, uint8_t y);
    void LoadNextSprites(uint16_t scanline);
    template <bool SideStatusBar=false>
    void DrawScanline(uint16_t scanline);

    enum class ECode
    {
        ReadVram,
        WriteVram,
        WriteRegister,
        WriteCram
    };

    std::array<uint8_t, 0x4000> vram = {};
    std::array<uint8_t, 0x20> cram = {};
    std::array<uint32_t, 256 * 240> frameBuffer = {};

    uint16_t mclks = 0;

    // These are used by ports 7E/7F and jump backwards at some point.
    uint8_t hCounter = 0;
    uint8_t vCounter = 0;

    // These are the actual positions.
    uint16_t vPosition = 0;
    uint16_t hPosition = 0;

    uint8_t dataRegister = 0;
    uint8_t statusRegister = 0;

    uint16_t commandWord = 0;
    bool firstByte = true;
    ECode codeRegister = ECode::ReadVram;
    uint16_t addressRegister = 0;

    uint8_t regModeControl1 = 0x36;              // 0x00
    uint8_t regModeControl2 = 0xA0;              // 0x01
    uint8_t regNameTableBaseAddr = 0xFF;         // 0x02
    uint8_t regColorTableBaseAddr = 0xFF;        // 0x03
    uint8_t regBackgroundPatternBaseAddr = 0xFF; // 0x04
    uint8_t regSpriteAttributeBaseAddr = 0xFF;   // 0x05
    uint8_t regSpritePatternBaseAddr = 0xFB;     // 0x06
    uint8_t regOverscanColor = 0;                // 0x07
    uint8_t regXScroll = 0;                      // 0x08
    uint8_t regYScroll = 0;                      // 0x09
    uint8_t regLineCounter = 0xFF;               // 0x0A

    uint8_t screenHeight = 192;

    // Mode Control 1
    bool isSideStatusBar = false;
    bool isTopStatusBar = false;
    bool isMaskCol0 = true;
    bool isLineIntEnabled = true;
    bool isShiftSprites = false;
    bool isModeM4 = true;
    bool isModeM2 = true;

    // Mode Control 2
    bool isDisplayEnabled = true;
    bool isFrameIntEnabled = true;
    bool isModeM1 = false;
    bool isModeM3 = false;
    uint8_t spriteHeight = 8;
    bool isTallSprites = false;
    bool isSpriteDoubleSize = false;

    uint16_t nameTableBaseAddr = 0x3800;
    uint16_t spriteAttributeBaseAddr = 0x3F00;
    bool spritePatternHighBit = false;

    uint8_t xScrollLatch = 0;
    uint8_t yScrollLatch = 0;

    struct Sprite
    {
        uint8_t y;
        uint8_t x;
        uint8_t tile;
    } sprites[8] = {};
    uint8_t spriteCount = 0;

    Interrupt *interrupt = nullptr;
    DisplayInterface *displayInterface = nullptr;
};


}

#endif
