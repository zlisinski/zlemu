#include <core/Bytes.h>
#include <core/Logger.h>
#include "Interrupt.h"
#include "Vdp.h"


namespace Sms
{


Vdp::Vdp(Interrupt *interrupt) :
    interrupt(interrupt)
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
        scanline++;
        vCounter++;

        if (scanline < 192)
        {
            DrawScanline();
        }
        else if (scanline == 192)
        {
            // Enter vblank
            Bytes::SetBit<7>(statusRegister);
            if (Bytes::TestBit<5>(regModeControl2))
            {
                interrupt->RequestInterrupt();
            }
        }
        else if (scanline == 219)
        {
            // The value jumps backwards for some reason.
            vCounter -= 6;
        }
        else if (scanline == 262)
        {
            // Exit vblank
            scanline = 0;
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


void Vdp::DrawScanline()
{

}


}
