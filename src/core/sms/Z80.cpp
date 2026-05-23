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
    operandCount = 2;
    OperandWord() = ReadPC16();
}


inline uint8_t Z80::PtrRead8(uint16_t addr)
{
    return memory->ReadByte(addr);
}


inline uint16_t Z80::PtrRead16(uint16_t addr)
{
    return memory->ReadWord(addr);
}


inline uint16_t Z80::Indexed(uint16_t addr)
{
    if (prefix == IndexPrefix::hl)
        return addr;

    ReadImm8();
    return addr + static_cast<int8_t>(operand[0]);
}


inline void Z80::LoadRegister8(uint8_t &dest, uint8_t src)
{
    dest = src;
}


inline void Z80::LoadRegister16(BytePair dest, uint16_t src)
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


inline void Z80::Pop(BytePair dest)
{
    dest.l() = memory->ReadByte(reg.sp);
    reg.sp++;
    dest.h() = memory->ReadByte(reg.sp);
    reg.sp++;
}


inline void Z80::SetAFlags()
{
    // Clear all but carry flag.
    reg.f &= cf;

    if (reg.a == 0)
        reg.f |= zf;
    else
        reg.f |= (reg.a & (sf | yf | xf)); // Sign flag, x flag, and y flag get copied over from the a register.

    reg.f |= (iff2 ? pf : 0);
}


