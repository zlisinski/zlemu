#ifndef ZLEMU_CORE_SMS_Z80_H
#define ZLEMU_CORE_SMS_Z80_H

#include "../Bytes.h"
#include "../Zlemu.h"
#include "Memory.h"


namespace Sms
{


enum EFlagMask
{
    cf = 0x01,
    nf = 0x02,
    pf = 0x04,
    vf = 0x04,
    xf = 0x08,
    hf = 0x10,
    yf = 0x20,
    zf = 0x40,
    sf = 0x80
};


struct BytePair
{
    uint8_t &high;
    uint8_t &low;

    constexpr BytePair &operator=(uint16_t value) noexcept
    {
        high = Bytes::GetByte<1>(value);
        low = Bytes::GetByte<0>(value);
        return *this;
    }

    constexpr BytePair &operator=(const BytePair &value) noexcept
    {
        high = value.high;
        low = value.low;
        return *this;
    }

    constexpr operator uint16_t() const noexcept
    {
        return Bytes::Make16Bit(high, low);
    }
};


struct Registers
{
    uint8_t a = 0xFF;
    uint8_t f = 0xFF;
    uint8_t b = 0;
    uint8_t c = 0;
    uint8_t d = 0;
    uint8_t e = 0;
    uint8_t h = 0;
    uint8_t l = 0;

    uint8_t a_ = 0xFF;
    uint8_t f_ = 0xFF;
    uint8_t b_ = 0;
    uint8_t c_ = 0;
    uint8_t d_ = 0;
    uint8_t e_ = 0;
    uint8_t h_ = 0;
    uint8_t l_ = 0;

    uint8_t i = 0;
    uint8_t r = 0;

    uint16_t ix = 0;
    uint16_t iy = 0;
    uint16_t pc = 0;
    uint16_t sp = 0xFFFF;

    constexpr BytePair AF() {return {a, f};}
    constexpr BytePair BC() {return {b, c};}
    constexpr BytePair DE() {return {d, e};}
    constexpr BytePair HL() {return {h, l};}
    constexpr BytePair AF_() {return {a_, f_};}
    constexpr BytePair BC_() {return {b_, c_};}
    constexpr BytePair DE_() {return {d_, e_};}
    constexpr BytePair HL_() {return {h_, l_};}
};


class Z80
{
public:
    Z80(Memory *memory);
    ~Z80() = default;

    void Reset();
    void ProcessOpcode();

protected:
    void NotYetImplemented(uint8_t opcode) const;

    uint8_t ReadPC8();
    uint16_t ReadPC16();
    void FetchOpcode();

    void ReadImm8();
    void ReadImm16();

    uint8_t PtrRead8(uint16_t addr);
    uint16_t PtrRead16(uint16_t addr);
    uint16_t Indexed(uint16_t addr);

    void LoadRegister8(uint8_t &dest, uint8_t src);
    void LoadRegister16(BytePair dest, uint16_t src);
    void LoadRegister16(uint16_t &dest, uint16_t src);
    void LoadPointer8(uint16_t destAddr, uint8_t src);
    void LoadPointer16(uint16_t destAddr, uint16_t src);

    void Push(uint16_t value);

    void SetAFlags();

    void ProcessOpcodeCB();
    void ProcessOpcodeDD();
    void ProcessOpcodeDDCB();
    void ProcessOpcodeED();
    void ProcessOpcodeFD();
    void ProcessOpcodeFDCB();

    Registers reg;

    uint8_t opcode[3] = {0};
    uint8_t opcodeCount = 0;
    uint8_t operand[2] = {0};
    constexpr BytePair OperandWord() {return BytePair{operand[1], operand[0]};}

    bool iff1 = false;
    bool iff2 = false;

    Memory *memory = nullptr;
};


}

#endif