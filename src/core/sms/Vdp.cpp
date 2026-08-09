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
    hPosition = mclks / 2;

    if (hPosition >= 342)
    {
        // Reset mclks counter, but keep remainder.
        mclks -= 684;
        hPosition = mclks / 2;
        vPosition++;
        vCounter++;

        xScrollLatch = regXScroll;

        if (vPosition <= 192)
        {
            lineIntCounter--;
            if (lineIntCounter == 0xFF)
            {
                lineIntCounter = regLineCounter;
                if (isLineIntEnabled)
                {
                    LogInterrupt("Requesting frame IRQ");
                    interrupt->RequestIrq();
                }
            }
        }
        else
        {
            lineIntCounter = regLineCounter;
        }

        if (vPosition <= 192)
        {
            if (isSideStatusBar)
                DrawScanline<true>(vPosition - 1);
            else
                DrawScanline<false>(vPosition - 1);
            LoadNextSprites(vPosition);
        }
        else if (vPosition == 193)
        {
            // Enter vblank
            displayInterface->FrameReady(frameBuffer);

            Bytes::SetBit<7>(statusRegister);
            if (isFrameIntEnabled)
            {
                LogInterrupt("Requesting frame IRQ");
                interrupt->RequestIrq();
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
            // Load sprites for the next scanline, which is 0.
            LoadNextSprites(0);

            yScrollLatch = regYScroll;
        }
    }
}


