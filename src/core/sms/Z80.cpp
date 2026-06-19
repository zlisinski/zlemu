#include <format>
#include <functional>
#include <stdexcept>

#include <core/Bytes.h>
#include <core/Logger.h>
#include <core/Utils.h>
#include "Bus.h"
#include "Interrupt.h"
#include "Memory.h"
#include "Timer.h"
#include "Z80.h"
#include "Z80Opcodes.h"


namespace Sms
{


Z80::Z80(Bus *bus, Memory *memory, Timer *timer, Interrupt *interrupt) :
    bus(bus),
    memory(memory),
    timer(timer),
    interrupt(interrupt)
{
}


void Z80::Reset()
{
}


template <bool WriteWZ>
inline uint8_t Z80::PtrRead8(uint16_t addr)
{
    if constexpr (WriteWZ)
        reg.wz = addr + 1;
    return memory->ReadByte(addr);
}


inline uint16_t Z80::PtrRead16(uint16_t addr)
{
    uint8_t low = PtrRead8(addr);
    reg.wz++;
    uint8_t high = PtrRead8(addr+1);
    return Bytes::Make16Bit(high, low);
}


inline void Z80::PtrWrite8(uint16_t addr, uint8_t value)
{
    memory->WriteByte(addr, value);
}


inline uint8_t Z80::PortRead(uint8_t port)
{
    return bus->ReadPort(port);
}


inline void Z80::PortWrite(uint8_t port, uint8_t value)
{
    bus->WritePort(port, value);
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


template <bool WriteWZ>
inline void Z80::ReadImm16()
{
    ReadImm8();
    ReadImm8();
    if constexpr (WriteWZ)
        reg.wz = operandWord;
}


inline uint8_t &Z80::GetSrcReg8(uint8_t opcode)
{
    return *regTable8[opcode & 0x07];
}


inline uint8_t &Z80::GetDestReg8(uint8_t opcode)
{
    return *regTable8[(opcode >> 3) & 0x07];
}


inline uint8_t &Z80::GetSrcReg8Unindexed(uint8_t opcode)
{
    return *regTableUnindexed8[opcode & 0x07];
}


inline uint8_t &Z80::GetDestReg8Unindexed(uint8_t opcode)
{
    return *regTableUnindexed8[(opcode >> 3) & 0x07];
}


inline uint16_t &Z80::GetReg16(uint8_t opcode)
{
    return *regTable16[(opcode >> 4) & 0x03];
}


inline uint16_t &Z80::GetReg16Stack(uint8_t opcode)
{
    return *regTable16Stack[(opcode >> 4) & 0x03];
}


inline bool Z80::FlagCheck(uint8_t opcode)
{
    uint8_t shiftTable[] = {ZF, CF, PF, SF};
    uint8_t shift = shiftTable[(opcode >> 4) & 0x03];

    return ((reg.f >> shift) & 0x01) == !!(opcode & 0x08);
}


inline void Z80::SetIndexType(IndexType type)
{
    indexType = type;
    switch (type)
    {
        case IndexType::HL:
            index = regTable16[2] = regTable16Stack[2] = &reg.hl;
            indexH = regTable8[4] = &reg.h;
            indexL = regTable8[5] = &reg.l;
            break;
        case IndexType::IX:
            index = regTable16[2] = regTable16Stack[2] = &reg.ix;
            indexH = regTable8[4] = &reg.ixh;
            indexL = regTable8[5] = &reg.ixl;
            break;
        case IndexType::IY:
            index = regTable16[2] = regTable16Stack[2] = &reg.iy;
            indexH = regTable8[4] = &reg.iyh;
            indexL = regTable8[5] = &reg.iyl;
            break;
    }
}


inline uint16_t Z80::Indexed()
{
    if (indexType == IndexType::HL)
        return *index;

    reg.wz = *index + static_cast<int8_t>(operand[0]);

    return reg.wz;
}


template <auto Func, bool PrefixedCB>
inline void Z80::ValWrapper(uint8_t &r, auto&&... args)
{
    if constexpr (PrefixedCB)
    {
        uint16_t addr = Indexed();
        r = PtrRead8(addr);
        r = std::invoke(Func, this, r, std::forward<decltype(args)>(args)...);
        PtrWrite8(addr, r);
    }
    else
    {
        r = std::invoke(Func, this, r, std::forward<decltype(args)>(args)...);
    }
}

template <auto Func>
inline void Z80::PtrWrapper(uint16_t addr, auto&&... args)
{
    uint8_t value = PtrRead8(addr);
    value = std::invoke(Func, this, value, std::forward<decltype(args)>(args)...);
    PtrWrite8(addr, value);
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


inline void Z80::SetIORepeatFlags()
{
    if (reg.flags.c)
    {
        if (reg.flags.n)
        {
            reg.flags.p = reg.flags.p == GetParity((reg.b - 1) & 0x07);
            reg.flags.h = (reg.b & 0x0F) == 0;
        }
        else
        {
            reg.flags.p = reg.flags.p == GetParity((reg.b + 1) & 0x07);
            reg.flags.h = (reg.b & 0x0F) == 0x0F;
        }
    }
    else
    {
        reg.flags.p = reg.flags.p == GetParity(reg.b & 0x07);
    }
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


template <bool WriteWZ>
inline void Z80::LoadPointer8(uint16_t destAddr, uint8_t src)
{
    if constexpr (WriteWZ)
    {
        reg.z = (destAddr + 1) & 0xFF;
        reg.w = src;
    }
    memory->WriteByte(destAddr, src);
}


inline void Z80::LoadPointer16(uint16_t destAddr, uint16_t src)
{
    reg.wz++;
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


template <bool Increment, bool Repeat>
inline void Z80::BlockLoad()
{
    uint8_t byte = memory->ReadByte(reg.hl);
    memory->WriteByte(reg.de, byte);

    reg.bc--;
    if constexpr (Increment)
    {
        reg.de++;
        reg.hl++;
    }
    else
    {
        reg.de--;
        reg.hl--;
    }

    reg.flags.n = 0;
    reg.flags.p = reg.bc != 0;
    reg.flags.x = Bytes::TestBit<3>(reg.a + byte);
    reg.flags.h = 0;
    reg.flags.y = Bytes::TestBit<1>(reg.a + byte);

    if (reg.bc && Repeat)
    {
        reg.pc -= 2;
        reg.wz = reg.pc + 1;
        SetXYFlags(reg.pc >> 8);
    }
}


template <bool Increment, bool Repeat>
inline void Z80::BlockCompare()
{
    uint8_t byte = memory->ReadByte(reg.hl);
    uint8_t result = reg.a - byte;

    reg.bc--;
    if constexpr (Increment)
        reg.hl++;
    else
        reg.hl--;

    reg.flags.n = 1;
    reg.flags.p = reg.bc != 0;
    reg.flags.h = HalfCarry(reg.a, byte, result);
    reg.flags.x = Bytes::TestBit<3>(result - reg.flags.h);
    reg.flags.y = Bytes::TestBit<1>(result - reg.flags.h);
    SetZSFlags(result);

    if (Repeat && reg.bc && !reg.flags.z)
    {
        cycles += 5;
        reg.pc -= 2;
        reg.wz = reg.pc + 1;
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

    reg.wz = dest + 1;

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

    reg.wz = dest + 1;

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

    reg.wz = dest + 1;

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


inline void Z80::Cpl()
{
    reg.a = ~reg.a;

    reg.flags.n = 1;
    reg.flags.h = 1;
    SetXYFlags(reg.a);
}


inline void Z80::Neg()
{
    uint8_t result = ~reg.a + 1;

    reg.flags.c = !!reg.a;
    reg.flags.n = 1;
    reg.flags.p = reg.a == 0x80;
    reg.flags.h = HalfCarry(reg.a, (uint8_t)0, result);
    SetXYFlags(result);
    SetZSFlags(result);

    reg.a = result;
}


inline void Z80::Ccf()
{
    reg.flags.n = 0;
    reg.flags.h = reg.flags.c;
    reg.flags.c = !reg.flags.c;
    SetXYFlags(reg.a | reg.f);
}


inline void Z80::Scf()
{
    reg.flags.n = 0;
    reg.flags.h = 0;
    reg.flags.c = 1;
    SetXYFlags(reg.a | reg.f);
}


inline void Z80::Daa()
{
    uint8_t oldA = reg.a;

    if (reg.flags.c || reg.a > 0x99)
    {
        reg.a += reg.flags.n ? -0x60 : 0x60;
        reg.flags.c = 1;
    }
    if (reg.flags.h || (reg.a & 0x0F) > 0x09)
    {
        reg.a += reg.flags.n ? -0x06 : 0x06;
    }

    reg.flags.h = Bytes::TestBit<HF>(reg.a ^ oldA);
    reg.flags.p = GetParity(reg.a);
    SetXYFlags(reg.a);
    SetZSFlags(reg.a);
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


inline void Z80::Rld()
{
    uint8_t oldA = reg.a;
    uint8_t value = memory->ReadByte(reg.hl);
    reg.a = (reg.a & 0xF0) | ((value & 0xF0) >> 4);
    value = (value << 4) | (oldA & 0x0F);
    memory->WriteByte(reg.hl, value);

    reg.wz = reg.hl + 1;

    reg.flags.n = 0;
    reg.flags.p = GetParity(reg.a);
    reg.flags.h = 0;
    SetXYFlags(reg.a);
    SetZSFlags(reg.a);
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


inline void Z80::Rrd()
{
    uint8_t oldA = reg.a;
    uint8_t value = memory->ReadByte(reg.hl);
    reg.a = (reg.a & 0xF0) | (value & 0x0F);
    value = ((oldA & 0x0F) << 4) | (value >> 4);
    memory->WriteByte(reg.hl, value);

    reg.wz = reg.hl + 1;

    reg.flags.n = 0;
    reg.flags.p = GetParity(reg.a);
    reg.flags.h = 0;
    SetXYFlags(reg.a);
    SetZSFlags(reg.a);
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


inline uint8_t Z80::Sra(uint8_t value)
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


inline uint8_t Z80::Srl(uint8_t value)
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


template <bool IsPtr>
inline void Z80::Bit(uint8_t value, uint8_t bit)
{
    uint8_t result = value & (0x01 << bit);
    reg.flags.n = 0;
    reg.flags.p = result == 0;
    reg.flags.h = 1;
    SetZSFlags(result);

    if constexpr (IsPtr)
        SetXYFlags(reg.w);
    else
        SetXYFlags(value);
}


inline uint8_t Z80::ResBit(uint8_t value, uint8_t bit)
{
    return value & ~(1 << bit);
}


inline uint8_t Z80::SetBit(uint8_t value, uint8_t bit)
{
    return value | (1 << bit);
}


inline void Z80::Jr(bool condition)
{
    if (condition)
    {
        cycles += 5;
        reg.pc += (int8_t)operand[0];
        reg.wz = reg.pc;
    }
}


inline void Z80::In(uint8_t &dest, uint8_t port)
{
    reg.wz = reg.bc + 1;
    dest = PortRead(port);

    reg.flags.n = 0;
    reg.flags.p = GetParity(dest);
    reg.flags.h = 0;
    SetXYFlags(dest);
    SetZSFlags(dest);
}


inline void Z80::InImm(uint8_t port)
{
    reg.w = reg.a;
    reg.z = port;
    reg.wz++;
    reg.a = PortRead(port);
}


template <bool Increment, bool Repeat>
void Z80::InInd(uint8_t port)
{
    uint8_t value = PortRead(port);
    PtrWrite8(reg.hl, value);

    uint16_t check = value;
    if constexpr (Increment)
    {
        reg.wz = reg.bc + 1;
        reg.hl++;
        check += (reg.c + 1) & 0xFF;
    }
    else
    {
        reg.wz = reg.bc - 1;
        reg.hl--;
        check += (reg.c - 1) & 0xFF;
    }

    reg.b--;

    reg.flags.c = check > 255;
    reg.flags.n = Bytes::TestBit<7>(value);
    reg.flags.p = GetParity((check & 0x07) ^ reg.b);
    reg.flags.h = reg.flags.c;
    SetXYFlags(reg.b);
    SetZSFlags(reg.b);

    if (Repeat && reg.b)
    {
        cycles += 5;
        reg.pc -= 2;
        reg.wz = reg.pc + 1;
        SetXYFlags(reg.pc >> 8);
        SetIORepeatFlags();
    }
}


inline void Z80::Out(uint8_t src, uint8_t port)
{
    reg.wz = reg.bc + 1;
    PortWrite(port, src);
}


inline void Z80::OutImm(uint8_t port)
{
    reg.w = reg.a;
    reg.z = port;
    PortWrite(port, reg.a);
    reg.z++;
}


template <bool Increment, bool Repeat>
void Z80::OutInd(uint8_t port)
{
    uint8_t value = PtrRead8(reg.hl);
    PortWrite(port, value);

    reg.b--;

    if constexpr (Increment)
    {
        reg.wz = reg.bc + 1;
        reg.hl++;
    }
    else
    {
        reg.wz = reg.bc - 1;
        reg.hl--;
    }

    uint16_t check = value + reg.l;
    reg.flags.c = check > 255;
    reg.flags.n = Bytes::TestBit<7>(value);
    reg.flags.p = GetParity((check & 0x07) ^ reg.b);
    reg.flags.h = reg.flags.c;
    SetXYFlags(reg.b);
    SetZSFlags(reg.b);

    if (Repeat && reg.b)
    {
        cycles += 5;
        reg.pc -= 2;
        reg.wz = reg.pc + 1;
        SetXYFlags(reg.pc >> 8);
        SetIORepeatFlags();
    }
}


inline void Z80::LogState() const
{
    LogCpu("State: a=%02X, bc=%04X, de=%04X, hl=%04X, ix=%04X, iy=%04X, pc=%04X, sp=%04X, flags=s:%d z:%d h:%d p:%d n:%d c:%d\n",
           reg.a, reg.bc, reg.de, reg.hl, reg.ix, reg.iy, reg.pc, reg.sp,
           reg.flags.s, reg.flags.z, reg.flags.h, reg.flags.p, reg.flags.n, reg.flags.c);
}


template <bool IsCB>
void Z80::ReadArgsAndLog(const OpcodeInfo &opcode)
{
    operandCount = 0;
    cycles = opcode.cycles;

    switch (opcode.argType)
    {
        case OpcodeInfo::ArgTypes::None:
            LogCpu(opcode.formatStr);
            LogState();
            break;
        case OpcodeInfo::ArgTypes::N:
            if constexpr (!IsCB)
                ReadImm8();
            LogCpu(opcode.formatStr, operand[0], operand[0]);
            LogState();
            break;
        case OpcodeInfo::ArgTypes::D:
            if constexpr (!IsCB)
                ReadImm8();
            LogCpu(opcode.formatStr, operand[0], static_cast<int8_t>(operand[0]));
            LogState();
            break;
        case OpcodeInfo::ArgTypes::NN:
            if constexpr (!IsCB)
            {
                reg.wz_ = reg.wz; // This is needed for 4 opcodes that don't change wz when reading immediate data.
                ReadImm16();
            }
            LogCpu(opcode.formatStr, operand[0], operand[1], operandWord);
            LogState();
            break;
        case OpcodeInfo::ArgTypes::DN:
            if constexpr (!IsCB)
                ReadImm16();
            LogCpu(opcode.formatStr, operand[0], operand[1], static_cast<int8_t>(operand[0]), operand[1]);
            LogState();
            break;
    }
}


void Z80::CheckInterrupt()
{
    if (!ei && iff1 && interrupt->CheckInterrupt())
    {
        LogCpu("Processing interrupt");
        timer->AddCycles(6);
        halted = false;
        iff1 = false;
        iff2 = false;

        if (im != 1)
            throw std::runtime_error("im != 1");

        Push(reg.pc);
        reg.wz = 0x0038;
        reg.pc = reg.wz;
    }
}


void Z80::Cycle()
{
    cycles = 0;

    CheckInterrupt();

    ei = false;

    if (halted)
    {
        cycles = 4;
        timer->AddCycles(cycles);
        return;
    }

    uint8_t opcode = FetchOpcode();

    SetIndexType(IndexType::HL);

    // Multiple prefix bytes are allowed and just overwrite the previous one.
    while (opcode == 0xDD || opcode == 0xFD)
    {
        if (opcode == 0xDD)
            SetIndexType(IndexType::IX);
        else
            SetIndexType(IndexType::IY);

        opcode = FetchOpcode();
    }

    if (opcode == 0xCB)
    {
        if (index != &reg.hl)
        {
            // DD/FD CB opcodes always have a displacement byte before the final opcode byte.
            ReadImm8();
            // Don't use FetchOpcode, since that increments the r register.
            opcode = ReadPC8();
            ProcessOpcodeCB<true>(opcode);
        }
        else
        {
            opcode = FetchOpcode();
            ProcessOpcodeCB<false>(opcode);
        }
    }
    else if (opcode == 0xED)
    {
        // 0xED ignores any previously set prefix.
        SetIndexType(IndexType::HL);
        opcode = FetchOpcode();
        ProcessOpcodeED(opcode);
    }
    else
    {
        ProcessOpcode(opcode);
    }

    timer->AddCycles(cycles);
}


void Z80::ProcessOpcode(uint8_t opcode)
{
    const OpcodeInfo &o = [&]() -> const OpcodeInfo &
    {
        switch (indexType)
        {
            case IndexType::IX: return OpcodeTableDD[opcode];
            case IndexType::IY: return OpcodeTableFD[opcode];
            default: return OpcodeTable[opcode];
        }
    }();

    ReadArgsAndLog<false>(o);

    switch (opcode)
    {
        case 0x00: // NOP
            break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Loads
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x47: // LD B, r
        case 0x48: case 0x49: case 0x4A: case 0x4B: case 0x4C: case 0x4D: case 0x4F: // LD C, r
        case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x57: // LD D, r
        case 0x58: case 0x59: case 0x5A: case 0x5B: case 0x5C: case 0x5D: case 0x5F: // LD E, r
        case 0x60: case 0x61: case 0x62: case 0x63: case 0x64: case 0x65: case 0x67: // LD H|IXH|IYH, r
        case 0x68: case 0x69: case 0x6A: case 0x6B: case 0x6C: case 0x6D: case 0x6F: // LD L|IXL|IYL, r
        case 0x78: case 0x79: case 0x7A: case 0x7B: case 0x7C: case 0x7D: case 0x7F: // LD A, r
            LoadRegister8(GetDestReg8(opcode), GetSrcReg8(opcode)); break;

        case 0x06: case 0x0E: case 0x16: case 0x1E: case 0x26: case 0x2E: case 0x3E: // LD r, n
            LoadRegister8(GetDestReg8(opcode), operand[0]); break;

        case 0x46: case 0x4E: case 0x56: case 0x5E: case 0x66: case 0x6E: case 0x7E: // LD r, (HL|IX+d|IY+d)
            LoadRegister8(GetDestReg8Unindexed(opcode), PtrRead8(Indexed())); break;

        case 0x0A: case 0x1A: // LD A, (rr)
            LoadRegister8(reg.a, PtrRead8<true>(GetReg16(opcode))); break;

        case 0x2A: // LD HL|IX|IY, (nn)
            LoadRegister16(*index, PtrRead16(operandWord)); break;

        case 0x3A: // LD A, (nn)
            LoadRegister8(reg.a, PtrRead8<true>(operandWord)); break;

        case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75: case 0x77: // LD (HL|IX+d|IY+d), r
            LoadPointer8(Indexed(), GetSrcReg8Unindexed(opcode)); break;

        case 0x02: case 0x12: // LD (rr), A
            LoadPointer8<true>(GetReg16(opcode), reg.a); break;

        case 0x22: // LD (nn), HL|IX|IY
            LoadPointer16(operandWord, *index); break;

        case 0x32: // LD (nn), A
            LoadPointer8<true>(operandWord, reg.a); break;

        case 0x36: // LD (HL|IX+d|IY+d), n
            LoadPointer8(Indexed(), operand[operandCount - 1]); break;

        case 0x01: case 0x11: case 0x21: case 0x31: // LD rr, nn
            reg.wz = reg.wz_; LoadRegister16(GetReg16(opcode), operandWord); break;

        case 0xF9: // LD SP, HL|IX|IY
            LoadRegister16(reg.sp, *index); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Stack
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0xC5: case 0xD5: case 0xE5: case 0xF5: // Push rr
            Push(GetReg16Stack(opcode)); break;

        case 0xC1: case 0xD1: case 0xE1: case 0xF1: // Pop rr
            Pop(GetReg16Stack(opcode)); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Exchange
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0xEB: // EX DE, HL
            std::swap(reg.de, reg.hl); break;

        case 0x08: // EX AF, AF'
            std::swap(reg.af, reg.af_); break;

        case 0xD9: // EXX
            std::swap(reg.bc, reg.bc_);
            std::swap(reg.de, reg.de_);
            std::swap(reg.hl, reg.hl_);
            break;

        case 0xE3: // EX (SP), HL|IX|IY
        {
            uint16_t old = *index;
            *index = memory->ReadWord(reg.sp);
            reg.wz = *index;
            memory->WriteWord(reg.sp, old);
            break;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Arithmetic
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x87: // ADD r
            Add8(GetSrcReg8(opcode)); break;
        case 0x86: // ADD (HL|IX+d|IY+d)
            Add8(PtrRead8(Indexed())); break;
        case 0xC6: // ADD n
            Add8(operand[0]); break;
        case 0x09: case 0x19: case 0x29: case 0x39: // ADD HL|IX|IY, rr
            Add16(*index, GetReg16(opcode)); break;

        case 0x88: case 0x89: case 0x8A: case 0x8B: case 0x8C: case 0x8D: case 0x8F: // ADC r
            Add8(GetSrcReg8(opcode), reg.flags.c); break;
        case 0x8E: // ADC (HL|IX+d|IY+d)
            Add8(PtrRead8(Indexed()), reg.flags.c); break;
        case 0xCE: // ADC n
            Add8(operand[0], reg.flags.c); break;

        case 0x90: case 0x91: case 0x92: case 0x93:case 0x94: case 0x95: case 0x97: // SUB r
            Sub8(GetSrcReg8(opcode)); break;
        case 0x96: // SUB (HL|IX+d|IY+d)
            Sub8(PtrRead8(Indexed())); break;
        case 0xD6: // SUB n
            Sub8(operand[0]); break;

        case 0x98: case 0x99: case 0x9A: case 0x9B: case 0x9C: case 0x9D: case 0x9F: // SBC r
            Sub8(GetSrcReg8(opcode), reg.flags.c); break;
        case 0x9E: // SBC (HL|IX+d|IY+d)
            Sub8(PtrRead8(Indexed()), reg.flags.c); break;
        case 0xDE: // SBC n
            Sub8(operand[0], reg.flags.c); break;

        case 0x04: case 0x0C: case 0x14: case 0x1C: case 0x24: case 0x2C: case 0x3C: // INC r
            Inc8(GetDestReg8(opcode)); break;
        case 0x34: // INC (HL|IX+d|IY+d)
            IncPtr8(Indexed()); break;
        case 0x03: case 0x13: case 0x23: case 0x33: // INC rr
            Inc16(GetReg16(opcode)); break;

        case 0x05: case 0x0D: case 0x15: case 0x1D: case 0x25: case 0x2D: case 0x3D: // DEC r
            Dec8(GetDestReg8(opcode)); break;
        case 0x35: // DEC (HL|IX+d|IY+d)
            DecPtr8(Indexed()); break;
        case 0x0B: case 0x1B: case 0x2B: case 0x3B: // DEC rr
            Dec16(GetReg16(opcode)); break;

        case 0x2F: // CPL
            Cpl(); break;

        case 0x3F: // CCF
            Ccf(); break;

        case 0x37: // SCF
            Scf(); break;

        case 0x27: // DAA
            Daa(); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Logic
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0xA0: case 0xA1: case 0xA2: case 0xA3: case 0xA4: case 0xA5: case 0xA7: // AND r
            And(GetSrcReg8(opcode)); break;
        case 0xA6: // AND (HL|IX+d|IY+d)
            And(PtrRead8(Indexed())); break;
        case 0xE6: // AND n
            And(operand[0]); break;

        case 0xB0: case 0xB1: case 0xB2: case 0xB3: case 0xB4: case 0xB5: case 0xB7: // OR r
            Or(GetSrcReg8(opcode)); break;
        case 0xB6: // OR (HL|IX+d|IY+d)
            Or(PtrRead8(Indexed())); break;
        case 0xF6: // OR n
            Or(operand[0]); break;

        case 0xA8: case 0xA9: case 0xAA: case 0xAB: case 0xAC: case 0xAD: case 0xAF: // XOR r
            Xor(GetSrcReg8(opcode)); break;
        case 0xAE: // XOR (HL|IX+d|IY+d)
            Xor(PtrRead8(Indexed())); break;
        case 0xEE: // XOR n
            Xor(operand[0]); break;

        case 0xB8: case 0xB9: case 0xBA: case 0xBB: case 0xBC: case 0xBD: case 0xBF: // CP r
            Cp(GetSrcReg8(opcode)); break;
        case 0xBE: // CP (HL|IX+d|IY+d)
            Cp(PtrRead8(Indexed())); break;
        case 0xFE: // CP n
            Cp(operand[0]); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Rotate & Shift
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x07: RlcA(); break;
        case 0x17: RlA(); break;
        case 0x0F: RrcA(); break;
        case 0x1F: RrA(); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Jumps
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0xC3: // JP nn
            reg.pc = operandWord; break;
        case 0xC2: case 0xCA: case 0xD2: case 0xDA: case 0xE2: case 0xEA: case 0xF2: case 0xFA: // JP cc, nn
        {
            if (FlagCheck(opcode))
                reg.pc = operandWord;
            break;
        }
        case 0xE9: // JP HL|IX|IY
            reg.pc = *index; break;

        case 0x18: // JR e
            reg.pc += (int8_t)operand[0];
            reg.wz = reg.pc;
            break;
        case 0x20: case 0x28: // JR Z|NZ
            Jr(reg.flags.z == !!(opcode & 0x08)); break;
        case 0x30: case 0x38: // JR C|NC
            Jr(reg.flags.c == !!(opcode & 0x08)); break;

        case 0x10: // DJNZ, e
            reg.b--; Jr(reg.b); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Call & Return
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0xCD: // CALL nn
            Push(reg.pc); reg.pc = operandWord; break;
        case 0xC4: case 0xCC: case 0xD4: case 0xDC: case 0xE4: case 0xEC: case 0xF4: case 0xFC: // CALL cc, nn
        {
            if (FlagCheck(opcode))
            {
                cycles += 7;
                Push(reg.pc);
                reg.pc = operandWord;
            }
            break;
        }

        case 0xC9: // RET
            Pop(reg.pc); reg.wz = reg.pc; break;
        case 0xC0: case 0xC8: case 0xD0: case 0xD8: case 0xE0: case 0xE8: case 0xF0: case 0xF8: // RET cc, nn
        {
            if (FlagCheck(opcode))
            {
                cycles += 6;
                Pop(reg.wz);
                reg.pc = reg.wz;
            }
            break;
        }

        case 0xC7: case 0xCF: case 0xD7: case 0xDF: case 0xE7: case 0xEF: case 0xF7: case 0xFF: // RST
        {
            Push(reg.pc);
            reg.wz = 0x08 * ((opcode >> 3) & 0x07);
            reg.pc = reg.wz;
            break;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Interrupts
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0xF3: // DI
            iff1 = iff2 = false; break;
        case 0xFB: // EI
            iff1 = iff2 = ei = true; break;
        case 0x76:
            halted = true; break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// IO
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0xDB: // IN A, (n)
            InImm(operand[0]); break;
        case 0xD3: // OUT (n), A
            OutImm(operand[0]); break;

        default: NotYetImplemented(opcode); break;
    }
}


void Z80::ProcessOpcodeED(uint8_t opcode)
{
    const OpcodeInfo &o = OpcodeTableED[opcode];
    ReadArgsAndLog<false>(o);

    switch (opcode)
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Loads
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x47: // LD I, A
            LoadRegister8(reg.i, reg.a); break;
        case 0x4F: // LD R, A
            LoadRegister8(reg.r, reg.a); break;
        case 0x57: // LD A, I
            LoadRegister8(reg.a, reg.i); SetIRFlags(); break;
        case 0x5F: // LD A, R
            LoadRegister8(reg.a, reg.r); SetIRFlags(); break;
        case 0x4B: case 0x5B: case 0x6B: case 0x7B: // LD rr, nn
            LoadRegister16(GetReg16(opcode), PtrRead16(operandWord)); break;
        case 0x43: case 0x53: case 0x63: case 0x73: // (nn), rr
            LoadPointer16(operandWord, GetReg16(opcode)); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Block Transfer
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0xA0: // LDI
            BlockLoad<true, false>(); break;
        case 0xB0: // LDI
            BlockLoad<true, true>(); break;
        case 0xA8: // LDD
            BlockLoad<false, false>(); break;
        case 0xB8: // LDDR
            BlockLoad<false, true>(); break;
        case 0xA1: // CPI
            reg.wz++; BlockCompare<true, false>(); break;
        case 0xB1: // CPIR
            reg.wz++; BlockCompare<true, true>(); break;
        case 0xA9: // CPD
            reg.wz--; BlockCompare<false, false>(); break;
        case 0xB9: // CPDR
            reg.wz--; BlockCompare<false, true>(); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Arithmetic
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x4A: case 0x5A: case 0x6A: case 0x7A: // ADC HL, rr
            Adc16(reg.hl, GetReg16(opcode)); break;

        case 0x42: case 0x52: case 0x62: case 0x72: // SBC HL, rr
            Sbc16(reg.hl, GetReg16(opcode)); break;

        case 0x44: // NEG
        case 0x4C: case 0x54: case 0x5C: case 0x64: case 0x6C: case 0x74: case 0x7C: // Undocumented NEG
            Neg(); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Rotate & Shift
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x6F: // RLD
            Rld(); break;
        case 0x67: // RRD
            Rrd(); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Call & Return
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x45: case 0x4D: // RETN / RETI
        case 0x55: case 0x65: case 0x75: // Undocumented RETN
        case 0x5D: case 0x6D: case 0x7D: // Undocumented RETI
            Pop(reg.wz); reg.pc = reg.wz; iff1 = iff2; break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Interrupts
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x46: case 0x4E: case 0x66: case 0x6E: // IM 0
            im = 0; break;
        case 0x56: case 0x76: // IM 1
            im = 1; break;
        case 0x5E: case 0x7E: // IM 2
            im = 2; break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// IO
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x40: case 0x48: case 0x50: case 0x58: case 0x60: case 0x68: case 0x78: // IN r, (C)
            In(GetDestReg8(opcode), reg.c); break;
        case 0x70: // IN HL, (C)
        {
            uint8_t dummy;
            In(dummy, reg.c);
            break;
        }
        case 0xA2: // INI
            InInd<true, false>(reg.c); break;
        case 0xB2: // INIR
            InInd<true, true>(reg.c); break;
        case 0xAA: // IND
            InInd<false, false>(reg.c); break;
        case 0xBA: // INDR
            InInd<false, true>(reg.c); break;

        case 0x41: case 0x49: case 0x51: case 0x59: case 0x61: case 0x69: case 0x79: // OUT (C), r
            Out(GetDestReg8(opcode), reg.c); break;
        case 0x71: // OUT (C), HL
            Out(0xFF, reg.c); break;
        case 0xA3: // OUTI
            OutInd<true, false>(reg.c); break;
        case 0xB3: // OTIR
            OutInd<true, true>(reg.c); break;
        case 0xAB: // OUTD
            OutInd<false, false>(reg.c); break;
        case 0xBB: // OTDR
            OutInd<false, true>(reg.c); break;

        default:
            // NOP
            break;
    }
}


template <bool Prefixed>
void Z80::ProcessOpcodeCB(uint8_t opcode)
{
    uint8_t &src = GetSrcReg8Unindexed(opcode);
    uint8_t bit = (opcode >> 3) & 0x07;

    const OpcodeInfo &o = [&]() -> const OpcodeInfo &
    {
        switch (indexType)
        {
            case IndexType::IX: return OpcodeTableDDCB[opcode];
            case IndexType::IY: return OpcodeTableFDCB[opcode];
            default: return OpcodeTableCB[opcode];
        }
    }();

    ReadArgsAndLog<true>(o);

    switch (opcode)
    {
        // RLC
        case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x05: case 0x07:
            ValWrapper<&Z80::Rlc, Prefixed>(src); break;
        case 0x06:
            PtrWrapper<&Z80::Rlc>(Indexed()); break;

        // RL
        case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x17:
            ValWrapper<&Z80::Rl, Prefixed>(src); break;
        case 0x16:
            PtrWrapper<&Z80::Rl>(Indexed()); break;

        // SLA
        case 0x20: case 0x21: case 0x22: case 0x23: case 0x24: case 0x25: case 0x27:
            ValWrapper<&Z80::Sla, Prefixed>(src); break;
        case 0x26:
            PtrWrapper<&Z80::Sla>(Indexed()); break;

        // SLL
        case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x37:
            ValWrapper<&Z80::Sll, Prefixed>(src); break;
        case 0x36:
            PtrWrapper<&Z80::Sll>(Indexed()); break;

        // RRC
        case 0x08: case 0x09: case 0x0A: case 0x0B: case 0x0C: case 0x0D: case 0x0F:
            ValWrapper<&Z80::Rrc, Prefixed>(src); break;
        case 0x0E:
            PtrWrapper<&Z80::Rrc>(Indexed()); break;

        // RR
        case 0x18: case 0x19: case 0x1A: case 0x1B: case 0x1C: case 0x1D: case 0x1F:
            ValWrapper<&Z80::Rr, Prefixed>(src); break;
        case 0x1E:
            PtrWrapper<&Z80::Rr>(Indexed()); break;

        // SRA
        case 0x28: case 0x29: case 0x2A: case 0x2B: case 0x2C: case 0x2D: case 0x2F:
            ValWrapper<&Z80::Sra, Prefixed>(src); break;
        case 0x2E:
            PtrWrapper<&Z80::Sra>(Indexed()); break;

        // SRL
        case 0x38: case 0x39: case 0x3A: case 0x3B: case 0x3C: case 0x3D: case 0x3F:
            ValWrapper<&Z80::Srl, Prefixed>(src); break;
        case 0x3E:
            PtrWrapper<&Z80::Srl>(Indexed()); break;

        // BIT
        case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x47:
        case 0x48: case 0x49: case 0x4A: case 0x4B: case 0x4C: case 0x4D: case 0x4F:
        case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x57:
        case 0x58: case 0x59: case 0x5A: case 0x5B: case 0x5C: case 0x5D: case 0x5F:
        case 0x60: case 0x61: case 0x62: case 0x63: case 0x64: case 0x65: case 0x67:
        case 0x68: case 0x69: case 0x6A: case 0x6B: case 0x6C: case 0x6D: case 0x6F:
        case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75: case 0x77:
        case 0x78: case 0x79: case 0x7A: case 0x7B: case 0x7C: case 0x7D: case 0x7F:
            if constexpr (Prefixed)
                Bit<true>(PtrRead8(Indexed()), bit);
            else
                Bit<false>(src, bit);
            break;
        case 0x46: case 0x4E: case 0x56: case 0x5E: case 0x66: case 0x6E: case 0x76: case 0x7E:
            Bit<true>(PtrRead8(Indexed()), bit); break;

        // RES
        case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x87:
        case 0x88: case 0x89: case 0x8A: case 0x8B: case 0x8C: case 0x8D: case 0x8F:
        case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95: case 0x97:
        case 0x98: case 0x99: case 0x9A: case 0x9B: case 0x9C: case 0x9D: case 0x9F:
        case 0xA0: case 0xA1: case 0xA2: case 0xA3: case 0xA4: case 0xA5: case 0xA7:
        case 0xA8: case 0xA9: case 0xAA: case 0xAB: case 0xAC: case 0xAD: case 0xAF:
        case 0xB0: case 0xB1: case 0xB2: case 0xB3: case 0xB4: case 0xB5: case 0xB7:
        case 0xB8: case 0xB9: case 0xBA: case 0xBB: case 0xBC: case 0xBD: case 0xBF:
            ValWrapper<&Z80::ResBit, Prefixed>(src, bit); break;
        case 0x86: case 0x8E: case 0x96: case 0x9E: case 0xA6: case 0xAE: case 0xB6: case 0xBE:
            PtrWrapper<&Z80::ResBit>(Indexed(), bit); break;

        // SET
        case 0xC0: case 0xC1: case 0xC2: case 0xC3: case 0xC4: case 0xC5: case 0xC7:
        case 0xC8: case 0xC9: case 0xCA: case 0xCB: case 0xCC: case 0xCD: case 0xCF:
        case 0xD0: case 0xD1: case 0xD2: case 0xD3: case 0xD4: case 0xD5: case 0xD7:
        case 0xD8: case 0xD9: case 0xDA: case 0xDB: case 0xDC: case 0xDD: case 0xDF:
        case 0xE0: case 0xE1: case 0xE2: case 0xE3: case 0xE4: case 0xE5: case 0xE7:
        case 0xE8: case 0xE9: case 0xEA: case 0xEB: case 0xEC: case 0xED: case 0xEF:
        case 0xF0: case 0xF1: case 0xF2: case 0xF3: case 0xF4: case 0xF5: case 0xF7:
        case 0xF8: case 0xF9: case 0xFA: case 0xFB: case 0xFC: case 0xFD: case 0xFF:
            ValWrapper<&Z80::SetBit, Prefixed>(src, bit); break;
        case 0xC6: case 0xCE: case 0xD6: case 0xDE: case 0xE6: case 0xEE: case 0xF6: case 0xFE:
            PtrWrapper<&Z80::SetBit>(Indexed(), bit); break;

        default: NotYetImplemented(opcode); break;
    }
}


void Z80::NotYetImplemented(uint8_t opcode) const
{
    throw std::runtime_error(fmt("NYI opcode 0x%02X at 0x%04X", opcode, reg.pc - 1));
}


}
