#include <core/Bytes.h>
#include <core/DisplayInterface.h>
#include <core/Logger.h>
#include "Interrupt.h"
#include "Vdp.h"


namespace Sms
{

static constexpr uint32_t ColorTable[] = {
    0x00000000, 0x00550000, 0x00AA0000, 0x00FF0000, 0x00005500, 0x00555500, 0x00AA5500, 0x00FF5500,
    0x0000AA00, 0x0055AA00, 0x00AAAA00, 0x00FFAA00, 0x0000FF00, 0x0055FF00, 0x00AAFF00, 0x00FFFF00,
    0x00000055, 0x00550055, 0x00AA0055, 0x00FF0055, 0x00005555, 0x00555555, 0x00AA5555, 0x00FF5555,
    0x0000AA55, 0x0055AA55, 0x00AAAA55, 0x00FFAA55, 0x0000FF55, 0x0055FF55, 0x00AAFF55, 0x00FFFF55,
    0x000000AA, 0x005500AA, 0x00AA00AA, 0x00FF00AA, 0x000055AA, 0x005555AA, 0x00AA55AA, 0x00FF55AA,
    0x0000AAAA, 0x0055AAAA, 0x00AAAAAA, 0x00FFAAAA, 0x0000FFAA, 0x0055FFAA, 0x00AAFFAA, 0x00FFFFAA,
    0x000000FF, 0x005500FF, 0x00AA00FF, 0x00FF00FF, 0x000055FF, 0x005555FF, 0x00AA55FF, 0x00FF55FF,
    0x0000AAFF, 0x0055AAFF, 0x00AAAAFF, 0x00FFAAFF, 0x0000FFFF, 0x0055FFFF, 0x00AAFFFF, 0x00FFFFFF,
};


Vdp::Vdp(Interrupt *interrupt, DisplayInterface *displayInterface) :
    interrupt(interrupt),
    displayInterface(displayInterface)
{
}


void Vdp::Run(uint32_t masterClocks)
{
    // A lot of this is probably wrong, fix it later.

    mclks += masterClocks;

    // VDP runs at half the master clock.
    uint16_t oldHPosition = hPosition;
    hPosition = mclks / 2;

    // hCounter is the top 8 bits of a 9 bit counter.
    hCounter = hPosition >> 1;

    if (hPosition >= 279)
    {
        // Counter jumps forward for some reason.
        hCounter += 84;

        if (oldHPosition < 279)
        {
            // Enter hblank
        }
    }

    if (hPosition >= 342)
    {
        // Reset mclks counter, but keep remainder.
        mclks &= 0x01;
        hPosition = 0;
        vPosition++;
        vCounter++;

        if (vPosition < 192)
        {
            DrawScanline(vPosition);
        }
        else if (vPosition == 192)
        {
            // Enter vblank
            displayInterface->FrameReady(frameBuffer);

            Bytes::SetBit<7>(statusRegister);
            if (Bytes::TestBit<5>(regModeControl2))
            {
                interrupt->RequestInterrupt();
            }
        }
        else if (vPosition == 219)
        {
            // The value jumps backwards for some reason.
            vCounter -= 6;
        }
        else if (vPosition == 262)
        {
            // Exit vblank
            vPosition = 0;
        }
    }
}


uint8_t Vdp::ReadData()
{
    firstByte = true;
    uint8_t data = dataRegister;

    dataRegister = vram[addressRegister];
    addressRegister = (addressRegister + 1) & 0x3FFF;

    return data;
}


void Vdp::WriteData(uint8_t data)
{
    firstByte = true;

    dataRegister = data;
    if (codeRegister == ECode::WriteCram)
        cram[addressRegister & 0x1F] = data;
    else
        vram[addressRegister] = data;

    addressRegister = (addressRegister + 1) & 0x3FFF;
}


uint8_t Vdp::ReadControl()
{
    firstByte = true;

    uint8_t data = statusRegister;
    statusRegister = 0;
    interrupt->ClearInterrupt();

    return data;
}


void Vdp::WriteControl(uint8_t data)
{
    if (firstByte)
    {
        commandWord = (commandWord & 0xFF00) | data;
        firstByte = false;
        return;
    }

    commandWord = (data << 8) | (commandWord & 0xFF);
    firstByte = true;

    codeRegister = static_cast<ECode>(commandWord >> 14);
    addressRegister = commandWord & 0x3FFF;

    if (codeRegister == ECode::ReadVram)
    {
        dataRegister = vram[addressRegister];
        addressRegister = (addressRegister + 1) & 0x3FFF;
    }
    else if (codeRegister == ECode::WriteRegister)
    {
        uint8_t reg = (addressRegister >> 8) & 0x0F;
        data = addressRegister & 0xFF;
        switch (reg)
        {
            case 0x00:
                regModeControl1 = data;
                break;
            case 0x01:
                regModeControl2 = data;
                // Clearing the IE bit clears any pending interrupts.
                if (!Bytes::TestBit<5>(regModeControl2))
                    interrupt->ClearInterrupt();
                break;
            case 0x02:
                regNameTableBaseAddr = data;
                break;
            case 0x03:
                regColorTableBaseAddr = data;
                break;
            case 0x04:
                regBackgroundPatternBaseAddr = data;
                break;
            case 0x05:
                regSpriteAttributeBaseAddr = data;
                break;
            case 0x06:
                regSpritePatternBaseAddr = data;
                break;
            case 0x07:
                regOverscanColor = data;
                break;
            case 0x08:
                regXScroll = data;
                break;
            case 0x09:
                regYScroll = data;
                break;
            case 0x0A:
                regLineCounter = data;
                break;
            default:
                break;
        }
    }
}


uint8_t Vdp::GetPixelColor(uint16_t tile, uint8_t x, uint8_t y) const
{
    const uint8_t *tileData = &vram[tile * 32];
    uint8_t xOffset = 7 - x;
    uint8_t yOffset = y * 4;

    uint8_t bit0 = (tileData[yOffset] >> xOffset) & 0x01;
    uint8_t bit1 = (tileData[yOffset + 1] >> xOffset) & 0x01;
    uint8_t bit2 = (tileData[yOffset + 2] >> xOffset) & 0x01;
    uint8_t bit3 = (tileData[yOffset + 3] >> xOffset) & 0x01;

    return (bit3 << 3) | (bit2 << 2) | (bit1 << 1) | bit0;
}


void Vdp::DrawScanline(uint16_t scanline)
{
    DrawBackground(scanline);
}


void Vdp::DrawBackground(uint16_t scanline)
{
    uint8_t y = (scanline + regYScroll) % 224;
    uint8_t yTile = y / 8;
    uint8_t yOffset = y & 7;

    for (int i = 0; i < 256; i++)
    {
        uint8_t x = (i + regXScroll) & 0xFF;
        uint8_t xTile = x / 8;
        uint8_t xOffset = x & 7;

        uint16_t addr = ((regNameTableBaseAddr << 10) & 0x3800) | (yTile << 6) | (xTile << 1);
        uint16_t tileIndex = vram[addr];
        uint8_t tileAttr = vram[addr + 1];
        tileIndex |= (tileAttr & 0x01) << 8;

        uint8_t colorIndex = GetPixelColor(tileIndex, xOffset, yOffset);
        uint8_t color = cram[colorIndex];
        frameBuffer[(scanline * 256) + x] = ColorTable[color];
    }
}


}
