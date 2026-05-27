#include <stdexcept>

#include "../Bytes.h"
#include "../Utils.h"
#include "Z80.h"


namespace Sms
{


Z80::Z80(Memory *memory) :
    memory(memory)
{
}


void Z80::Reset()
{
}


inline uint8_t Z80::ReadPC8()
{
    uint8_t byte = memory->ReadByte(reg.pc++);
    return byte;
}


inline uint16_t Z80::ReadPC16()
{
    uint8_t low = ReadPC8();
    uint8_t high = ReadPC8();
    return Bytes::Make16Bit(high, low);
}


inline uint8_t Z80::FetchOpcode()
{
    // Increment r, but keep the top bit.
    reg.r = (reg.r & 0x80) | ((reg.r + 1) & 0x7F);

    return ReadPC8();
}


inline void Z80::ReadImm8()
{
    operand[operandCount++] = ReadPC8();
}


inline void Z80::ReadImm16()
{
    ReadImm8();
    ReadImm8();
}


inline uint8_t Z80::PtrRead8(uint16_t addr)
{
    return memory->ReadByte(addr);
}


inline uint16_t Z80::PtrRead16(uint16_t addr)
{
    return memory->ReadWord(addr);
}


template <bool PrefixedCB>
inline uint16_t Z80::Indexed()
{
    if (index == &reg.hl)
        return *index;

    // Prefixed CB instructions already read the displacement.
    if constexpr (!PrefixedCB)
        ReadImm8();

    return *index + static_cast<int8_t>(operand[0]);
}


template <uint8_t (Z80::*func)(uint8_t), bool PrefixedCB>
inline void Z80::ValWrapper(uint8_t &r)
{
    if constexpr (PrefixedCB)
    {
        uint16_t addr = Indexed<PrefixedCB>();
        r = PtrRead8(addr);
        r = (this->*func)(r);
        LoadPointer8(addr, r);
    }
    else
    {
        r = (this->*func)(r);
    }
}


template <uint8_t (Z80::*func)(uint8_t)>
inline void Z80::PtrWrapper(uint16_t addr)
{
    uint8_t value = PtrRead8(addr);
    value = (this->*func)(value);
    LoadPointer8(addr, value);
}


inline void Z80::SetXYFlags(uint8_t value)
{
    reg.flags.x = Bytes::TestBit<3>(value);
    reg.flags.y = Bytes::TestBit<5>(value);
}


template <typename T>
inline void Z80::SetZSFlags(T value)
{
    reg.flags.z = value == 0;
    reg.flags.s = Bytes::TestBit<(sizeof(T) * 8) - 1>(value);
}


inline void Z80::SetIRFlags()
{
    reg.flags.n = 0;
    reg.flags.p = iff2;
    reg.flags.h = 0;
    SetXYFlags(reg.a);
    SetZSFlags(reg.a);
}


inline bool Z80::GetParity(uint8_t value) const
{
    value ^= value >> 4;
    value ^= value >> 2;
    value ^= value >> 1;
    return !(value & 1);
}


template <typename T>
inline bool Z80::HalfCarry(T op1, T op2, int result) const
{
    return (op1 ^ op2 ^ result) & (0x10 << (sizeof(T) - 1) * 8);
}


inline void Z80::LoadRegister8(uint8_t &dest, uint8_t src)
{
    dest = src;
}


inline void Z80::LoadRegister16(uint16_t &dest, uint16_t src)
{
    dest = src;
}


inline void Z80::LoadPointer8(uint16_t destAddr, uint8_t src)
{
    memory->WriteByte(destAddr, src);
}


inline void Z80::LoadPointer16(uint16_t destAddr, uint16_t src)
{
    memory->WriteWord(destAddr, src);
}


inline void Z80::Push(uint16_t value)
{
    reg.sp--;
    memory->WriteByte(reg.sp, Bytes::GetByte<1>(value));
    reg.sp--;
    memory->WriteByte(reg.sp, Bytes::GetByte<0>(value));
}


inline void Z80::Pop(uint16_t &dest)
{
    uint8_t low = memory->ReadByte(reg.sp);
    reg.sp++;
    uint8_t high = memory->ReadByte(reg.sp);
    reg.sp++;
    dest = Bytes::Make16Bit(high, low);
}


inline void Z80::BlockLoad(bool loop)
{
    uint8_t byte = memory->ReadByte(reg.hl);
    memory->WriteByte(reg.de, byte);

    reg.bc--;

    reg.flags.n = 0;
    reg.flags.p = reg.bc != 0;
    reg.flags.x = Bytes::TestBit<3>(reg.a + byte);
    reg.flags.h = 0;
    reg.flags.y = Bytes::TestBit<1>(reg.a + byte);

    if (reg.bc && loop)
    {
        reg.pc -= 2;
        SetXYFlags(reg.pc >> 8);
    }
}


inline void Z80::BlockCompare(bool loop)
{
    uint8_t byte = memory->ReadByte(reg.hl);
    uint8_t result = reg.a - byte;

    reg.bc--;

    reg.flags.n = 1;
    reg.flags.p = reg.bc != 0;
    reg.flags.h = HalfCarry(reg.a, byte, result);
    reg.flags.x = Bytes::TestBit<3>(result - reg.flags.h);
    reg.flags.y = Bytes::TestBit<1>(result - reg.flags.h);
    SetZSFlags(result);

    if (reg.bc && !reg.flags.z && loop)
    {
        reg.pc -= 2;
        SetXYFlags(reg.pc >> 8);
    }
}


inline void Z80::Add8(uint8_t value, bool carry)
{
    uint16_t result = reg.a + value + carry;

    reg.flags.c = result > 0xFF;
    reg.flags.n = 0;
    reg.flags.p = Bytes::TestBit<7>((reg.a ^ result) & ~(reg.a ^ value));
    reg.flags.h = HalfCarry(reg.a, value, result);
    SetXYFlags(result);
    SetZSFlags((uint8_t)result);

    reg.a = result;
}


inline void Z80::Add16(uint16_t &dest, uint16_t value)
{
    int32_t result = dest + value;

    reg.flags.c = result > 0xFFFF;
    reg.flags.n = 0;
    reg.flags.h = HalfCarry(dest, value, result);
    SetXYFlags(result >> 8);

    dest = result;
}


inline void Z80::Adc16(uint16_t &dest, uint16_t value)
{
    int32_t result = dest + value + reg.flags.c;

    reg.flags.c = result > 0xFFFF;
    reg.flags.n = 0;
    reg.flags.p = Bytes::TestBit<15>((dest ^ result) & ~(dest ^ value));
    reg.flags.h = HalfCarry(dest, value, result);
    SetXYFlags(result >> 8);
    SetZSFlags((uint16_t)result);

    dest = result;
}


inline void Z80::Sub8(uint8_t value, bool carry)
{
    int16_t result = reg.a - value - carry;

    reg.flags.c = result < 0;
    reg.flags.n = 1;
    reg.flags.p = Bytes::TestBit<7>((reg.a ^ result) & (reg.a ^ value));
    reg.flags.h = HalfCarry(reg.a, value, result);
    SetXYFlags(result);
    SetZSFlags((uint8_t)result);

    reg.a = Bytes::GetByte<0>(result);
}


void Z80::Sbc16(uint16_t &dest, uint16_t value)
{
    int32_t result = dest - value - reg.flags.c;

    reg.flags.c = result < 0;
    reg.flags.n = 1;
    reg.flags.p = Bytes::TestBit<15>((dest ^ result) & (dest ^ value));
    reg.flags.h = HalfCarry(dest, value, result);
    SetXYFlags(result >> 8);
    SetZSFlags((uint16_t)result);

    dest = result;
}


inline void Z80::Inc8(uint8_t &dest)
{
    uint8_t result = dest + 1;

    reg.flags.n = 0;
    reg.flags.p = dest == 0x7F;
    reg.flags.h = HalfCarry(dest, (uint8_t)1, result);
    SetXYFlags(result);
    SetZSFlags(result);

    dest = result;
}


inline void Z80::IncPtr8(uint16_t destAddr)
{
    uint8_t src = PtrRead8(destAddr);
    uint8_t result = src + 1;

    reg.flags.n = 0;
    reg.flags.p = src == 0x7F;
    reg.flags.h = HalfCarry(src, (uint8_t)1, result);
    SetXYFlags(result);
    SetZSFlags(result);

    memory->WriteByte(destAddr, result);
}


inline void Z80::Inc16(uint16_t &dest)
{
    dest++;
}


inline void Z80::Dec8(uint8_t &dest)
{
    uint8_t result = dest - 1;

    reg.flags.n = 1;
    reg.flags.p = dest == 0x80;
    reg.flags.h = HalfCarry(dest, (uint8_t)1, result);
    SetXYFlags(result);
    SetZSFlags(result);

    dest = result;
}


inline void Z80::DecPtr8(uint16_t destAddr)
{
    uint8_t src = PtrRead8(destAddr);
    uint8_t result = src - 1;

    reg.flags.n = 1;
    reg.flags.p = src == 0x80;
    reg.flags.h = HalfCarry(src, (uint8_t)1, result);
    SetXYFlags(result);
    SetZSFlags(result);

    memory->WriteByte(destAddr, result);
}


inline void Z80::Dec16(uint16_t &dest)
{
    dest--;
}


inline void Z80::And(uint8_t value)
{
    uint8_t result = reg.a & value;

    reg.flags.c = 0;
    reg.flags.n = 0;
    reg.flags.p = GetParity(result);
    reg.flags.h = 1;
    SetXYFlags(result);
    SetZSFlags(result);

    reg.a  = result;
}


inline void Z80::Or(uint8_t value)
{
    uint8_t result = reg.a | value;

    reg.flags.c = 0;
    reg.flags.n = 0;
    reg.flags.p = GetParity(result);
    reg.flags.h = 0;
    SetXYFlags(result);
    SetZSFlags(result);

    reg.a  = result;
}


inline void Z80::Xor(uint8_t value)
{
    uint8_t result = reg.a ^ value;

    reg.flags.c = 0;
    reg.flags.n = 0;
    reg.flags.p = GetParity(result);
    reg.flags.h = 0;
    SetXYFlags(result);
    SetZSFlags(result);

    reg.a  = result;
}


inline void Z80::Cp(uint8_t value)
{
    int16_t result = reg.a - value;

    reg.flags.c = result < 0;
    reg.flags.n = 1;
    reg.flags.p = Bytes::TestBit<7>((reg.a ^ result) & (reg.a ^ value));
    reg.flags.h = HalfCarry(reg.a, value, result);
    SetXYFlags(value);
    SetZSFlags((uint8_t)result);
}


inline void Z80::RlcA()
{
    reg.flags.c = Bytes::TestBit<7>(reg.a);
    reg.a = (reg.a << 1) | reg.flags.c;

    reg.flags.n = 0;
    reg.flags.h = 0;
    SetXYFlags(reg.a);
}


inline void Z80::RlA()
{
    uint8_t oldCarry = reg.flags.c;
    reg.flags.c = Bytes::TestBit<7>(reg.a);
    reg.a = (reg.a << 1) | oldCarry;

    reg.flags.n = 0;
    reg.flags.h = 0;
    SetXYFlags(reg.a);
}


inline uint8_t Z80::Rlc(uint8_t value)
{
    reg.flags.c = Bytes::TestBit<7>(value);
    value = (value << 1) | reg.flags.c;

    reg.flags.n = 0;
    reg.flags.p = GetParity(value);
    reg.flags.h = 0;
    SetXYFlags(value);
    SetZSFlags(value);

    return value;
}


inline uint8_t Z80::Rl(uint8_t value)
{
    uint8_t oldCarry = reg.flags.c;
    reg.flags.c = Bytes::TestBit<7>(value);
    value = (value << 1) | oldCarry;

    reg.flags.n = 0;
    reg.flags.p = GetParity(value);
    reg.flags.h = 0;
    SetXYFlags(value);
    SetZSFlags(value);

    return value;
}


inline uint8_t Z80::Sla(uint8_t value)
{
    reg.flags.c = Bytes::TestBit<7>(value);
    value <<= 1;

    reg.flags.n = 0;
    reg.flags.p = GetParity(value);
    reg.flags.h = 0;
    SetXYFlags(value);
    SetZSFlags(value);

    return value;
}


inline uint8_t Z80::Sll(uint8_t value)
{
    reg.flags.c = Bytes::TestBit<7>(value);
    value = (value << 1) | 0x01;

    reg.flags.n = 0;
    reg.flags.p = GetParity(value);
    reg.flags.h = 0;
    SetXYFlags(value);
    SetZSFlags(value);

    return value;
}


inline void Z80::RrcA()
{
    reg.flags.c = Bytes::TestBit<0>(reg.a);
    reg.a = (reg.a >> 1) | (reg.flags.c << 7);

    reg.flags.n = 0;
    reg.flags.h = 0;
    SetXYFlags(reg.a);
}


inline void Z80::RrA()
{
    uint8_t oldCarry = reg.flags.c;
    reg.flags.c = Bytes::TestBit<0>(reg.a);
    reg.a = (reg.a >> 1) | (oldCarry << 7);

    reg.flags.n = 0;
    reg.flags.h = 0;
    SetXYFlags(reg.a);
}


inline uint8_t Z80::Rrc(uint8_t value)
{
    reg.flags.c = Bytes::TestBit<0>(value);
    value = value >> 1 | (reg.flags.c << 7);

    reg.flags.n = 0;
    reg.flags.p = GetParity(value);
    reg.flags.h = 0;
    SetXYFlags(value);
    SetZSFlags(value);

    return value;
}


inline uint8_t Z80::Rr(uint8_t value)
{
    uint8_t oldCarry = reg.flags.c;
    reg.flags.c = Bytes::TestBit<0>(value);
    value = (value >> 1) | (oldCarry << 7);

    reg.flags.n = 0;
    reg.flags.p = GetParity(value);
    reg.flags.h = 0;
    SetXYFlags(value);
    SetZSFlags(value);

    return value;
}


uint8_t Z80::Sra(uint8_t value)
{
    reg.flags.c = Bytes::TestBit<0>(value);
    value = static_cast<int8_t>(value) >> 1;

    reg.flags.n = 0;
    reg.flags.p = GetParity(value);
    reg.flags.h = 0;
    SetXYFlags(value);
    SetZSFlags(value);

    return value;
}


uint8_t Z80::Srl(uint8_t value)
{
    reg.flags.c = Bytes::TestBit<0>(value);
    value >>= 1;

    reg.flags.n = 0;
    reg.flags.p = GetParity(value);
    reg.flags.h = 0;
    SetXYFlags(value);
    SetZSFlags(value);

    return value;
}


void Z80::ProcessOpcode()
{
    uint8_t opcode = FetchOpcode();

    operandCount = 0;
    index = &reg.hl;
    indexH = &reg.h;
    indexL = &reg.l;

    // Multiple prefix bytes are allowed and just overwrite the previous one.
    while (opcode == 0xDD || opcode == 0xFD)
    {
        if (opcode == 0xDD)
        {
            index = &reg.ix;
            indexH = &reg.ixh;
            indexL = &reg.ixl;
        }
        else
        {
            index = &reg.iy;
            indexH = &reg.iyh;
            indexL = &reg.iyl;
        }
        opcode = FetchOpcode();
    }

    if (opcode == 0xCB)
    {
        if (index != &reg.hl)
            ProcessOpcodeCB<true>();
        else
            ProcessOpcodeCB<false>();

        return;
    }
    if (opcode == 0xED)
    {
        // 0xED ignores any previously set prefix.
        index = &reg.hl;
        indexH = &reg.h;
        indexL = &reg.l;
        ProcessOpcodeED();
        return;
    }

    switch (opcode)
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register, Register
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x40: LoadRegister8(reg.b, reg.b); break;
        case 0x41: LoadRegister8(reg.b, reg.c); break;
        case 0x42: LoadRegister8(reg.b, reg.d); break;
        case 0x43: LoadRegister8(reg.b, reg.e); break;
        case 0x44: LoadRegister8(reg.b, *indexH); break;
        case 0x45: LoadRegister8(reg.b, *indexL); break;
        case 0x47: LoadRegister8(reg.b, reg.a); break;
        case 0x48: LoadRegister8(reg.c, reg.b); break;
        case 0x49: LoadRegister8(reg.c, reg.c); break;
        case 0x4A: LoadRegister8(reg.c, reg.d); break;
        case 0x4B: LoadRegister8(reg.c, reg.e); break;
        case 0x4C: LoadRegister8(reg.c, *indexH); break;
        case 0x4D: LoadRegister8(reg.c, *indexL); break;
        case 0x4F: LoadRegister8(reg.c, reg.a); break;
        case 0x50: LoadRegister8(reg.d, reg.b); break;
        case 0x51: LoadRegister8(reg.d, reg.c); break;
        case 0x52: LoadRegister8(reg.d, reg.d); break;
        case 0x53: LoadRegister8(reg.d, reg.e); break;
        case 0x54: LoadRegister8(reg.d, *indexH); break;
        case 0x55: LoadRegister8(reg.d, *indexL); break;
        case 0x57: LoadRegister8(reg.d, reg.a); break;
        case 0x58: LoadRegister8(reg.e, reg.b); break;
        case 0x59: LoadRegister8(reg.e, reg.c); break;
        case 0x5A: LoadRegister8(reg.e, reg.d); break;
        case 0x5B: LoadRegister8(reg.e, reg.e); break;
        case 0x5C: LoadRegister8(reg.e, *indexH); break;
        case 0x5D: LoadRegister8(reg.e, *indexL); break;
        case 0x5F: LoadRegister8(reg.e, reg.a); break;
        case 0x60: LoadRegister8(*indexH, reg.b); break;
        case 0x61: LoadRegister8(*indexH, reg.c); break;
        case 0x62: LoadRegister8(*indexH, reg.d); break;
        case 0x63: LoadRegister8(*indexH, reg.e); break;
        case 0x64: LoadRegister8(*indexH, *indexH); break;
        case 0x65: LoadRegister8(*indexH, *indexL); break;
        case 0x67: LoadRegister8(*indexH, reg.a); break;
        case 0x68: LoadRegister8(*indexL, reg.b); break;
        case 0x69: LoadRegister8(*indexL, reg.c); break;
        case 0x6A: LoadRegister8(*indexL, reg.d); break;
        case 0x6B: LoadRegister8(*indexL, reg.e); break;
        case 0x6C: LoadRegister8(*indexL, *indexH); break;
        case 0x6D: LoadRegister8(*indexL, *indexL); break;
        case 0x6F: LoadRegister8(*indexL, reg.a); break;
        case 0x78: LoadRegister8(reg.a, reg.b); break;
        case 0x79: LoadRegister8(reg.a, reg.c); break;
        case 0x7A: LoadRegister8(reg.a, reg.d); break;
        case 0x7B: LoadRegister8(reg.a, reg.e); break;
        case 0x7C: LoadRegister8(reg.a, *indexH); break;
        case 0x7D: LoadRegister8(reg.a, *indexL); break;
        case 0x7F: LoadRegister8(reg.a, reg.a); break;
        case 0xF9: LoadRegister16(reg.sp, *index); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register, Immediate
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x06: ReadImm8(); LoadRegister8(reg.b, operand[0]); break;
        case 0x0E: ReadImm8(); LoadRegister8(reg.c, operand[0]); break;
        case 0x16: ReadImm8(); LoadRegister8(reg.d, operand[0]); break;
        case 0x1E: ReadImm8(); LoadRegister8(reg.e, operand[0]); break;
        case 0x26: ReadImm8(); LoadRegister8(*indexH, operand[0]); break;
        case 0x2E: ReadImm8(); LoadRegister8(*indexL, operand[0]); break;
        case 0x3E: ReadImm8(); LoadRegister8(reg.a, operand[0]); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register, Pointer
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x46: LoadRegister8(reg.b, PtrRead8(Indexed())); break;
        case 0x4E: LoadRegister8(reg.c, PtrRead8(Indexed())); break;
        case 0x56: LoadRegister8(reg.d, PtrRead8(Indexed())); break;
        case 0x5E: LoadRegister8(reg.e, PtrRead8(Indexed())); break;
        case 0x66: LoadRegister8(reg.h, PtrRead8(Indexed())); break;
        case 0x6E: LoadRegister8(reg.l, PtrRead8(Indexed())); break;
        case 0x7E: LoadRegister8(reg.a, PtrRead8(Indexed())); break;
        case 0x0A: LoadRegister8(reg.a, PtrRead8(reg.bc)); break;
        case 0x1A: LoadRegister8(reg.a, PtrRead8(reg.de)); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Pointer, Register
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x70: LoadPointer8(Indexed(), reg.b); break;
        case 0x71: LoadPointer8(Indexed(), reg.c); break;
        case 0x72: LoadPointer8(Indexed(), reg.d); break;
        case 0x73: LoadPointer8(Indexed(), reg.e); break;
        case 0x74: LoadPointer8(Indexed(), reg.h); break;
        case 0x75: LoadPointer8(Indexed(), reg.l); break;
        case 0x77: LoadPointer8(Indexed(), reg.a); break;
        case 0x02: LoadPointer8(reg.bc, reg.a); break;
        case 0x12: LoadPointer8(reg.de, reg.a); break;
        case 0x32: ReadImm16(); LoadPointer8(operandWord, reg.a); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Pointer, Immediate
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x36:
        {
            uint16_t addr = Indexed(); // DD or FD prefixes will call ReadImm8().
            ReadImm8();
            LoadPointer8(addr, operand[operandCount - 1]);
            break;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register, Immediate Pointer
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x3A: ReadImm16(); LoadRegister8(reg.a, PtrRead8(operandWord)); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register Pair, Immediate Word
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x01: ReadImm16(); LoadRegister16(reg.bc, operandWord); break;
        case 0x11: ReadImm16(); LoadRegister16(reg.de, operandWord); break;
        case 0x21: ReadImm16(); LoadRegister16(*index, operandWord); break;
        case 0x31: ReadImm16(); LoadRegister16(reg.sp, operandWord); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register Pair, Immediate Pointer
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x2A: ReadImm16(); LoadRegister16(*index, PtrRead16(operandWord)); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Immediate Pointer Word, Register Pair
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x22: ReadImm16(); LoadPointer16(operandWord, *index); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Stack
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0xC5: Push(reg.bc); break;
        case 0xD5: Push(reg.de); break;
        case 0xE5: Push(*index); break;
        case 0xF5: Push(reg.af); break;
        case 0xC1: Pop(reg.bc); break;
        case 0xD1: Pop(reg.de); break;
        case 0xE1: Pop(*index); break;
        case 0xF1: Pop(reg.af); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Exchange
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0xEB: std::swap(reg.de, reg.hl); break;
        case 0x08: std::swap(reg.af, reg.af_); break;
        case 0xD9:
            std::swap(reg.bc, reg.bc_);
            std::swap(reg.de, reg.de_);
            std::swap(reg.hl, reg.hl_);
            break;
        case 0xE3:
        {
            uint16_t old = *index;
            *index = memory->ReadWord(reg.sp);
            memory->WriteWord(reg.sp, old);
            break;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Arithmetic
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x80: Add8(reg.b); break;
        case 0x81: Add8(reg.c); break;
        case 0x82: Add8(reg.d); break;
        case 0x83: Add8(reg.e); break;
        case 0x84: Add8(*indexH); break;
        case 0x85: Add8(*indexL); break;
        case 0x86: Add8(PtrRead8(Indexed())); break;
        case 0x87: Add8(reg.a); break;
        case 0xC6: ReadImm8(); Add8(operand[0]); break;
        case 0x09: Add16(*index, reg.bc); break;
        case 0x19: Add16(*index, reg.de); break;
        case 0x29: Add16(*index, *index); break;
        case 0x39: Add16(*index, reg.sp); break;

        case 0x88: Add8(reg.b, reg.flags.c); break;
        case 0x89: Add8(reg.c, reg.flags.c); break;
        case 0x8A: Add8(reg.d, reg.flags.c); break;
        case 0x8B: Add8(reg.e, reg.flags.c); break;
        case 0x8C: Add8(*indexH, reg.flags.c); break;
        case 0x8D: Add8(*indexL, reg.flags.c); break;
        case 0x8E: Add8(PtrRead8(Indexed()), reg.flags.c); break;
        case 0x8F: Add8(reg.a, reg.flags.c); break;
        case 0xCE: ReadImm8(); Add8(operand[0], reg.flags.c); break;

        case 0x90: Sub8(reg.b); break;
        case 0x91: Sub8(reg.c); break;
        case 0x92: Sub8(reg.d); break;
        case 0x93: Sub8(reg.e); break;
        case 0x94: Sub8(*indexH); break;
        case 0x95: Sub8(*indexL); break;
        case 0x96: Sub8(PtrRead8(Indexed())); break;
        case 0x97: Sub8(reg.a); break;
        case 0xD6: ReadImm8(); Sub8(operand[0]); break;

        case 0x98: Sub8(reg.b, reg.flags.c); break;
        case 0x99: Sub8(reg.c, reg.flags.c); break;
        case 0x9A: Sub8(reg.d, reg.flags.c); break;
        case 0x9B: Sub8(reg.e, reg.flags.c); break;
        case 0x9C: Sub8(*indexH, reg.flags.c); break;
        case 0x9D: Sub8(*indexL, reg.flags.c); break;
        case 0x9E: Sub8(PtrRead8(Indexed()), reg.flags.c); break;
        case 0x9F: Sub8(reg.a, reg.flags.c); break;
        case 0xDE: ReadImm8(); Sub8(operand[0], reg.flags.c); break;

        case 0x04: Inc8(reg.b); break;
        case 0x0C: Inc8(reg.c); break;
        case 0x14: Inc8(reg.d); break;
        case 0x1C: Inc8(reg.e); break;
        case 0x24: Inc8(*indexH); break;
        case 0x2C: Inc8(*indexL); break;
        case 0x34: IncPtr8(Indexed()); break;
        case 0x3C: Inc8(reg.a); break;
        case 0x03: Inc16(reg.bc); break;
        case 0x13: Inc16(reg.de); break;
        case 0x23: Inc16(*index); break;
        case 0x33: Inc16(reg.sp); break;

        case 0x05: Dec8(reg.b); break;
        case 0x0D: Dec8(reg.c); break;
        case 0x15: Dec8(reg.d); break;
        case 0x1D: Dec8(reg.e); break;
        case 0x25: Dec8(*indexH); break;
        case 0x2D: Dec8(*indexL); break;
        case 0x35: DecPtr8(Indexed()); break;
        case 0x3D: Dec8(reg.a); break;
        case 0x0B: Dec16(reg.bc); break;
        case 0x1B: Dec16(reg.de); break;
        case 0x2B: Dec16(*index); break;
        case 0x3B: Dec16(reg.sp); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Logic
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0xA0: And(reg.b); break;
        case 0xA1: And(reg.c); break;
        case 0xA2: And(reg.d); break;
        case 0xA3: And(reg.e); break;
        case 0xA4: And(*indexH); break;
        case 0xA5: And(*indexL); break;
        case 0xA6: And(PtrRead8(Indexed())); break;
        case 0xA7: And(reg.a); break;
        case 0xE6: ReadImm8(); And(operand[0]); break;

        case 0xB0: Or(reg.b); break;
        case 0xB1: Or(reg.c); break;
        case 0xB2: Or(reg.d); break;
        case 0xB3: Or(reg.e); break;
        case 0xB4: Or(*indexH); break;
        case 0xB5: Or(*indexL); break;
        case 0xB6: Or(PtrRead8(Indexed())); break;
        case 0xB7: Or(reg.a); break;
        case 0xF6: ReadImm8(); Or(operand[0]); break;

        case 0xA8: Xor(reg.b); break;
        case 0xA9: Xor(reg.c); break;
        case 0xAA: Xor(reg.d); break;
        case 0xAB: Xor(reg.e); break;
        case 0xAC: Xor(*indexH); break;
        case 0xAD: Xor(*indexL); break;
        case 0xAE: Xor(PtrRead8(Indexed())); break;
        case 0xAF: Xor(reg.a); break;
        case 0xEE: ReadImm8(); Xor(operand[0]); break;

        case 0xB8: Cp(reg.b); break;
        case 0xB9: Cp(reg.c); break;
        case 0xBA: Cp(reg.d); break;
        case 0xBB: Cp(reg.e); break;
        case 0xBC: Cp(*indexH); break;
        case 0xBD: Cp(*indexL); break;
        case 0xBE: Cp(PtrRead8(Indexed())); break;
        case 0xBF: Cp(reg.a); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Rotate & Shift
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x07: RlcA(); break;
        case 0x17: RlA(); break;
        case 0x0F: RrcA(); break;
        case 0x1F: RrA(); break;

        default: NotYetImplemented(opcode); break;
    }
}


void Z80::ProcessOpcodeED()
{
    uint8_t opcode = FetchOpcode();

    switch (opcode)
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register, Register
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x47: LoadRegister8(reg.i, reg.a); break;
        case 0x4F: LoadRegister8(reg.r, reg.a); break;
        case 0x57: LoadRegister8(reg.a, reg.i); SetIRFlags(); break;
        case 0x5F: LoadRegister8(reg.a, reg.r); SetIRFlags(); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register Pair, Immediate Pointer
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x4B: ReadImm16(); LoadRegister16(reg.bc, PtrRead16(operandWord)); break;
        case 0x5B: ReadImm16(); LoadRegister16(reg.de, PtrRead16(operandWord)); break;
        case 0x6B: ReadImm16(); LoadRegister16(reg.hl, PtrRead16(operandWord)); break;
        case 0x7B: ReadImm16(); LoadRegister16(reg.sp, PtrRead16(operandWord)); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Immediate Pointer Word, Register Pair
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x43: ReadImm16(); LoadPointer16(operandWord, reg.bc); break;
        case 0x53: ReadImm16(); LoadPointer16(operandWord, reg.de); break;
        case 0x63: ReadImm16(); LoadPointer16(operandWord, reg.hl); break;
        case 0x73: ReadImm16(); LoadPointer16(operandWord, reg.sp); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Block Transfer
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0xA0: BlockLoad(false); reg.de++; reg.hl++; break;
        case 0xB0: BlockLoad(true); reg.de++; reg.hl++; break;
        case 0xA8: BlockLoad(false); reg.de--; reg.hl--; break;
        case 0xB8: BlockLoad(true); reg.de--; reg.hl--; break;
        case 0xA1: BlockCompare(false); reg.hl++; break;
        case 0xB1: BlockCompare(true); reg.hl++; break;
        case 0xA9: BlockCompare(false); reg.hl--; break;
        case 0xB9: BlockCompare(true); reg.hl--; break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Arithmetic
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x4A: Adc16(reg.hl, reg.bc); break;
        case 0x5A: Adc16(reg.hl, reg.de); break;
        case 0x6A: Adc16(reg.hl, reg.hl); break;
        case 0x7A: Adc16(reg.hl, reg.sp); break;

        case 0x42: Sbc16(reg.hl, reg.bc); break;
        case 0x52: Sbc16(reg.hl, reg.de); break;
        case 0x62: Sbc16(reg.hl, reg.hl); break;
        case 0x72: Sbc16(reg.hl, reg.sp); break;

        default: NotYetImplemented(opcode); break;
    }
}


template <bool Prefixed>
void Z80::ProcessOpcodeCB()
{
    uint8_t opcode;

    if constexpr (Prefixed)
    {
        // DD/FD CB opcodes always have a displacement byte before the final opcode byte.
        ReadImm8();

        // Don't use FetchOpcode, since that increments the r register.
        opcode = ReadPC8();
    }
    else
    {
        opcode = FetchOpcode();
    }

    switch (opcode)
    {
        case 0x00: ValWrapper<&Z80::Rlc, Prefixed>(reg.b); break;
        case 0x01: ValWrapper<&Z80::Rlc, Prefixed>(reg.c); break;
        case 0x02: ValWrapper<&Z80::Rlc, Prefixed>(reg.d); break;
        case 0x03: ValWrapper<&Z80::Rlc, Prefixed>(reg.e); break;
        case 0x04: ValWrapper<&Z80::Rlc, Prefixed>(reg.h); break;
        case 0x05: ValWrapper<&Z80::Rlc, Prefixed>(reg.l); break;
        case 0x06: PtrWrapper<&Z80::Rlc>(Indexed<Prefixed>()); break;
        case 0x07: ValWrapper<&Z80::Rlc, Prefixed>(reg.a); break;

        case 0x10: ValWrapper<&Z80::Rl, Prefixed>(reg.b); break;
        case 0x11: ValWrapper<&Z80::Rl, Prefixed>(reg.c); break;
        case 0x12: ValWrapper<&Z80::Rl, Prefixed>(reg.d); break;
        case 0x13: ValWrapper<&Z80::Rl, Prefixed>(reg.e); break;
        case 0x14: ValWrapper<&Z80::Rl, Prefixed>(reg.h); break;
        case 0x15: ValWrapper<&Z80::Rl, Prefixed>(reg.l); break;
        case 0x16: PtrWrapper<&Z80::Rl>(Indexed<Prefixed>()); break;
        case 0x17: ValWrapper<&Z80::Rl, Prefixed>(reg.a); break;

        case 0x20: ValWrapper<&Z80::Sla, Prefixed>(reg.b); break;
        case 0x21: ValWrapper<&Z80::Sla, Prefixed>(reg.c); break;
        case 0x22: ValWrapper<&Z80::Sla, Prefixed>(reg.d); break;
        case 0x23: ValWrapper<&Z80::Sla, Prefixed>(reg.e); break;
        case 0x24: ValWrapper<&Z80::Sla, Prefixed>(reg.h); break;
        case 0x25: ValWrapper<&Z80::Sla, Prefixed>(reg.l); break;
        case 0x26: PtrWrapper<&Z80::Sla>(Indexed<Prefixed>()); break;
        case 0x27: ValWrapper<&Z80::Sla, Prefixed>(reg.a); break;

        case 0x30: ValWrapper<&Z80::Sll, Prefixed>(reg.b); break;
        case 0x31: ValWrapper<&Z80::Sll, Prefixed>(reg.c); break;
        case 0x32: ValWrapper<&Z80::Sll, Prefixed>(reg.d); break;
        case 0x33: ValWrapper<&Z80::Sll, Prefixed>(reg.e); break;
        case 0x34: ValWrapper<&Z80::Sll, Prefixed>(reg.h); break;
        case 0x35: ValWrapper<&Z80::Sll, Prefixed>(reg.l); break;
        case 0x36: PtrWrapper<&Z80::Sll>(Indexed<Prefixed>()); break;
        case 0x37: ValWrapper<&Z80::Sll, Prefixed>(reg.a); break;

        case 0x08: ValWrapper<&Z80::Rrc, Prefixed>(reg.b); break;
        case 0x09: ValWrapper<&Z80::Rrc, Prefixed>(reg.c); break;
        case 0x0A: ValWrapper<&Z80::Rrc, Prefixed>(reg.d); break;
        case 0x0B: ValWrapper<&Z80::Rrc, Prefixed>(reg.e); break;
        case 0x0C: ValWrapper<&Z80::Rrc, Prefixed>(reg.h); break;
        case 0x0D: ValWrapper<&Z80::Rrc, Prefixed>(reg.l); break;
        case 0x0E: PtrWrapper<&Z80::Rrc>(Indexed<Prefixed>()); break;
        case 0x0F: ValWrapper<&Z80::Rrc, Prefixed>(reg.a); break;

        case 0x18: ValWrapper<&Z80::Rr, Prefixed>(reg.b); break;
        case 0x19: ValWrapper<&Z80::Rr, Prefixed>(reg.c); break;
        case 0x1A: ValWrapper<&Z80::Rr, Prefixed>(reg.d); break;
        case 0x1B: ValWrapper<&Z80::Rr, Prefixed>(reg.e); break;
        case 0x1C: ValWrapper<&Z80::Rr, Prefixed>(reg.h); break;
        case 0x1D: ValWrapper<&Z80::Rr, Prefixed>(reg.l); break;
        case 0x1E: PtrWrapper<&Z80::Rr>(Indexed<Prefixed>()); break;
        case 0x1F: ValWrapper<&Z80::Rr, Prefixed>(reg.a); break;

        case 0x28: ValWrapper<&Z80::Sra, Prefixed>(reg.b); break;
        case 0x29: ValWrapper<&Z80::Sra, Prefixed>(reg.c); break;
        case 0x2A: ValWrapper<&Z80::Sra, Prefixed>(reg.d); break;
        case 0x2B: ValWrapper<&Z80::Sra, Prefixed>(reg.e); break;
        case 0x2C: ValWrapper<&Z80::Sra, Prefixed>(reg.h); break;
        case 0x2D: ValWrapper<&Z80::Sra, Prefixed>(reg.l); break;
        case 0x2E: PtrWrapper<&Z80::Sra>(Indexed<Prefixed>()); break;
        case 0x2F: ValWrapper<&Z80::Sra, Prefixed>(reg.a); break;

        case 0x38: ValWrapper<&Z80::Srl, Prefixed>(reg.b); break;
        case 0x39: ValWrapper<&Z80::Srl, Prefixed>(reg.c); break;
        case 0x3A: ValWrapper<&Z80::Srl, Prefixed>(reg.d); break;
        case 0x3B: ValWrapper<&Z80::Srl, Prefixed>(reg.e); break;
        case 0x3C: ValWrapper<&Z80::Srl, Prefixed>(reg.h); break;
        case 0x3D: ValWrapper<&Z80::Srl, Prefixed>(reg.l); break;
        case 0x3E: PtrWrapper<&Z80::Srl>(Indexed<Prefixed>()); break;
        case 0x3F: ValWrapper<&Z80::Srl, Prefixed>(reg.a); break;

        default: NotYetImplemented(opcode); break;
    }
}


void Z80::NotYetImplemented(uint8_t opcode) const
{
    throw std::runtime_error(fmt("NYI opcode 0x%02X at 0x%04X", opcode, reg.pc - 1));
}


}