void Vdp::LatchHCounter()
{
    // hCounter is the top 8 bits of a 9 bit counter.
    hCounter = hPosition >> 1;

    if (hCounter > 147)
    {
        // Counter jumps forward for some reason.
        hCounter += 85;
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
    interrupt->ClearIrq();

    return data;
}


void Vdp::WriteControl(uint8_t data)
{
    if (firstByte)
    {
        addressRegister = (addressRegister & 0x3F00) | data;
        firstByte = false;
        return;
    }

    firstByte = true;

    addressRegister = ((data & 0x3F) << 8) | (addressRegister & 0xFF);
    codeRegister = static_cast<ECode>(data >> 6);

    if (codeRegister == ECode::ReadVram)
    {
        dataRegister = vram[addressRegister];
        addressRegister = (addressRegister + 1) & 0x3FFF;
    }
    else if (codeRegister == ECode::WriteRegister)
    {
        uint8_t reg = (addressRegister >> 8) & 0x0F;
        data = addressRegister & 0xFF;
        LogDisplay("Write to VDP register %02X %02X", reg, data);
        switch (reg)
        {
            case 0x00:
                regModeControl1 = data;

                isSideStatusBar = Bytes::TestBit<7>(regModeControl1);
                isTopStatusBar = Bytes::TestBit<6>(regModeControl1);
                isMaskCol0 = Bytes::TestBit<5>(regModeControl1);
                isLineIntEnabled = Bytes::TestBit<4>(regModeControl1);
                isShiftSprites = Bytes::TestBit<3>(regModeControl1);
                isModeM4 = Bytes::TestBit<2>(regModeControl1);
                isModeM2 = Bytes::TestBit<1>(regModeControl1);

                LogDisplay("SideStatusBar=%d TopStatusBar=%d MaskCol0=%d LineInt=%d ShiftSprites=%d M4=%d M2=%d",
                    isSideStatusBar, isTopStatusBar, isMaskCol0, isLineIntEnabled, isShiftSprites, isModeM4, isModeM2);

                SetScreenHeight();
                break;
            case 0x01:
                regModeControl2 = data;

                isDisplayEnabled = Bytes::TestBit<6>(regModeControl2);
                isFrameIntEnabled = Bytes::TestBit<5>(regModeControl2);
                isModeM1 = Bytes::TestBit<4>(regModeControl2);
                isModeM3 = Bytes::TestBit<3>(regModeControl2);
                spriteHeight = 8 << Bytes::TestBit<1>(regModeControl2);
                isTallSprites = Bytes::TestBit<1>(regModeControl2);
                isSpriteDoubleSize = Bytes::TestBit<0>(regModeControl2);

                // Clearing the IE bit clears any pending interrupts.
                if (!Bytes::TestBit<5>(regModeControl2))
                    interrupt->ClearIrq();

                LogDisplay("DisplayOn=%d FrameInt=%d M1=%d M3=%d SpriteHeight=%d 2xSprite=%d",
                    isDisplayEnabled, isFrameIntEnabled, isModeM1, isModeM3, spriteHeight, isSpriteDoubleSize);

                SetScreenHeight();
                break;
            case 0x02:
                regNameTableBaseAddr = data;
                nameTableBaseAddr = (data & 0x0E) << 10;
                LogDisplay("NameTableBaseAddr=%04X", nameTableBaseAddr);
                break;
            case 0x03:
                regColorTableBaseAddr = data;
                break;
            case 0x04:
                regBackgroundPatternBaseAddr = data;
                break;
            case 0x05:
                regSpriteAttributeBaseAddr = data;
                spriteAttributeBaseAddr = (data & 0x7E) << 7;
                LogDisplay("SpriteAttributeBaseAddr=%04X", spriteAttributeBaseAddr);
                break;
            case 0x06:
                regSpritePatternBaseAddr = data;
                spritePatternHighBit = Bytes::TestBit<2>(regSpritePatternBaseAddr);
                LogDisplay("spritePatternHighBit=%d", spritePatternHighBit);
                break;
            case 0x07:
                regOverscanColor = data;
                LogDisplay("OverscanColor=%02X", regOverscanColor);
                break;
            case 0x08:
                regXScroll = data;
                LogDisplay("XScroll=%02X", regXScroll);
                break;
            case 0x09:
                regYScroll = data;
                LogDisplay("YScroll=%02X", regYScroll);
                break;
            case 0x0A:
                regLineCounter = data;
                LogDisplay("LineCounter=%02X", regLineCounter);
                break;
            default:
                break;
        }
    }
}


void Vdp::SetScreenHeight()
{
    screenHeight = 192;
    if (isModeM4 && isModeM2)
    {
        if (isModeM3 && !isModeM1)
            screenHeight = 240;
        else if (isModeM1 && !isModeM3)
            screenHeight = 224;
    }
    LogDisplay("ScreenHeight=%d", screenHeight);
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


uint8_t Vdp::GetSpritePixelColor(uint8_t x, uint8_t y)
{
    uint8_t ret = 0xFF;

    for (int i = 0; i < spriteCount; i++)
    {
        int spriteShift = isShiftSprites * -8;
        int spriteX = sprites[i].x + spriteShift;

        if (x < spriteX || x >= spriteX + (8 << isSpriteDoubleSize))
            continue;

        uint8_t xOffset = (x - spriteX) >> isSpriteDoubleSize;
        uint8_t yOffset = (y - sprites[i].y) >> isSpriteDoubleSize;
        uint16_t tileIndex = (spritePatternHighBit << 8) | sprites[i].tile;

        // Tall sprites always start on an even tile.
        tileIndex &= ~((uint16_t)isTallSprites);

        uint8_t colorIndex = GetPixelColor(tileIndex, xOffset, yOffset);
        if (colorIndex != 0)
        {
            // If this is the first non-transparent color, save it and keep checking for sprite collisions.
            if (ret == 0xFF)
                ret = colorIndex;
            else
            {
                Bytes::SetBit<5>(statusRegister);
                break;
            }
        }
    }

    return ret;
}


void Vdp::LoadNextSprites(uint16_t scanline)
{
    spriteCount = 0;
    const uint8_t *dataY = &vram[spriteAttributeBaseAddr];
    const uint8_t *dataXT = &vram[spriteAttributeBaseAddr + 0x80];

    for (int i = 0; i < 64; i++)
    {
        // Sprite Y values are stored as value-1.
        uint8_t spriteY = dataY[i] + 1;

        if (screenHeight == 192 && spriteY == 0xD1)
            break;

        if (scanline < spriteY || scanline >= spriteY + (spriteHeight << isSpriteDoubleSize))
            continue;

        if (spriteCount < 8)
        {
            uint8_t spriteX = dataXT[(i * 2)];
            uint8_t spriteTile = dataXT[(i * 2) + 1];
            sprites[spriteCount++] = {spriteY, spriteX, spriteTile};
        }
        else
        {
            Bytes::SetBit<6>(statusRegister);
            break;
        }
    }
}


template <bool SideStatusBar>
void Vdp::DrawScanline(uint16_t scanline)
{
    if (!isDisplayEnabled)
    {
        for (int i = 0; i < 256; i++)
            frameBuffer[(scanline * 256) + i] = 0;
        return;
    }

    int i = 0;
    if (isMaskCol0)
    {
        for (i = 0; i < 8; i++)
        {
            uint8_t color = cram[(regOverscanColor & 0x0F) + 16];
            frameBuffer[(scanline * 256) + i] = ColorTable[color];
        }
    }

    uint8_t y = (scanline + yScrollLatch) % 224;
    uint8_t yTile = y / 8;
    uint8_t yOffset = y & 7;

    for (; i < 256; i++)
    {
        uint8_t x = isTopStatusBar && scanline < 16 ? i : (i - regXScroll) & 0xFF;
        uint8_t xTile = x / 8;
        uint8_t xOffset = x & 7;

        if constexpr (SideStatusBar)
        {
            if (i == 192)
            {
                y = scanline;
                yTile = y / 8;
                yOffset = y & 7;
            }
        }

        uint16_t addr = nameTableBaseAddr | (yTile << 6) | (xTile << 1);
        uint16_t tileIndex = vram[addr];
        uint8_t tileAttr = vram[addr + 1];
        bool flipX = Bytes::TestBit<1>(tileAttr);
        bool flipY = Bytes::TestBit<2>(tileAttr);
        bool highPalette = Bytes::TestBit<3>(tileAttr);
        bool bgPriority = Bytes::TestBit<4>(tileAttr);

        tileIndex |= (tileAttr & 0x01) << 8;

        if (flipX)
            xOffset = 7 - xOffset;
        if (flipY)
            yOffset = 7 - yOffset;

        uint8_t colorIndex = GetPixelColor(tileIndex, xOffset, yOffset);
        uint8_t spriteColorIndex = GetSpritePixelColor(i, scanline);

        if (spriteColorIndex != 0xFF && (!bgPriority || colorIndex == 0))
        {
            colorIndex = spriteColorIndex;
            highPalette = true;
        }

        uint8_t color = cram[colorIndex + (16 * highPalette)];
        frameBuffer[(scanline * 256) + i] = ColorTable[color];
    }
}


}