void Z80::ProcessOpcode()
{
    uint8_t opcode = FetchOpcode();

    operandCount = 0;
    prefix = IndexPrefix::hl;
    index = reg.HL();

    // Multiple prefix bytes are allowed and just overwrite the previous one.
    while (opcode == 0xDD || opcode == 0xFD)
    {
        if (opcode == 0xDD)
        {
            prefix = IndexPrefix::ix;
            index = reg.IX();
        }
        else
        {
            prefix = IndexPrefix::iy;
            index = reg.IY();
        }
        opcode = FetchOpcode();
    }

    if (opcode == 0xCB)
    {
        ProcessOpcodeCB();
        return;
    }
    if (opcode == 0xED)
    {
        // 0xED ignores any previously set prefix.
        prefix = IndexPrefix::hl;
        index = reg.HL();
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
        case 0x44: LoadRegister8(reg.b, index.h()); break;
        case 0x45: LoadRegister8(reg.b, index.l()); break;
        case 0x47: LoadRegister8(reg.b, reg.a); break;
        case 0x48: LoadRegister8(reg.c, reg.b); break;
        case 0x49: LoadRegister8(reg.c, reg.c); break;
        case 0x4A: LoadRegister8(reg.c, reg.d); break;
        case 0x4B: LoadRegister8(reg.c, reg.e); break;
        case 0x4C: LoadRegister8(reg.c, index.h()); break;
        case 0x4D: LoadRegister8(reg.c, index.l()); break;
        case 0x4F: LoadRegister8(reg.c, reg.a); break;
        case 0x50: LoadRegister8(reg.d, reg.b); break;
        case 0x51: LoadRegister8(reg.d, reg.c); break;
        case 0x52: LoadRegister8(reg.d, reg.d); break;
        case 0x53: LoadRegister8(reg.d, reg.e); break;
        case 0x54: LoadRegister8(reg.d, index.h()); break;
        case 0x55: LoadRegister8(reg.d, index.l()); break;
        case 0x57: LoadRegister8(reg.d, reg.a); break;
        case 0x58: LoadRegister8(reg.e, reg.b); break;
        case 0x59: LoadRegister8(reg.e, reg.c); break;
        case 0x5A: LoadRegister8(reg.e, reg.d); break;
        case 0x5B: LoadRegister8(reg.e, reg.e); break;
        case 0x5C: LoadRegister8(reg.e, index.h()); break;
        case 0x5D: LoadRegister8(reg.e, index.l()); break;
        case 0x5F: LoadRegister8(reg.e, reg.a); break;
        case 0x60: LoadRegister8(index.h(), reg.b); break;
        case 0x61: LoadRegister8(index.h(), reg.c); break;
        case 0x62: LoadRegister8(index.h(), reg.d); break;
        case 0x63: LoadRegister8(index.h(), reg.e); break;
        case 0x64: LoadRegister8(index.h(), index.h()); break;
        case 0x65: LoadRegister8(index.h(), index.l()); break;
        case 0x67: LoadRegister8(index.h(), reg.a); break;
        case 0x68: LoadRegister8(index.l(), reg.b); break;
        case 0x69: LoadRegister8(index.l(), reg.c); break;
        case 0x6A: LoadRegister8(index.l(), reg.d); break;
        case 0x6B: LoadRegister8(index.l(), reg.e); break;
        case 0x6C: LoadRegister8(index.l(), index.h()); break;
        case 0x6D: LoadRegister8(index.l(), index.l()); break;
        case 0x6F: LoadRegister8(index.l(), reg.a); break;
        case 0x78: LoadRegister8(reg.a, reg.b); break;
        case 0x79: LoadRegister8(reg.a, reg.c); break;
        case 0x7A: LoadRegister8(reg.a, reg.d); break;
        case 0x7B: LoadRegister8(reg.a, reg.e); break;
        case 0x7C: LoadRegister8(reg.a, index.h()); break;
        case 0x7D: LoadRegister8(reg.a, index.l()); break;
        case 0x7F: LoadRegister8(reg.a, reg.a); break;
        case 0xF9: LoadRegister16(reg.sp, index); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register, Immediate
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x06: ReadImm8(); LoadRegister8(reg.b, operand[0]); break;
        case 0x0E: ReadImm8(); LoadRegister8(reg.c, operand[0]); break;
        case 0x16: ReadImm8(); LoadRegister8(reg.d, operand[0]); break;
        case 0x1E: ReadImm8(); LoadRegister8(reg.e, operand[0]); break;
        case 0x26: ReadImm8(); LoadRegister8(index.h(), operand[0]); break;
        case 0x2E: ReadImm8(); LoadRegister8(index.l(), operand[0]); break;
        case 0x3E: ReadImm8(); LoadRegister8(reg.a, operand[0]); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register, Pointer
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x46: LoadRegister8(reg.b, PtrRead8(Indexed(index))); break;
        case 0x4E: LoadRegister8(reg.c, PtrRead8(Indexed(index))); break;
        case 0x56: LoadRegister8(reg.d, PtrRead8(Indexed(index))); break;
        case 0x5E: LoadRegister8(reg.e, PtrRead8(Indexed(index))); break;
        case 0x66: LoadRegister8(reg.h, PtrRead8(Indexed(index))); break;
        case 0x6E: LoadRegister8(reg.l, PtrRead8(Indexed(index))); break;
        case 0x7E: LoadRegister8(reg.a, PtrRead8(Indexed(index))); break;
        case 0x0A: LoadRegister8(reg.a, PtrRead8(reg.BC())); break;
        case 0x1A: LoadRegister8(reg.a, PtrRead8(reg.DE())); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Pointer, Register
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x70: LoadPointer8(Indexed(index), reg.b); break;
        case 0x71: LoadPointer8(Indexed(index), reg.c); break;
        case 0x72: LoadPointer8(Indexed(index), reg.d); break;
        case 0x73: LoadPointer8(Indexed(index), reg.e); break;
        case 0x74: LoadPointer8(Indexed(index), reg.h); break;
        case 0x75: LoadPointer8(Indexed(index), reg.l); break;
        case 0x77: LoadPointer8(Indexed(index), reg.a); break;
        case 0x02: LoadPointer8(reg.BC(), reg.a); break;
        case 0x12: LoadPointer8(reg.DE(), reg.a); break;
        case 0x32: ReadImm16(); LoadPointer8(OperandWord(), reg.a); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Pointer, Immediate
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x36:
        {
            uint16_t addr = Indexed(index); // DD or FD prefixes will call ReadImm8().
            ReadImm8();
            LoadPointer8(addr, operand[operandCount - 1]);
            break;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register, Immediate Pointer
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x3A: ReadImm16(); LoadRegister8(reg.a, PtrRead8(OperandWord())); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register Pair, Immediate Word
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x01: ReadImm16(); LoadRegister16(reg.BC(), OperandWord()); break;
        case 0x11: ReadImm16(); LoadRegister16(reg.DE(), OperandWord()); break;
        case 0x21: ReadImm16(); LoadRegister16(index, OperandWord()); break;
        case 0x31: ReadImm16(); LoadRegister16(reg.sp, OperandWord()); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register Pair, Immediate Pointer
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x2A: ReadImm16(); LoadRegister16(index, PtrRead16(OperandWord())); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Immediate Pointer Word, Register Pair
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x22: ReadImm16(); LoadPointer16(OperandWord(), index); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Stack
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0xC5: Push(reg.BC()); break;
        case 0xD5: Push(reg.DE()); break;
        case 0xE5: Push(index); break;
        case 0xF5: Push(reg.AF()); break;
        case 0xC1: Pop(reg.BC()); break;
        case 0xD1: Pop(reg.DE()); break;
        case 0xE1: Pop(index); break;
        case 0xF1: Pop(reg.AF()); break;

        default: NotYetImplemented(opcode); break;
    }
}


void Z80::ProcessOpcodeCB()
{
    /*uint8_t opcode = FetchOpcode();

    switch (opcode)
    {
        default: NotYetImplemented(opcode); break;
    }*/
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
        case 0x57: LoadRegister8(reg.a, reg.i); SetAFlags(); break;
        case 0x5F: LoadRegister8(reg.a, reg.r); SetAFlags(); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Register Pair, Immediate Pointer
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x4B: ReadImm16(); LoadRegister16(reg.BC(), PtrRead16(OperandWord())); break;
        case 0x5B: ReadImm16(); LoadRegister16(reg.DE(), PtrRead16(OperandWord())); break;
        case 0x6B: ReadImm16(); LoadRegister16(reg.HL(), PtrRead16(OperandWord())); break;
        case 0x7B: ReadImm16(); LoadRegister16(reg.sp, PtrRead16(OperandWord())); break;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LD Immediate Pointer Word, Register Pair
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 0x43: ReadImm16(); LoadPointer16(OperandWord(), reg.BC()); break;
        case 0x53: ReadImm16(); LoadPointer16(OperandWord(), reg.DE()); break;
        case 0x63: ReadImm16(); LoadPointer16(OperandWord(), reg.HL()); break;
        case 0x73: ReadImm16(); LoadPointer16(OperandWord(), reg.sp); break;

        default: NotYetImplemented(opcode); break;
    }
}


void Z80::NotYetImplemented(uint8_t opcode) const
{
    throw std::runtime_error(fmt("NYI opcode 0x%02X at 0x%04X", opcode, reg.pc - 1));
}


}
