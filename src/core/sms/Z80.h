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


struct Registers
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#define PAIR(NAME, HIGH, LOW) \
    union                     \
    {                         \
        uint16_t NAME = 0;    \
        struct                \
        {                     \
            uint8_t LOW;      \
            uint8_t HIGH;     \
        };\
    }

    union
    {
        uint16_t af = 0xFFFF;
        struct
        {
            union
            {
                uint8_t f;
                struct
                {
                    uint8_t c:1; // Carry
                    uint8_t n:1; // Subtract
                    uint8_t p:1; // Parity/Overflow
                    uint8_t x:1; // Undocumented
                    uint8_t h:1; // Half-carry
                    uint8_t y:1; // Undocumented
                    uint8_t z:1; // Zero
                    uint8_t s:1; // Sign
                } flags;
            };
            uint8_t a;
        };
    };
    PAIR(bc, b, c);
    PAIR(de, d, e);
    PAIR(hl, h, l);
    PAIR(ix, ixh, ixl);
    PAIR(iy, iyh, iyl);

#undef PAIR
#pragma GCC diagnostic pop

    uint16_t af_ = 0xFFFF;
    uint16_t bc_ = 0;
    uint16_t de_ = 0;
    uint16_t hl_ = 0;

    uint8_t i = 0;
    uint8_t r = 0;

    uint16_t pc = 0;
    uint16_t sp = 0xFFFF;
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
    uint8_t FetchOpcode();

    void ReadImm8();
    void ReadImm16();

    uint8_t PtrRead8(uint16_t addr);
    uint16_t PtrRead16(uint16_t addr);
    uint16_t Indexed();

    void LoadRegister8(uint8_t &dest, uint8_t src);
    void LoadRegister16(uint16_t &dest, uint16_t src);
    void LoadPointer8(uint16_t destAddr, uint8_t src);
    void LoadPointer16(uint16_t destAddr, uint16_t src);

    void Push(uint16_t value);
    void Pop(uint16_t &dest);

    void BlockLoad(bool loop);
    void BlockCompare(bool loop);

    void SetAFlags();

    void ProcessOpcodeCB();
    void ProcessOpcodeED();

    Registers reg;
    uint16_t *index = &reg.hl;
    uint8_t *indexH = &reg.h;
    uint8_t *indexL = &reg.l;

    union
    {
        uint8_t operand[2] = {0};
        uint16_t operandWord;
    };
    uint8_t operandCount = 0;

    bool iff1 = false;
    bool iff2 = false;

    Memory *memory = nullptr;
};


}

#endif