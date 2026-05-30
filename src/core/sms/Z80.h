#ifndef ZLEMU_CORE_SMS_Z80_H
#define ZLEMU_CORE_SMS_Z80_H

#include "../Bytes.h"
#include "../Zlemu.h"
#include "Memory.h"


namespace Sms
{


enum EFlagMask
{
    CF = 0x01,
    NF = 0x02,
    PF = 0x04,
    VF = 0x04,
    XF = 0x08,
    HF = 0x10,
    YF = 0x20,
    ZF = 0x40,
    SF = 0x80
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
    PAIR(wz, w, z);

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
    enum class IndexType {HL, IX, IY};

    void NotYetImplemented(uint8_t opcode) const;

    uint8_t ReadPC8();
    uint16_t ReadPC16();
    uint8_t FetchOpcode();

    void ReadImm8();
    template <bool WriteWZ = true>
    void ReadImm16();

    uint8_t &GetSrcReg8(uint8_t opcode);
    uint8_t &GetDestReg8(uint8_t opcode);
    uint8_t &GetSrcReg8Unindexed(uint8_t opcode);
    uint8_t &GetDestReg8Unindexed(uint8_t opcode);
    uint16_t &GetReg16(uint8_t opcode);
    uint16_t &GetReg16Stack(uint8_t opcode);
    void SetIndexType(IndexType type);

    template <bool WriteWZ = false>
    uint8_t PtrRead8(uint16_t addr);
    uint16_t PtrRead16(uint16_t addr);
    template <bool PrefixedCB = false>
    uint16_t Indexed();

    template <auto Func, bool PrefixedCB = false>
    void ValWrapper(uint8_t &r, auto&&... args);
    template <auto Func>
    void PtrWrapper(uint16_t addr, auto&&... args);

    void SetXYFlags(uint8_t value);
    template <typename T>
    void SetZSFlags(T value);
    void SetIRFlags();
    bool GetParity(uint8_t value) const;
    template <typename T>
    bool HalfCarry(T op1, T op2, int result) const;

    void LoadRegister8(uint8_t &dest, uint8_t src);
    void LoadRegister16(uint16_t &dest, uint16_t src);
    template <bool WriteWZ = false>
    void LoadPointer8(uint16_t destAddr, uint8_t src);
    void LoadPointer16(uint16_t destAddr, uint16_t src);

    void Push(uint16_t value);
    void Pop(uint16_t &dest);

    void BlockLoad(bool loop);
    void BlockCompare(bool loop);

    void Add8(uint8_t value, bool carry = false);
    void Add16(uint16_t &dest, uint16_t value);
    void Adc16(uint16_t &dest, uint16_t value);
    void Sub8(uint8_t value, bool carry = false);
    void Sbc16(uint16_t &dest, uint16_t value);
    void Inc8(uint8_t &dest);
    void IncPtr8(uint16_t destAddr);
    void Inc16(uint16_t &dest);
    void Dec8(uint8_t &dest);
    void DecPtr8(uint16_t destAddr);
    void Dec16(uint16_t &dest);

    void And(uint8_t value);
    void Or(uint8_t value);
    void Xor(uint8_t value);
    void Cp(uint8_t value);

    void RlcA();
    void RlA();
    uint8_t Rlc(uint8_t value);
    uint8_t Rl(uint8_t value);
    uint8_t Sla(uint8_t value);
    uint8_t Sll(uint8_t value);

    void RrcA();
    void RrA();
    uint8_t Rrc(uint8_t value);
    uint8_t Rr(uint8_t value);
    uint8_t Sra(uint8_t value);
    uint8_t Srl(uint8_t value);

    template <bool IsPtr = false>
    void Bit(uint8_t value, uint8_t bit);
    uint8_t ResBit(uint8_t value, uint8_t bit);
    uint8_t SetBit(uint8_t value, uint8_t bit);

    void ProcessOpcodeED();
    template <bool Prefixed>
    void ProcessOpcodeCB();

    Registers reg;

    IndexType indexType = IndexType::HL;
    uint16_t *index = &reg.hl;
    uint8_t *indexH = &reg.h;
    uint8_t *indexL = &reg.l;
    uint8_t *regTable8[8] = {&reg.b, &reg.c, &reg.d, &reg.e, &reg.h, &reg.l, nullptr, &reg.a};
    uint8_t *regTableUnindexed8[8] = {&reg.b, &reg.c, &reg.d, &reg.e, &reg.h, &reg.l, nullptr, &reg.a};
    uint16_t *regTable16[4] = {&reg.bc, &reg.de, &reg.hl, &reg.sp};
    uint16_t *regTable16Stack[4] = {&reg.bc, &reg.de, &reg.hl, &reg.af};

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