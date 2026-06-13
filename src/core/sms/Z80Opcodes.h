#ifndef ZLEMU_CORE_SMS_Z80OPCODES_H
#define ZLEMU_CORE_SMS_Z80OPCODES_H

#include <array>

#include <core/Zlemu.h>


namespace Sms
{


struct OpcodeInfo
{
    const char *formatStr;
    enum class ArgTypes : uint8_t
    {
        None,
        N,
        D,
        NN,
        DN
    } argType;
    uint8_t cycles;
};


inline constexpr std::array<OpcodeInfo, 256> OpcodeTable = {{
    {"00: NOP",                           OpcodeInfo::ArgTypes::None, 4 }, // 00
    {"01 %02X %02X: LD BC,%04X",          OpcodeInfo::ArgTypes::NN,   10}, // 01
    {"02: LD (BC),A",                     OpcodeInfo::ArgTypes::None, 7 }, // 02
    {"03: INC BC",                        OpcodeInfo::ArgTypes::None, 6 }, // 03
    {"04: INC B",                         OpcodeInfo::ArgTypes::None, 4 }, // 04
    {"05: DEC B",                         OpcodeInfo::ArgTypes::None, 4 }, // 05
    {"06 %02X: LD B,%02X",                OpcodeInfo::ArgTypes::N,    7 }, // 06
    {"07: RLCA",                          OpcodeInfo::ArgTypes::None, 4 }, // 07
    {"08: EX AF,AF'",                     OpcodeInfo::ArgTypes::None, 4 }, // 08
    {"09: ADD HL,BC",                     OpcodeInfo::ArgTypes::None, 11}, // 09
    {"0A: LD A,(BC)",                     OpcodeInfo::ArgTypes::None, 7 }, // 0A
    {"0B: DEC BC",                        OpcodeInfo::ArgTypes::None, 6 }, // 0B
    {"0C: INC C",                         OpcodeInfo::ArgTypes::None, 4 }, // 0C
    {"0D: DEC C",                         OpcodeInfo::ArgTypes::None, 4 }, // 0D
    {"0E %02X: LD C,%02X",                OpcodeInfo::ArgTypes::N,    7 }, // 0E
    {"0F: RRCA",                          OpcodeInfo::ArgTypes::None, 4 }, // 0F
    {"10 %02X: DJNZ %d",                  OpcodeInfo::ArgTypes::D,    8 }, // 10
    {"11 %02X %02X: LD DE,%04X",          OpcodeInfo::ArgTypes::NN,   10}, // 11
    {"12: LD (DE),A",                     OpcodeInfo::ArgTypes::None, 7 }, // 12
    {"13: INC DE",                        OpcodeInfo::ArgTypes::None, 6 }, // 13
    {"14: INC D",                         OpcodeInfo::ArgTypes::None, 4 }, // 14
    {"15: DEC D",                         OpcodeInfo::ArgTypes::None, 4 }, // 15
    {"16 %02X: LD D,%02X",                OpcodeInfo::ArgTypes::N,    7 }, // 16
    {"17: RLA",                           OpcodeInfo::ArgTypes::None, 4 }, // 17
    {"18 %02X: JR %d",                    OpcodeInfo::ArgTypes::D,    12}, // 18
    {"19: ADD HL,DE",                     OpcodeInfo::ArgTypes::None, 11}, // 19
    {"1A: LD A,(DE)",                     OpcodeInfo::ArgTypes::None, 7 }, // 1A
    {"1B: DEC DE",                        OpcodeInfo::ArgTypes::None, 6 }, // 1B
    {"1C: INC E",                         OpcodeInfo::ArgTypes::None, 4 }, // 1C
    {"1D: DEC E",                         OpcodeInfo::ArgTypes::None, 4 }, // 1D
    {"1E %02X: LD E,%02X",                OpcodeInfo::ArgTypes::N,    7 }, // 1E
    {"1F: RRA",                           OpcodeInfo::ArgTypes::None, 4 }, // 1F
    {"20 %02X: JR NZ,%d",                 OpcodeInfo::ArgTypes::D,    7 }, // 20
    {"21 %02X %02X: LD HL,%04X",          OpcodeInfo::ArgTypes::NN,   10}, // 21
    {"22 %02X %02X: LD (%04X),HL",        OpcodeInfo::ArgTypes::NN,   16}, // 22
    {"23: INC HL",                        OpcodeInfo::ArgTypes::None, 6 }, // 23
    {"24: INC H",                         OpcodeInfo::ArgTypes::None, 4 }, // 24
    {"25: DEC H",                         OpcodeInfo::ArgTypes::None, 4 }, // 25
    {"26 %02X: LD H,%02X",                OpcodeInfo::ArgTypes::N,    7 }, // 26
    {"27: DAA",                           OpcodeInfo::ArgTypes::None, 4 }, // 27
    {"28 %02X: JR Z,%d",                  OpcodeInfo::ArgTypes::D,    7 }, // 28
    {"29: ADD HL,HL",                     OpcodeInfo::ArgTypes::None, 11}, // 29
    {"2A %02X %02X: LD HL,(%04X)",        OpcodeInfo::ArgTypes::NN,   16}, // 2A
    {"2B: DEC HL",                        OpcodeInfo::ArgTypes::None, 6 }, // 2B
    {"2C: INC L",                         OpcodeInfo::ArgTypes::None, 4 }, // 2C
    {"2D: DEC L",                         OpcodeInfo::ArgTypes::None, 4 }, // 2D
    {"2E %02X: LD L,%02X",                OpcodeInfo::ArgTypes::N,    7 }, // 2E
    {"2F: CPL",                           OpcodeInfo::ArgTypes::None, 4 }, // 2F
    {"30 %02X: JR NC,%d",                 OpcodeInfo::ArgTypes::D,    7 }, // 30
    {"31 %02X %02X: LD SP,%04X",          OpcodeInfo::ArgTypes::NN,   10}, // 31
    {"32 %02X %02X: LD (%04X),A",         OpcodeInfo::ArgTypes::NN,   13}, // 32
    {"33: INC SP",                        OpcodeInfo::ArgTypes::None, 6 }, // 33
    {"34: INC (HL)",                      OpcodeInfo::ArgTypes::None, 11}, // 34
    {"35: DEC (HL)",                      OpcodeInfo::ArgTypes::None, 11}, // 35
    {"36 %02X: LD (HL),%02X",             OpcodeInfo::ArgTypes::N,    10}, // 36
    {"37: SCF",                           OpcodeInfo::ArgTypes::None, 4 }, // 37
    {"38 %02X: JR C,%d",                  OpcodeInfo::ArgTypes::D,    7 }, // 38
    {"39: ADD HL,SP",                     OpcodeInfo::ArgTypes::None, 11}, // 39
    {"3A %02X %02X: LD A,(%04X)",         OpcodeInfo::ArgTypes::NN,   13}, // 3A
    {"3B: DEC SP",                        OpcodeInfo::ArgTypes::None, 6 }, // 3B
    {"3C: INC A",                         OpcodeInfo::ArgTypes::None, 4 }, // 3C
    {"3D: DEC A",                         OpcodeInfo::ArgTypes::None, 4 }, // 3D
    {"3E %02X: LD A,%02X",                OpcodeInfo::ArgTypes::N,    7 }, // 3E
    {"3F: CCF",                           OpcodeInfo::ArgTypes::None, 4 }, // 3F
    {"40: LD B,B",                        OpcodeInfo::ArgTypes::None, 4 }, // 40
    {"41: LD B,C",                        OpcodeInfo::ArgTypes::None, 4 }, // 41
    {"42: LD B,D",                        OpcodeInfo::ArgTypes::None, 4 }, // 42
    {"43: LD B,E",                        OpcodeInfo::ArgTypes::None, 4 }, // 43
    {"44: LD B,H",                        OpcodeInfo::ArgTypes::None, 4 }, // 44
    {"45: LD B,L",                        OpcodeInfo::ArgTypes::None, 4 }, // 45
    {"46: LD B,(HL)",                     OpcodeInfo::ArgTypes::None, 7 }, // 46
    {"47: LD B,A",                        OpcodeInfo::ArgTypes::None, 4 }, // 47
    {"48: LD C,B",                        OpcodeInfo::ArgTypes::None, 4 }, // 48
    {"49: LD C,C",                        OpcodeInfo::ArgTypes::None, 4 }, // 49
    {"4A: LD C,D",                        OpcodeInfo::ArgTypes::None, 4 }, // 4A
    {"4B: LD C,E",                        OpcodeInfo::ArgTypes::None, 4 }, // 4B
    {"4C: LD C,H",                        OpcodeInfo::ArgTypes::None, 4 }, // 4C
    {"4D: LD C,L",                        OpcodeInfo::ArgTypes::None, 4 }, // 4D
    {"4E: LD C,(HL)",                     OpcodeInfo::ArgTypes::None, 7 }, // 4E
    {"4F: LD C,A",                        OpcodeInfo::ArgTypes::None, 4 }, // 4F
    {"50: LD D,B",                        OpcodeInfo::ArgTypes::None, 4 }, // 50
    {"51: LD D,C",                        OpcodeInfo::ArgTypes::None, 4 }, // 51
    {"52: LD D,D",                        OpcodeInfo::ArgTypes::None, 4 }, // 52
    {"53: LD D,E",                        OpcodeInfo::ArgTypes::None, 4 }, // 53
    {"54: LD D,H",                        OpcodeInfo::ArgTypes::None, 4 }, // 54
    {"55: LD D,L",                        OpcodeInfo::ArgTypes::None, 4 }, // 55
    {"56: LD D,(HL)",                     OpcodeInfo::ArgTypes::None, 7 }, // 56
    {"57: LD D,A",                        OpcodeInfo::ArgTypes::None, 4 }, // 57
    {"58: LD E,B",                        OpcodeInfo::ArgTypes::None, 4 }, // 58
    {"59: LD E,C",                        OpcodeInfo::ArgTypes::None, 4 }, // 59
    {"5A: LD E,D",                        OpcodeInfo::ArgTypes::None, 4 }, // 5A
    {"5B: LD E,E",                        OpcodeInfo::ArgTypes::None, 4 }, // 5B
    {"5C: LD E,H",                        OpcodeInfo::ArgTypes::None, 4 }, // 5C
    {"5D: LD E,L",                        OpcodeInfo::ArgTypes::None, 4 }, // 5D
    {"5E: LD E,(HL)",                     OpcodeInfo::ArgTypes::None, 7 }, // 5E
    {"5F: LD E,A",                        OpcodeInfo::ArgTypes::None, 4 }, // 5F
    {"60: LD H,B",                        OpcodeInfo::ArgTypes::None, 4 }, // 60
    {"61: LD H,C",                        OpcodeInfo::ArgTypes::None, 4 }, // 61
    {"62: LD H,D",                        OpcodeInfo::ArgTypes::None, 4 }, // 62
    {"63: LD H,E",                        OpcodeInfo::ArgTypes::None, 4 }, // 63
    {"64: LD H,H",                        OpcodeInfo::ArgTypes::None, 4 }, // 64
    {"65: LD H,L",                        OpcodeInfo::ArgTypes::None, 4 }, // 65
    {"66: LD H,(HL)",                     OpcodeInfo::ArgTypes::None, 7 }, // 66
    {"67: LD H,A",                        OpcodeInfo::ArgTypes::None, 4 }, // 67
    {"68: LD L,B",                        OpcodeInfo::ArgTypes::None, 4 }, // 68
    {"69: LD L,C",                        OpcodeInfo::ArgTypes::None, 4 }, // 69
    {"6A: LD L,D",                        OpcodeInfo::ArgTypes::None, 4 }, // 6A
    {"6B: LD L,E",                        OpcodeInfo::ArgTypes::None, 4 }, // 6B
    {"6C: LD L,H",                        OpcodeInfo::ArgTypes::None, 4 }, // 6C
    {"6D: LD L,L",                        OpcodeInfo::ArgTypes::None, 4 }, // 6D
    {"6E: LD L,(HL)",                     OpcodeInfo::ArgTypes::None, 7 }, // 6E
    {"6F: LD L,A",                        OpcodeInfo::ArgTypes::None, 4 }, // 6F
    {"70: LD (HL),B",                     OpcodeInfo::ArgTypes::None, 7 }, // 70
    {"71: LD (HL),C",                     OpcodeInfo::ArgTypes::None, 7 }, // 71
    {"72: LD (HL),D",                     OpcodeInfo::ArgTypes::None, 7 }, // 72
    {"73: LD (HL),E",                     OpcodeInfo::ArgTypes::None, 7 }, // 73
    {"74: LD (HL),H",                     OpcodeInfo::ArgTypes::None, 7 }, // 74
    {"75: LD (HL),L",                     OpcodeInfo::ArgTypes::None, 7 }, // 75
    {"76: HALT",                          OpcodeInfo::ArgTypes::None, 4 }, // 76
    {"77: LD (HL),A",                     OpcodeInfo::ArgTypes::None, 7 }, // 77
    {"78: LD A,B",                        OpcodeInfo::ArgTypes::None, 4 }, // 78
    {"79: LD A,C",                        OpcodeInfo::ArgTypes::None, 4 }, // 79
    {"7A: LD A,D",                        OpcodeInfo::ArgTypes::None, 4 }, // 7A
    {"7B: LD A,E",                        OpcodeInfo::ArgTypes::None, 4 }, // 7B
    {"7C: LD A,H",                        OpcodeInfo::ArgTypes::None, 4 }, // 7C
    {"7D: LD A,L",                        OpcodeInfo::ArgTypes::None, 4 }, // 7D
    {"7E: LD A,(HL)",                     OpcodeInfo::ArgTypes::None, 7 }, // 7E
    {"7F: LD A,A",                        OpcodeInfo::ArgTypes::None, 4 }, // 7F
    {"80: ADD A,B",                       OpcodeInfo::ArgTypes::None, 4 }, // 80
    {"81: ADD A,C",                       OpcodeInfo::ArgTypes::None, 4 }, // 81
    {"82: ADD A,D",                       OpcodeInfo::ArgTypes::None, 4 }, // 82
    {"83: ADD A,E",                       OpcodeInfo::ArgTypes::None, 4 }, // 83
    {"84: ADD A,H",                       OpcodeInfo::ArgTypes::None, 4 }, // 84
    {"85: ADD A,L",                       OpcodeInfo::ArgTypes::None, 4 }, // 85
    {"86: ADD A,(HL)",                    OpcodeInfo::ArgTypes::None, 7 }, // 86
    {"87: ADD A,A",                       OpcodeInfo::ArgTypes::None, 4 }, // 87
    {"88: ADC A,B",                       OpcodeInfo::ArgTypes::None, 4 }, // 88
    {"89: ADC A,C",                       OpcodeInfo::ArgTypes::None, 4 }, // 89
    {"8A: ADC A,D",                       OpcodeInfo::ArgTypes::None, 4 }, // 8A
    {"8B: ADC A,E",                       OpcodeInfo::ArgTypes::None, 4 }, // 8B
    {"8C: ADC A,H",                       OpcodeInfo::ArgTypes::None, 4 }, // 8C
    {"8D: ADC A,L",                       OpcodeInfo::ArgTypes::None, 4 }, // 8D
    {"8E: ADC A,(HL)",                    OpcodeInfo::ArgTypes::None, 7 }, // 8E
    {"8F: ADC A,A",                       OpcodeInfo::ArgTypes::None, 4 }, // 8F
    {"90: SUB B",                         OpcodeInfo::ArgTypes::None, 4 }, // 90
    {"91: SUB C",                         OpcodeInfo::ArgTypes::None, 4 }, // 91
    {"92: SUB D",                         OpcodeInfo::ArgTypes::None, 4 }, // 92
    {"93: SUB E",                         OpcodeInfo::ArgTypes::None, 4 }, // 93
    {"94: SUB H",                         OpcodeInfo::ArgTypes::None, 4 }, // 94
    {"95: SUB L",                         OpcodeInfo::ArgTypes::None, 4 }, // 95
    {"96: SUB (HL)",                      OpcodeInfo::ArgTypes::None, 7 }, // 96
    {"97: SUB A",                         OpcodeInfo::ArgTypes::None, 4 }, // 97
    {"98: SBC A,B",                       OpcodeInfo::ArgTypes::None, 4 }, // 98
    {"99: SBC A,C",                       OpcodeInfo::ArgTypes::None, 4 }, // 99
    {"9A: SBC A,D",                       OpcodeInfo::ArgTypes::None, 4 }, // 9A
    {"9B: SBC A,E",                       OpcodeInfo::ArgTypes::None, 4 }, // 9B
    {"9C: SBC A,H",                       OpcodeInfo::ArgTypes::None, 4 }, // 9C
    {"9D: SBC A,L",                       OpcodeInfo::ArgTypes::None, 4 }, // 9D
    {"9E: SBC A,(HL)",                    OpcodeInfo::ArgTypes::None, 7 }, // 9E
    {"9F: SBC A,A",                       OpcodeInfo::ArgTypes::None, 4 }, // 9F
    {"A0: AND B",                         OpcodeInfo::ArgTypes::None, 4 }, // A0
    {"A1: AND C",                         OpcodeInfo::ArgTypes::None, 4 }, // A1
    {"A2: AND D",                         OpcodeInfo::ArgTypes::None, 4 }, // A2
    {"A3: AND E",                         OpcodeInfo::ArgTypes::None, 4 }, // A3
    {"A4: AND H",                         OpcodeInfo::ArgTypes::None, 4 }, // A4
    {"A5: AND L",                         OpcodeInfo::ArgTypes::None, 4 }, // A5
    {"A6: AND (HL)",                      OpcodeInfo::ArgTypes::None, 7 }, // A6
    {"A7: AND A",                         OpcodeInfo::ArgTypes::None, 4 }, // A7
    {"A8: XOR B",                         OpcodeInfo::ArgTypes::None, 4 }, // A8
    {"A9: XOR C",                         OpcodeInfo::ArgTypes::None, 4 }, // A9
    {"AA: XOR D",                         OpcodeInfo::ArgTypes::None, 4 }, // AA
    {"AB: XOR E",                         OpcodeInfo::ArgTypes::None, 4 }, // AB
    {"AC: XOR H",                         OpcodeInfo::ArgTypes::None, 4 }, // AC
    {"AD: XOR L",                         OpcodeInfo::ArgTypes::None, 4 }, // AD
    {"AE: XOR (HL)",                      OpcodeInfo::ArgTypes::None, 7 }, // AE
    {"AF: XOR A",                         OpcodeInfo::ArgTypes::None, 4 }, // AF
    {"B0: OR B",                          OpcodeInfo::ArgTypes::None, 4 }, // B0
    {"B1: OR C",                          OpcodeInfo::ArgTypes::None, 4 }, // B1
    {"B2: OR D",                          OpcodeInfo::ArgTypes::None, 4 }, // B2
    {"B3: OR E",                          OpcodeInfo::ArgTypes::None, 4 }, // B3
    {"B4: OR H",                          OpcodeInfo::ArgTypes::None, 4 }, // B4
    {"B5: OR L",                          OpcodeInfo::ArgTypes::None, 4 }, // B5
    {"B6: OR (HL)",                       OpcodeInfo::ArgTypes::None, 7 }, // B6
    {"B7: OR A",                          OpcodeInfo::ArgTypes::None, 4 }, // B7
    {"B8: CP B",                          OpcodeInfo::ArgTypes::None, 4 }, // B8
    {"B9: CP C",                          OpcodeInfo::ArgTypes::None, 4 }, // B9
    {"BA: CP D",                          OpcodeInfo::ArgTypes::None, 4 }, // BA
    {"BB: CP E",                          OpcodeInfo::ArgTypes::None, 4 }, // BB
    {"BC: CP H",                          OpcodeInfo::ArgTypes::None, 4 }, // BC
    {"BD: CP L",                          OpcodeInfo::ArgTypes::None, 4 }, // BD
    {"BE: CP (HL)",                       OpcodeInfo::ArgTypes::None, 7 }, // BE
    {"BF: CP A",                          OpcodeInfo::ArgTypes::None, 4 }, // BF
    {"C0: RET NZ",                        OpcodeInfo::ArgTypes::None, 5 }, // C0
    {"C1: POP BC",                        OpcodeInfo::ArgTypes::None, 10}, // C1
    {"C2 %02X %02X: JP NZ,%04X",          OpcodeInfo::ArgTypes::NN,   10}, // C2
    {"C3 %02X %02X: JP %04X",             OpcodeInfo::ArgTypes::NN,   10}, // C3
    {"C4 %02X %02X: CALL NZ,%04X",        OpcodeInfo::ArgTypes::NN,   10}, // C4
    {"C5: PUSH BC",                       OpcodeInfo::ArgTypes::None, 11}, // C5
    {"C6 %02X: ADD A,%02X",               OpcodeInfo::ArgTypes::N,    7 }, // C6
    {"C7: RST 0",                         OpcodeInfo::ArgTypes::None, 11}, // C7
    {"C8: RET Z",                         OpcodeInfo::ArgTypes::None, 5 }, // C8
    {"C9: RET",                           OpcodeInfo::ArgTypes::None, 10}, // C9
    {"CA %02X %02X: JP Z,%04X",           OpcodeInfo::ArgTypes::NN,   10}, // CA
    {"CB: [Prefix]",                      OpcodeInfo::ArgTypes::None, 4 }, // CB
    {"CC %02X %02X: CALL Z,%04X",         OpcodeInfo::ArgTypes::NN,   10}, // CC
    {"CD %02X %02X: CALL %04X",           OpcodeInfo::ArgTypes::NN,   17}, // CD
    {"CE %02X: ADC A,%02X",               OpcodeInfo::ArgTypes::N,    7 }, // CE
    {"CF: RST 8",                         OpcodeInfo::ArgTypes::None, 11}, // CF
    {"D0: RET NC",                        OpcodeInfo::ArgTypes::None, 5 }, // D0
    {"D1: POP DE",                        OpcodeInfo::ArgTypes::None, 10}, // D1
    {"D2 %02X %02X: JP NC,%04X",          OpcodeInfo::ArgTypes::NN,   10}, // D2
    {"D3 %02X: OUT (%02X),A",             OpcodeInfo::ArgTypes::N,    11}, // D3
    {"D4 %02X %02X: CALL NC,%04X",        OpcodeInfo::ArgTypes::NN,   10}, // D4
    {"D5: PUSH DE",                       OpcodeInfo::ArgTypes::None, 11}, // D5
    {"D6 %02X: SUB %02X",                 OpcodeInfo::ArgTypes::N,    7 }, // D6
    {"D7: RST 10H",                       OpcodeInfo::ArgTypes::None, 11}, // D7
    {"D8: RET C",                         OpcodeInfo::ArgTypes::None, 5 }, // D8
    {"D9: EXX",                           OpcodeInfo::ArgTypes::None, 4 }, // D9
    {"DA %02X %02X: JP C,%04X",           OpcodeInfo::ArgTypes::NN,   10}, // DA
    {"DB %02X: IN A,(%02X)",              OpcodeInfo::ArgTypes::N,    11}, // DB
    {"DC %02X %02X: CALL C,%04X",         OpcodeInfo::ArgTypes::NN,   10}, // DC
    {"DD: [IX Prefix]",                   OpcodeInfo::ArgTypes::None, 4 }, // DD
    {"DE %02X: SBC A,%02X",               OpcodeInfo::ArgTypes::N,    7 }, // DE
    {"DF: RST 18H",                       OpcodeInfo::ArgTypes::None, 11}, // DF
    {"E0: RET PO",                        OpcodeInfo::ArgTypes::None, 5 }, // E0
    {"E1: POP HL",                        OpcodeInfo::ArgTypes::None, 10}, // E1
    {"E2 %02X %02X: JP PO,%04X",          OpcodeInfo::ArgTypes::NN,   10}, // E2
    {"E3: EX (SP),HL",                    OpcodeInfo::ArgTypes::None, 19}, // E3
    {"E4 %02X %02X: CALL PO,%04X",        OpcodeInfo::ArgTypes::NN,   10}, // E4
    {"E5: PUSH HL",                       OpcodeInfo::ArgTypes::None, 11}, // E5
    {"E6 %02X: AND %02X",                 OpcodeInfo::ArgTypes::N,    7 }, // E6
    {"E7: RST 20H",                       OpcodeInfo::ArgTypes::None, 11}, // E7
    {"E8: RET PE",                        OpcodeInfo::ArgTypes::None, 5 }, // E8
    {"E9: JP (HL)",                       OpcodeInfo::ArgTypes::None, 4 }, // E9
    {"EA %02X %02X: JP PE,%04X",          OpcodeInfo::ArgTypes::NN,   10}, // EA
    {"EB: EX DE,HL",                      OpcodeInfo::ArgTypes::None, 4 }, // EB
    {"EC %02X %02X: CALL PE,%04X",        OpcodeInfo::ArgTypes::NN,   10}, // EC
    {"ED: [Prefix]",                      OpcodeInfo::ArgTypes::None, 4 }, // ED
    {"EE %02X: XOR %02X",                 OpcodeInfo::ArgTypes::N,    7 }, // EE
    {"EF: RST 28H",                       OpcodeInfo::ArgTypes::None, 11}, // EF
    {"F0: RET P",                         OpcodeInfo::ArgTypes::None, 5 }, // F0
    {"F1: POP AF",                        OpcodeInfo::ArgTypes::None, 10}, // F1
    {"F2 %02X %02X: JP P,%04X",           OpcodeInfo::ArgTypes::NN,   10}, // F2
    {"F3: DI",                            OpcodeInfo::ArgTypes::None, 4 }, // F3
    {"F4 %02X %02X: CALL P,%04X",         OpcodeInfo::ArgTypes::NN,   10}, // F4
    {"F5: PUSH AF",                       OpcodeInfo::ArgTypes::None, 11}, // F5
    {"F6 %02X: OR %02X",                  OpcodeInfo::ArgTypes::N,    7 }, // F6
    {"F7: RST 30H",                       OpcodeInfo::ArgTypes::None, 11}, // F7
    {"F8: RET M",                         OpcodeInfo::ArgTypes::None, 5 }, // F8
    {"F9: LD SP,HL",                      OpcodeInfo::ArgTypes::None, 6 }, // F9
    {"FA %02X %02X: JP M,%04X",           OpcodeInfo::ArgTypes::NN,   10}, // FA
    {"FB: EI",                            OpcodeInfo::ArgTypes::None, 4 }, // FB
    {"FC %02X %02X: CALL M,%04X",         OpcodeInfo::ArgTypes::NN,   10}, // FC
    {"FD: [IY Prefix]",                   OpcodeInfo::ArgTypes::None, 4 }, // FD
    {"FE %02X: CP %02X",                  OpcodeInfo::ArgTypes::N,    7 }, // FE
    {"FF: RST 38H",                       OpcodeInfo::ArgTypes::None, 11}, // FF
}};

inline constexpr std::array<OpcodeInfo, 256> OpcodeTableCB = {{
    {"CB 00: RLC B",                      OpcodeInfo::ArgTypes::None, 8 }, // 00
    {"CB 01: RLC C",                      OpcodeInfo::ArgTypes::None, 8 }, // 01
    {"CB 02: RLC D",                      OpcodeInfo::ArgTypes::None, 8 }, // 02
    {"CB 03: RLC E",                      OpcodeInfo::ArgTypes::None, 8 }, // 03
    {"CB 04: RLC H",                      OpcodeInfo::ArgTypes::None, 8 }, // 04
    {"CB 05: RLC L",                      OpcodeInfo::ArgTypes::None, 8 }, // 05
    {"CB 06: RLC (HL)",                   OpcodeInfo::ArgTypes::None, 15}, // 06
    {"CB 07: RLC A",                      OpcodeInfo::ArgTypes::None, 8 }, // 07
    {"CB 08: RRC B",                      OpcodeInfo::ArgTypes::None, 8 }, // 08
    {"CB 09: RRC C",                      OpcodeInfo::ArgTypes::None, 8 }, // 09
    {"CB 0A: RRC D",                      OpcodeInfo::ArgTypes::None, 8 }, // 0A
    {"CB 0B: RRC E",                      OpcodeInfo::ArgTypes::None, 8 }, // 0B
    {"CB 0C: RRC H",                      OpcodeInfo::ArgTypes::None, 8 }, // 0C
    {"CB 0D: RRC L",                      OpcodeInfo::ArgTypes::None, 8 }, // 0D
    {"CB 0E: RRC (HL)",                   OpcodeInfo::ArgTypes::None, 15}, // 0E
    {"CB 0F: RRC A",                      OpcodeInfo::ArgTypes::None, 8 }, // 0F
    {"CB 10: RL B",                       OpcodeInfo::ArgTypes::None, 8 }, // 10
    {"CB 11: RL C",                       OpcodeInfo::ArgTypes::None, 8 }, // 11
    {"CB 12: RL D",                       OpcodeInfo::ArgTypes::None, 8 }, // 12
    {"CB 13: RL E",                       OpcodeInfo::ArgTypes::None, 8 }, // 13
    {"CB 14: RL H",                       OpcodeInfo::ArgTypes::None, 8 }, // 14
    {"CB 15: RL L",                       OpcodeInfo::ArgTypes::None, 8 }, // 15
    {"CB 16: RL (HL)",                    OpcodeInfo::ArgTypes::None, 15}, // 16
    {"CB 17: RL A",                       OpcodeInfo::ArgTypes::None, 8 }, // 17
    {"CB 18: RR B",                       OpcodeInfo::ArgTypes::None, 8 }, // 18
    {"CB 19: RR C",                       OpcodeInfo::ArgTypes::None, 8 }, // 19
    {"CB 1A: RR D",                       OpcodeInfo::ArgTypes::None, 8 }, // 1A
    {"CB 1B: RR E",                       OpcodeInfo::ArgTypes::None, 8 }, // 1B
    {"CB 1C: RR H",                       OpcodeInfo::ArgTypes::None, 8 }, // 1C
    {"CB 1D: RR L",                       OpcodeInfo::ArgTypes::None, 8 }, // 1D
    {"CB 1E: RR (HL)",                    OpcodeInfo::ArgTypes::None, 15}, // 1E
    {"CB 1F: RR A",                       OpcodeInfo::ArgTypes::None, 8 }, // 1F
    {"CB 20: SLA B",                      OpcodeInfo::ArgTypes::None, 8 }, // 20
    {"CB 21: SLA C",                      OpcodeInfo::ArgTypes::None, 8 }, // 21
    {"CB 22: SLA D",                      OpcodeInfo::ArgTypes::None, 8 }, // 22
    {"CB 23: SLA E",                      OpcodeInfo::ArgTypes::None, 8 }, // 23
    {"CB 24: SLA H",                      OpcodeInfo::ArgTypes::None, 8 }, // 24
    {"CB 25: SLA L",                      OpcodeInfo::ArgTypes::None, 8 }, // 25
    {"CB 26: SLA (HL)",                   OpcodeInfo::ArgTypes::None, 15}, // 26
    {"CB 27: SLA A",                      OpcodeInfo::ArgTypes::None, 8 }, // 27
    {"CB 28: SRA B",                      OpcodeInfo::ArgTypes::None, 8 }, // 28
    {"CB 29: SRA C",                      OpcodeInfo::ArgTypes::None, 8 }, // 29
    {"CB 2A: SRA D",                      OpcodeInfo::ArgTypes::None, 8 }, // 2A
    {"CB 2B: SRA E",                      OpcodeInfo::ArgTypes::None, 8 }, // 2B
    {"CB 2C: SRA H",                      OpcodeInfo::ArgTypes::None, 8 }, // 2C
    {"CB 2D: SRA L",                      OpcodeInfo::ArgTypes::None, 8 }, // 2D
    {"CB 2E: SRA (HL)",                   OpcodeInfo::ArgTypes::None, 15}, // 2E
    {"CB 2F: SRA A",                      OpcodeInfo::ArgTypes::None, 8 }, // 2F
    {"CB 30: SLL B",                      OpcodeInfo::ArgTypes::None, 8 }, // 30
    {"CB 31: SLL C",                      OpcodeInfo::ArgTypes::None, 8 }, // 31
    {"CB 32: SLL D",                      OpcodeInfo::ArgTypes::None, 8 }, // 32
    {"CB 33: SLL E",                      OpcodeInfo::ArgTypes::None, 8 }, // 33
    {"CB 34: SLL H",                      OpcodeInfo::ArgTypes::None, 8 }, // 34
    {"CB 35: SLL L",                      OpcodeInfo::ArgTypes::None, 8 }, // 35
    {"CB 36: SLL (HL)",                   OpcodeInfo::ArgTypes::None, 15}, // 36
    {"CB 37: SLL A",                      OpcodeInfo::ArgTypes::None, 8 }, // 37
    {"CB 38: SRL B",                      OpcodeInfo::ArgTypes::None, 8 }, // 38
    {"CB 39: SRL C",                      OpcodeInfo::ArgTypes::None, 8 }, // 39
    {"CB 3A: SRL D",                      OpcodeInfo::ArgTypes::None, 8 }, // 3A
    {"CB 3B: SRL E",                      OpcodeInfo::ArgTypes::None, 8 }, // 3B
    {"CB 3C: SRL H",                      OpcodeInfo::ArgTypes::None, 8 }, // 3C
    {"CB 3D: SRL L",                      OpcodeInfo::ArgTypes::None, 8 }, // 3D
    {"CB 3E: SRL (HL)",                   OpcodeInfo::ArgTypes::None, 15}, // 3E
    {"CB 3F: SRL A",                      OpcodeInfo::ArgTypes::None, 8 }, // 3F
    {"CB 40: BIT 0,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 40
    {"CB 41: BIT 0,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 41
    {"CB 42: BIT 0,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 42
    {"CB 43: BIT 0,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 43
    {"CB 44: BIT 0,H",                    OpcodeInfo::ArgTypes::None, 8 }, // 44
    {"CB 45: BIT 0,L",                    OpcodeInfo::ArgTypes::None, 8 }, // 45
    {"CB 46: BIT 0,(HL)",                 OpcodeInfo::ArgTypes::None, 12}, // 46
    {"CB 47: BIT 0,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 47
    {"CB 48: BIT 1,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 48
    {"CB 49: BIT 1,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 49
    {"CB 4A: BIT 1,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 4A
    {"CB 4B: BIT 1,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 4B
    {"CB 4C: BIT 1,H",                    OpcodeInfo::ArgTypes::None, 8 }, // 4C
    {"CB 4D: BIT 1,L",                    OpcodeInfo::ArgTypes::None, 8 }, // 4D
    {"CB 4E: BIT 1,(HL)",                 OpcodeInfo::ArgTypes::None, 12}, // 4E
    {"CB 4F: BIT 1,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 4F
    {"CB 50: BIT 2,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 50
    {"CB 51: BIT 2,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 51
    {"CB 52: BIT 2,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 52
    {"CB 53: BIT 2,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 53
    {"CB 54: BIT 2,H",                    OpcodeInfo::ArgTypes::None, 8 }, // 54
    {"CB 55: BIT 2,L",                    OpcodeInfo::ArgTypes::None, 8 }, // 55
    {"CB 56: BIT 2,(HL)",                 OpcodeInfo::ArgTypes::None, 12}, // 56
    {"CB 57: BIT 2,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 57
    {"CB 58: BIT 3,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 58
    {"CB 59: BIT 3,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 59
    {"CB 5A: BIT 3,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 5A
    {"CB 5B: BIT 3,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 5B
    {"CB 5C: BIT 3,H",                    OpcodeInfo::ArgTypes::None, 8 }, // 5C
    {"CB 5D: BIT 3,L",                    OpcodeInfo::ArgTypes::None, 8 }, // 5D
    {"CB 5E: BIT 3,(HL)",                 OpcodeInfo::ArgTypes::None, 12}, // 5E
    {"CB 5F: BIT 3,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 5F
    {"CB 60: BIT 4,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 60
    {"CB 61: BIT 4,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 61
    {"CB 62: BIT 4,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 62
    {"CB 63: BIT 4,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 63
    {"CB 64: BIT 4,H",                    OpcodeInfo::ArgTypes::None, 8 }, // 64
    {"CB 65: BIT 4,L",                    OpcodeInfo::ArgTypes::None, 8 }, // 65
    {"CB 66: BIT 4,(HL)",                 OpcodeInfo::ArgTypes::None, 12}, // 66
    {"CB 67: BIT 4,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 67
    {"CB 68: BIT 5,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 68
    {"CB 69: BIT 5,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 69
    {"CB 6A: BIT 5,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 6A
    {"CB 6B: BIT 5,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 6B
    {"CB 6C: BIT 5,H",                    OpcodeInfo::ArgTypes::None, 8 }, // 6C
    {"CB 6D: BIT 5,L",                    OpcodeInfo::ArgTypes::None, 8 }, // 6D
    {"CB 6E: BIT 5,(HL)",                 OpcodeInfo::ArgTypes::None, 12}, // 6E
    {"CB 6F: BIT 5,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 6F
    {"CB 70: BIT 6,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 70
    {"CB 71: BIT 6,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 71
    {"CB 72: BIT 6,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 72
    {"CB 73: BIT 6,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 73
    {"CB 74: BIT 6,H",                    OpcodeInfo::ArgTypes::None, 8 }, // 74
    {"CB 75: BIT 6,L",                    OpcodeInfo::ArgTypes::None, 8 }, // 75
    {"CB 76: BIT 6,(HL)",                 OpcodeInfo::ArgTypes::None, 12}, // 76
    {"CB 77: BIT 6,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 77
    {"CB 78: BIT 7,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 78
    {"CB 79: BIT 7,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 79
    {"CB 7A: BIT 7,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 7A
    {"CB 7B: BIT 7,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 7B
    {"CB 7C: BIT 7,H",                    OpcodeInfo::ArgTypes::None, 8 }, // 7C
    {"CB 7D: BIT 7,L",                    OpcodeInfo::ArgTypes::None, 8 }, // 7D
    {"CB 7E: BIT 7,(HL)",                 OpcodeInfo::ArgTypes::None, 12}, // 7E
    {"CB 7F: BIT 7,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 7F
    {"CB 80: RES 0,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 80
    {"CB 81: RES 0,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 81
    {"CB 82: RES 0,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 82
    {"CB 83: RES 0,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 83
    {"CB 84: RES 0,H",                    OpcodeInfo::ArgTypes::None, 8 }, // 84
    {"CB 85: RES 0,L",                    OpcodeInfo::ArgTypes::None, 8 }, // 85
    {"CB 86: RES 0,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // 86
    {"CB 87: RES 0,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 87
    {"CB 88: RES 1,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 88
    {"CB 89: RES 1,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 89
    {"CB 8A: RES 1,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 8A
    {"CB 8B: RES 1,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 8B
    {"CB 8C: RES 1,H",                    OpcodeInfo::ArgTypes::None, 8 }, // 8C
    {"CB 8D: RES 1,L",                    OpcodeInfo::ArgTypes::None, 8 }, // 8D
    {"CB 8E: RES 1,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // 8E
    {"CB 8F: RES 1,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 8F
    {"CB 90: RES 2,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 90
    {"CB 91: RES 2,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 91
    {"CB 92: RES 2,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 92
    {"CB 93: RES 2,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 93
    {"CB 94: RES 2,H",                    OpcodeInfo::ArgTypes::None, 8 }, // 94
    {"CB 95: RES 2,L",                    OpcodeInfo::ArgTypes::None, 8 }, // 95
    {"CB 96: RES 2,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // 96
    {"CB 97: RES 2,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 97
    {"CB 98: RES 3,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 98
    {"CB 99: RES 3,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 99
    {"CB 9A: RES 3,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 9A
    {"CB 9B: RES 3,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 9B
    {"CB 9C: RES 3,H",                    OpcodeInfo::ArgTypes::None, 8 }, // 9C
    {"CB 9D: RES 3,L",                    OpcodeInfo::ArgTypes::None, 8 }, // 9D
    {"CB 9E: RES 3,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // 9E
    {"CB 9F: RES 3,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 9F
    {"CB A0: RES 4,B",                    OpcodeInfo::ArgTypes::None, 8 }, // A0
    {"CB A1: RES 4,C",                    OpcodeInfo::ArgTypes::None, 8 }, // A1
    {"CB A2: RES 4,D",                    OpcodeInfo::ArgTypes::None, 8 }, // A2
    {"CB A3: RES 4,E",                    OpcodeInfo::ArgTypes::None, 8 }, // A3
    {"CB A4: RES 4,H",                    OpcodeInfo::ArgTypes::None, 8 }, // A4
    {"CB A5: RES 4,L",                    OpcodeInfo::ArgTypes::None, 8 }, // A5
    {"CB A6: RES 4,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // A6
    {"CB A7: RES 4,A",                    OpcodeInfo::ArgTypes::None, 8 }, // A7
    {"CB A8: RES 5,B",                    OpcodeInfo::ArgTypes::None, 8 }, // A8
    {"CB A9: RES 5,C",                    OpcodeInfo::ArgTypes::None, 8 }, // A9
    {"CB AA: RES 5,D",                    OpcodeInfo::ArgTypes::None, 8 }, // AA
    {"CB AB: RES 5,E",                    OpcodeInfo::ArgTypes::None, 8 }, // AB
    {"CB AC: RES 5,H",                    OpcodeInfo::ArgTypes::None, 8 }, // AC
    {"CB AD: RES 5,L",                    OpcodeInfo::ArgTypes::None, 8 }, // AD
    {"CB AE: RES 5,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // AE
    {"CB AF: RES 5,A",                    OpcodeInfo::ArgTypes::None, 8 }, // AF
    {"CB B0: RES 6,B",                    OpcodeInfo::ArgTypes::None, 8 }, // B0
    {"CB B1: RES 6,C",                    OpcodeInfo::ArgTypes::None, 8 }, // B1
    {"CB B2: RES 6,D",                    OpcodeInfo::ArgTypes::None, 8 }, // B2
    {"CB B3: RES 6,E",                    OpcodeInfo::ArgTypes::None, 8 }, // B3
    {"CB B4: RES 6,H",                    OpcodeInfo::ArgTypes::None, 8 }, // B4
    {"CB B5: RES 6,L",                    OpcodeInfo::ArgTypes::None, 8 }, // B5
    {"CB B6: RES 6,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // B6
    {"CB B7: RES 6,A",                    OpcodeInfo::ArgTypes::None, 8 }, // B7
    {"CB B8: RES 7,B",                    OpcodeInfo::ArgTypes::None, 8 }, // B8
    {"CB B9: RES 7,C",                    OpcodeInfo::ArgTypes::None, 8 }, // B9
    {"CB BA: RES 7,D",                    OpcodeInfo::ArgTypes::None, 8 }, // BA
    {"CB BB: RES 7,E",                    OpcodeInfo::ArgTypes::None, 8 }, // BB
    {"CB BC: RES 7,H",                    OpcodeInfo::ArgTypes::None, 8 }, // BC
    {"CB BD: RES 7,L",                    OpcodeInfo::ArgTypes::None, 8 }, // BD
    {"CB BE: RES 7,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // BE
    {"CB BF: RES 7,A",                    OpcodeInfo::ArgTypes::None, 8 }, // BF
    {"CB C0: SET 0,B",                    OpcodeInfo::ArgTypes::None, 8 }, // C0
    {"CB C1: SET 0,C",                    OpcodeInfo::ArgTypes::None, 8 }, // C1
    {"CB C2: SET 0,D",                    OpcodeInfo::ArgTypes::None, 8 }, // C2
    {"CB C3: SET 0,E",                    OpcodeInfo::ArgTypes::None, 8 }, // C3
    {"CB C4: SET 0,H",                    OpcodeInfo::ArgTypes::None, 8 }, // C4
    {"CB C5: SET 0,L",                    OpcodeInfo::ArgTypes::None, 8 }, // C5
    {"CB C6: SET 0,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // C6
    {"CB C7: SET 0,A",                    OpcodeInfo::ArgTypes::None, 8 }, // C7
    {"CB C8: SET 1,B",                    OpcodeInfo::ArgTypes::None, 8 }, // C8
    {"CB C9: SET 1,C",                    OpcodeInfo::ArgTypes::None, 8 }, // C9
    {"CB CA: SET 1,D",                    OpcodeInfo::ArgTypes::None, 8 }, // CA
    {"CB CB: SET 1,E",                    OpcodeInfo::ArgTypes::None, 8 }, // CB
    {"CB CC: SET 1,H",                    OpcodeInfo::ArgTypes::None, 8 }, // CC
    {"CB CD: SET 1,L",                    OpcodeInfo::ArgTypes::None, 8 }, // CD
    {"CB CE: SET 1,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // CE
    {"CB CF: SET 1,A",                    OpcodeInfo::ArgTypes::None, 8 }, // CF
    {"CB D0: SET 2,B",                    OpcodeInfo::ArgTypes::None, 8 }, // D0
    {"CB D1: SET 2,C",                    OpcodeInfo::ArgTypes::None, 8 }, // D1
    {"CB D2: SET 2,D",                    OpcodeInfo::ArgTypes::None, 8 }, // D2
    {"CB D3: SET 2,E",                    OpcodeInfo::ArgTypes::None, 8 }, // D3
    {"CB D4: SET 2,H",                    OpcodeInfo::ArgTypes::None, 8 }, // D4
    {"CB D5: SET 2,L",                    OpcodeInfo::ArgTypes::None, 8 }, // D5
    {"CB D6: SET 2,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // D6
    {"CB D7: SET 2,A",                    OpcodeInfo::ArgTypes::None, 8 }, // D7
    {"CB D8: SET 3,B",                    OpcodeInfo::ArgTypes::None, 8 }, // D8
    {"CB D9: SET 3,C",                    OpcodeInfo::ArgTypes::None, 8 }, // D9
    {"CB DA: SET 3,D",                    OpcodeInfo::ArgTypes::None, 8 }, // DA
    {"CB DB: SET 3,E",                    OpcodeInfo::ArgTypes::None, 8 }, // DB
    {"CB DC: SET 3,H",                    OpcodeInfo::ArgTypes::None, 8 }, // DC
    {"CB DD: SET 3,L",                    OpcodeInfo::ArgTypes::None, 8 }, // DD
    {"CB DE: SET 3,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // DE
    {"CB DF: SET 3,A",                    OpcodeInfo::ArgTypes::None, 8 }, // DF
    {"CB E0: SET 4,B",                    OpcodeInfo::ArgTypes::None, 8 }, // E0
    {"CB E1: SET 4,C",                    OpcodeInfo::ArgTypes::None, 8 }, // E1
    {"CB E2: SET 4,D",                    OpcodeInfo::ArgTypes::None, 8 }, // E2
    {"CB E3: SET 4,E",                    OpcodeInfo::ArgTypes::None, 8 }, // E3
    {"CB E4: SET 4,H",                    OpcodeInfo::ArgTypes::None, 8 }, // E4
    {"CB E5: SET 4,L",                    OpcodeInfo::ArgTypes::None, 8 }, // E5
    {"CB E6: SET 4,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // E6
    {"CB E7: SET 4,A",                    OpcodeInfo::ArgTypes::None, 8 }, // E7
    {"CB E8: SET 5,B",                    OpcodeInfo::ArgTypes::None, 8 }, // E8
    {"CB E9: SET 5,C",                    OpcodeInfo::ArgTypes::None, 8 }, // E9
    {"CB EA: SET 5,D",                    OpcodeInfo::ArgTypes::None, 8 }, // EA
    {"CB EB: SET 5,E",                    OpcodeInfo::ArgTypes::None, 8 }, // EB
    {"CB EC: SET 5,H",                    OpcodeInfo::ArgTypes::None, 8 }, // EC
    {"CB ED: SET 5,L",                    OpcodeInfo::ArgTypes::None, 8 }, // ED
    {"CB EE: SET 5,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // EE
    {"CB EF: SET 5,A",                    OpcodeInfo::ArgTypes::None, 8 }, // EF
    {"CB F0: SET 6,B",                    OpcodeInfo::ArgTypes::None, 8 }, // F0
    {"CB F1: SET 6,C",                    OpcodeInfo::ArgTypes::None, 8 }, // F1
    {"CB F2: SET 6,D",                    OpcodeInfo::ArgTypes::None, 8 }, // F2
    {"CB F3: SET 6,E",                    OpcodeInfo::ArgTypes::None, 8 }, // F3
    {"CB F4: SET 6,H",                    OpcodeInfo::ArgTypes::None, 8 }, // F4
    {"CB F5: SET 6,L",                    OpcodeInfo::ArgTypes::None, 8 }, // F5
    {"CB F6: SET 6,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // F6
    {"CB F7: SET 6,A",                    OpcodeInfo::ArgTypes::None, 8 }, // F7
    {"CB F8: SET 7,B",                    OpcodeInfo::ArgTypes::None, 8 }, // F8
    {"CB F9: SET 7,C",                    OpcodeInfo::ArgTypes::None, 8 }, // F9
    {"CB FA: SET 7,D",                    OpcodeInfo::ArgTypes::None, 8 }, // FA
    {"CB FB: SET 7,E",                    OpcodeInfo::ArgTypes::None, 8 }, // FB
    {"CB FC: SET 7,H",                    OpcodeInfo::ArgTypes::None, 8 }, // FC
    {"CB FD: SET 7,L",                    OpcodeInfo::ArgTypes::None, 8 }, // FD
    {"CB FE: SET 7,(HL)",                 OpcodeInfo::ArgTypes::None, 15}, // FE
    {"CB FF: SET 7,A",                    OpcodeInfo::ArgTypes::None, 8 }, // FF
}};

inline constexpr std::array<OpcodeInfo, 256> OpcodeTableDD = {{
    {"DD 00: NOP",                        OpcodeInfo::ArgTypes::None, 8 }, // 00
    {"DD 01 %02X %02X: LD BC,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // 01
    {"DD 02: LD (BC),A",                  OpcodeInfo::ArgTypes::None, 11}, // 02
    {"DD 03: INC BC",                     OpcodeInfo::ArgTypes::None, 10}, // 03
    {"DD 04: INC B",                      OpcodeInfo::ArgTypes::None, 8 }, // 04
    {"DD 05: DEC B",                      OpcodeInfo::ArgTypes::None, 8 }, // 05
    {"DD 06 %02X: LD B,%02X",             OpcodeInfo::ArgTypes::N,    11}, // 06
    {"DD 07: RLCA",                       OpcodeInfo::ArgTypes::None, 8 }, // 07
    {"DD 08: EX AF,AF'",                  OpcodeInfo::ArgTypes::None, 8 }, // 08
    {"DD 09: ADD IX,BC",                  OpcodeInfo::ArgTypes::None, 15}, // 09
    {"DD 0A: LD A,(BC)",                  OpcodeInfo::ArgTypes::None, 11}, // 0A
    {"DD 0B: DEC BC",                     OpcodeInfo::ArgTypes::None, 10}, // 0B
    {"DD 0C: INC C",                      OpcodeInfo::ArgTypes::None, 8 }, // 0C
    {"DD 0D: DEC C",                      OpcodeInfo::ArgTypes::None, 8 }, // 0D
    {"DD 0E %02X: LD C,%02X",             OpcodeInfo::ArgTypes::N,    11}, // 0E
    {"DD 0F: RRCA",                       OpcodeInfo::ArgTypes::None, 8 }, // 0F
    {"DD 10 %02X: DJNZ %d",               OpcodeInfo::ArgTypes::D,    12}, // 10
    {"DD 11 %02X %02X: LD DE,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // 11
    {"DD 12: LD (DE),A",                  OpcodeInfo::ArgTypes::None, 11}, // 12
    {"DD 13: INC DE",                     OpcodeInfo::ArgTypes::None, 10}, // 13
    {"DD 14: INC D",                      OpcodeInfo::ArgTypes::None, 8 }, // 14
    {"DD 15: DEC D",                      OpcodeInfo::ArgTypes::None, 8 }, // 15
    {"DD 16 %02X: LD D,%02X",             OpcodeInfo::ArgTypes::N,    11}, // 16
    {"DD 17: RLA",                        OpcodeInfo::ArgTypes::None, 8 }, // 17
    {"DD 18 %02X: JR %d",                 OpcodeInfo::ArgTypes::D,    16}, // 18
    {"DD 19: ADD IX,DE",                  OpcodeInfo::ArgTypes::None, 15}, // 19
    {"DD 1A: LD A,(DE)",                  OpcodeInfo::ArgTypes::None, 11}, // 1A
    {"DD 1B: DEC DE",                     OpcodeInfo::ArgTypes::None, 10}, // 1B
    {"DD 1C: INC E",                      OpcodeInfo::ArgTypes::None, 8 }, // 1C
    {"DD 1D: DEC E",                      OpcodeInfo::ArgTypes::None, 8 }, // 1D
    {"DD 1E %02X: LD E,%02X",             OpcodeInfo::ArgTypes::N,    11}, // 1E
    {"DD 1F: RRA",                        OpcodeInfo::ArgTypes::None, 8 }, // 1F
    {"DD 20 %02X: JR NZ,%d",              OpcodeInfo::ArgTypes::D,    11}, // 20
    {"DD 21 %02X %02X: LD IX,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // 21
    {"DD 22 %02X %02X: LD (%04X),IX",     OpcodeInfo::ArgTypes::NN,   20}, // 22
    {"DD 23: INC IX",                     OpcodeInfo::ArgTypes::None, 10}, // 23
    {"DD 24: INC IXh",                    OpcodeInfo::ArgTypes::None, 8 }, // 24
    {"DD 25: DEC IXh",                    OpcodeInfo::ArgTypes::None, 8 }, // 25
    {"DD 26 %02X: LD IXh,%02X",           OpcodeInfo::ArgTypes::N,    11}, // 26
    {"DD 27: DAA",                        OpcodeInfo::ArgTypes::None, 8 }, // 27
    {"DD 28 %02X: JR Z,%d",               OpcodeInfo::ArgTypes::D,    11}, // 28
    {"DD 29: ADD IX,IX",                  OpcodeInfo::ArgTypes::None, 15}, // 29
    {"DD 2A %02X %02X: LD IX,(%04X)",     OpcodeInfo::ArgTypes::NN,   20}, // 2A
    {"DD 2B: DEC IX",                     OpcodeInfo::ArgTypes::None, 10}, // 2B
    {"DD 2C: INC IXl",                    OpcodeInfo::ArgTypes::None, 8 }, // 2C
    {"DD 2D: DEC IXl",                    OpcodeInfo::ArgTypes::None, 8 }, // 2D
    {"DD 2E %02X: LD IXl,%02X",           OpcodeInfo::ArgTypes::N,    11}, // 2E
    {"DD 2F: CPL",                        OpcodeInfo::ArgTypes::None, 8 }, // 2F
    {"DD 30 %02X: JR NC,%d",              OpcodeInfo::ArgTypes::D,    11}, // 30
    {"DD 31 %02X %02X: LD SP,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // 31
    {"DD 32 %02X %02X: LD (%04X),A",      OpcodeInfo::ArgTypes::NN,   17}, // 32
    {"DD 33: INC SP",                     OpcodeInfo::ArgTypes::None, 10}, // 33
    {"DD 34 %02X: INC (IX+%d)",           OpcodeInfo::ArgTypes::D,    23}, // 34
    {"DD 35 %02X: DEC (IX+%d)",           OpcodeInfo::ArgTypes::D,    23}, // 35
    {"DD 36 %02X %02X: LD (IX+%d),%02X",  OpcodeInfo::ArgTypes::DN,   19}, // 36
    {"DD 37: SCF",                        OpcodeInfo::ArgTypes::None, 8 }, // 37
    {"DD 38 %02X: JR C,%d",               OpcodeInfo::ArgTypes::D,    11}, // 38
    {"DD 39: ADD IX,SP",                  OpcodeInfo::ArgTypes::None, 15}, // 39
    {"DD 3A %02X %02X: LD A,(%04X)",      OpcodeInfo::ArgTypes::NN,   17}, // 3A
    {"DD 3B: DEC SP",                     OpcodeInfo::ArgTypes::None, 10}, // 3B
    {"DD 3C: INC A",                      OpcodeInfo::ArgTypes::None, 8 }, // 3C
    {"DD 3D: DEC A",                      OpcodeInfo::ArgTypes::None, 8 }, // 3D
    {"DD 3E %02X: LD A,%02X",             OpcodeInfo::ArgTypes::N,    11}, // 3E
    {"DD 3F: CCF",                        OpcodeInfo::ArgTypes::None, 8 }, // 3F
    {"DD 40: LD B,B",                     OpcodeInfo::ArgTypes::None, 8 }, // 40
    {"DD 41: LD B,C",                     OpcodeInfo::ArgTypes::None, 8 }, // 41
    {"DD 42: LD B,D",                     OpcodeInfo::ArgTypes::None, 8 }, // 42
    {"DD 43: LD B,E",                     OpcodeInfo::ArgTypes::None, 8 }, // 43
    {"DD 44: LD B,IXh",                   OpcodeInfo::ArgTypes::None, 8 }, // 44
    {"DD 45: LD B,IXl",                   OpcodeInfo::ArgTypes::None, 8 }, // 45
    {"DD 46 %02X: LD B,(IX+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 46
    {"DD 47: LD B,A",                     OpcodeInfo::ArgTypes::None, 8 }, // 47
    {"DD 48: LD C,B",                     OpcodeInfo::ArgTypes::None, 8 }, // 48
    {"DD 49: LD C,C",                     OpcodeInfo::ArgTypes::None, 8 }, // 49
    {"DD 4A: LD C,D",                     OpcodeInfo::ArgTypes::None, 8 }, // 4A
    {"DD 4B: LD C,E",                     OpcodeInfo::ArgTypes::None, 8 }, // 4B
    {"DD 4C: LD C,IXh",                   OpcodeInfo::ArgTypes::None, 8 }, // 4C
    {"DD 4D: LD C,IXl",                   OpcodeInfo::ArgTypes::None, 8 }, // 4D
    {"DD 4E %02X: LD C,(IX+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 4E
    {"DD 4F: LD C,A",                     OpcodeInfo::ArgTypes::None, 8 }, // 4F
    {"DD 50: LD D,B",                     OpcodeInfo::ArgTypes::None, 8 }, // 50
    {"DD 51: LD D,C",                     OpcodeInfo::ArgTypes::None, 8 }, // 51
    {"DD 52: LD D,D",                     OpcodeInfo::ArgTypes::None, 8 }, // 52
    {"DD 53: LD D,E",                     OpcodeInfo::ArgTypes::None, 8 }, // 53
    {"DD 54: LD D,IXh",                   OpcodeInfo::ArgTypes::None, 8 }, // 54
    {"DD 55: LD D,IXl",                   OpcodeInfo::ArgTypes::None, 8 }, // 55
    {"DD 56 %02X: LD D,(IX+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 56
    {"DD 57: LD D,A",                     OpcodeInfo::ArgTypes::None, 8 }, // 57
    {"DD 58: LD E,B",                     OpcodeInfo::ArgTypes::None, 8 }, // 58
    {"DD 59: LD E,C",                     OpcodeInfo::ArgTypes::None, 8 }, // 59
    {"DD 5A: LD E,D",                     OpcodeInfo::ArgTypes::None, 8 }, // 5A
    {"DD 5B: LD E,E",                     OpcodeInfo::ArgTypes::None, 8 }, // 5B
    {"DD 5C: LD E,IXh",                   OpcodeInfo::ArgTypes::None, 8 }, // 5C
    {"DD 5D: LD E,IXl",                   OpcodeInfo::ArgTypes::None, 8 }, // 5D
    {"DD 5E %02X: LD E,(IX+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 5E
    {"DD 5F: LD E,A",                     OpcodeInfo::ArgTypes::None, 8 }, // 5F
    {"DD 60: LD IXh,B",                   OpcodeInfo::ArgTypes::None, 8 }, // 60
    {"DD 61: LD IXh,C",                   OpcodeInfo::ArgTypes::None, 8 }, // 61
    {"DD 62: LD IXh,D",                   OpcodeInfo::ArgTypes::None, 8 }, // 62
    {"DD 63: LD IXh,E",                   OpcodeInfo::ArgTypes::None, 8 }, // 63
    {"DD 64: LD IXh,IXh",                 OpcodeInfo::ArgTypes::None, 8 }, // 64
    {"DD 65: LD IXh,IXl",                 OpcodeInfo::ArgTypes::None, 8 }, // 65
    {"DD 66 %02X: LD H,(IX+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 66
    {"DD 67: LD IXh,A",                   OpcodeInfo::ArgTypes::None, 8 }, // 67
    {"DD 68: LD IXl,B",                   OpcodeInfo::ArgTypes::None, 8 }, // 68
    {"DD 69: LD IXl,C",                   OpcodeInfo::ArgTypes::None, 8 }, // 69
    {"DD 6A: LD IXl,D",                   OpcodeInfo::ArgTypes::None, 8 }, // 6A
    {"DD 6B: LD IXl,E",                   OpcodeInfo::ArgTypes::None, 8 }, // 6B
    {"DD 6C: LD IXl,IXh",                 OpcodeInfo::ArgTypes::None, 8 }, // 6C
    {"DD 6D: LD IXl,IXl",                 OpcodeInfo::ArgTypes::None, 8 }, // 6D
    {"DD 6E %02X: LD L,(IX+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 6E
    {"DD 6F: LD IXl,A",                   OpcodeInfo::ArgTypes::None, 8 }, // 6F
    {"DD 70 %02X: LD (IX+%d),B",          OpcodeInfo::ArgTypes::D,    19}, // 70
    {"DD 71 %02X: LD (IX+%d),C",          OpcodeInfo::ArgTypes::D,    19}, // 71
    {"DD 72 %02X: LD (IX+%d),D",          OpcodeInfo::ArgTypes::D,    19}, // 72
    {"DD 73 %02X: LD (IX+%d),E",          OpcodeInfo::ArgTypes::D,    19}, // 73
    {"DD 74 %02X: LD (IX+%d),H",          OpcodeInfo::ArgTypes::D,    19}, // 74
    {"DD 75 %02X: LD (IX+%d),L",          OpcodeInfo::ArgTypes::D,    19}, // 75
    {"DD 76: HALT",                       OpcodeInfo::ArgTypes::None, 8 }, // 76
    {"DD 77 %02X: LD (IX+%d),A",          OpcodeInfo::ArgTypes::D,    19}, // 77
    {"DD 78: LD A,B",                     OpcodeInfo::ArgTypes::None, 8 }, // 78
    {"DD 79: LD A,C",                     OpcodeInfo::ArgTypes::None, 8 }, // 79
    {"DD 7A: LD A,D",                     OpcodeInfo::ArgTypes::None, 8 }, // 7A
    {"DD 7B: LD A,E",                     OpcodeInfo::ArgTypes::None, 8 }, // 7B
    {"DD 7C: LD A,IXh",                   OpcodeInfo::ArgTypes::None, 8 }, // 7C
    {"DD 7D: LD A,IXl",                   OpcodeInfo::ArgTypes::None, 8 }, // 7D
    {"DD 7E %02X: LD A,(IX+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 7E
    {"DD 7F: LD A,A",                     OpcodeInfo::ArgTypes::None, 8 }, // 7F
    {"DD 80: ADD A,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 80
    {"DD 81: ADD A,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 81
    {"DD 82: ADD A,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 82
    {"DD 83: ADD A,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 83
    {"DD 84: ADD A,IXh",                  OpcodeInfo::ArgTypes::None, 8 }, // 84
    {"DD 85: ADD A,IXl",                  OpcodeInfo::ArgTypes::None, 8 }, // 85
    {"DD 86 %02X: ADD A,(IX+%d)",         OpcodeInfo::ArgTypes::D,    19}, // 86
    {"DD 87: ADD A,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 87
    {"DD 88: ADC A,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 88
    {"DD 89: ADC A,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 89
    {"DD 8A: ADC A,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 8A
    {"DD 8B: ADC A,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 8B
    {"DD 8C: ADC A,IXh",                  OpcodeInfo::ArgTypes::None, 8 }, // 8C
    {"DD 8D: ADC A,IXl",                  OpcodeInfo::ArgTypes::None, 8 }, // 8D
    {"DD 8E %02X: ADC A,(IX+%d)",         OpcodeInfo::ArgTypes::D,    19}, // 8E
    {"DD 8F: ADC A,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 8F
    {"DD 90: SUB B",                      OpcodeInfo::ArgTypes::None, 8 }, // 90
    {"DD 91: SUB C",                      OpcodeInfo::ArgTypes::None, 8 }, // 91
    {"DD 92: SUB D",                      OpcodeInfo::ArgTypes::None, 8 }, // 92
    {"DD 93: SUB E",                      OpcodeInfo::ArgTypes::None, 8 }, // 93
    {"DD 94: SUB IXh",                    OpcodeInfo::ArgTypes::None, 8 }, // 94
    {"DD 95: SUB IXl",                    OpcodeInfo::ArgTypes::None, 8 }, // 95
    {"DD 96 %02X: SUB (IX+%d)",           OpcodeInfo::ArgTypes::D,    19}, // 96
    {"DD 97: SUB A",                      OpcodeInfo::ArgTypes::None, 8 }, // 97
    {"DD 98: SBC A,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 98
    {"DD 99: SBC A,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 99
    {"DD 9A: SBC A,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 9A
    {"DD 9B: SBC A,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 9B
    {"DD 9C: SBC A,IXh",                  OpcodeInfo::ArgTypes::None, 8 }, // 9C
    {"DD 9D: SBC A,IXl",                  OpcodeInfo::ArgTypes::None, 8 }, // 9D
    {"DD 9E %02X: SBC A,(IX+%d)",         OpcodeInfo::ArgTypes::D,    19}, // 9E
    {"DD 9F: SBC A,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 9F
    {"DD A0: AND B",                      OpcodeInfo::ArgTypes::None, 8 }, // A0
    {"DD A1: AND C",                      OpcodeInfo::ArgTypes::None, 8 }, // A1
    {"DD A2: AND D",                      OpcodeInfo::ArgTypes::None, 8 }, // A2
    {"DD A3: AND E",                      OpcodeInfo::ArgTypes::None, 8 }, // A3
    {"DD A4: AND IXh",                    OpcodeInfo::ArgTypes::None, 8 }, // A4
    {"DD A5: AND IXl",                    OpcodeInfo::ArgTypes::None, 8 }, // A5
    {"DD A6 %02X: AND (IX+%d)",           OpcodeInfo::ArgTypes::D,    19}, // A6
    {"DD A7: AND A",                      OpcodeInfo::ArgTypes::None, 8 }, // A7
    {"DD A8: XOR B",                      OpcodeInfo::ArgTypes::None, 8 }, // A8
    {"DD A9: XOR C",                      OpcodeInfo::ArgTypes::None, 8 }, // A9
    {"DD AA: XOR D",                      OpcodeInfo::ArgTypes::None, 8 }, // AA
    {"DD AB: XOR E",                      OpcodeInfo::ArgTypes::None, 8 }, // AB
    {"DD AC: XOR IXh",                    OpcodeInfo::ArgTypes::None, 8 }, // AC
    {"DD AD: XOR IXl",                    OpcodeInfo::ArgTypes::None, 8 }, // AD
    {"DD AE %02X: XOR (IX+%d)",           OpcodeInfo::ArgTypes::D,    19}, // AE
    {"DD AF: XOR A",                      OpcodeInfo::ArgTypes::None, 8 }, // AF
    {"DD B0: OR B",                       OpcodeInfo::ArgTypes::None, 8 }, // B0
    {"DD B1: OR C",                       OpcodeInfo::ArgTypes::None, 8 }, // B1
    {"DD B2: OR D",                       OpcodeInfo::ArgTypes::None, 8 }, // B2
    {"DD B3: OR E",                       OpcodeInfo::ArgTypes::None, 8 }, // B3
    {"DD B4: OR IXh",                     OpcodeInfo::ArgTypes::None, 8 }, // B4
    {"DD B5: OR IXl",                     OpcodeInfo::ArgTypes::None, 8 }, // B5
    {"DD B6 %02X: OR (IX+%d)",            OpcodeInfo::ArgTypes::D,    19}, // B6
    {"DD B7: OR A",                       OpcodeInfo::ArgTypes::None, 8 }, // B7
    {"DD B8: CP B",                       OpcodeInfo::ArgTypes::None, 8 }, // B8
    {"DD B9: CP C",                       OpcodeInfo::ArgTypes::None, 8 }, // B9
    {"DD BA: CP D",                       OpcodeInfo::ArgTypes::None, 8 }, // BA
    {"DD BB: CP E",                       OpcodeInfo::ArgTypes::None, 8 }, // BB
    {"DD BC: CP IXh",                     OpcodeInfo::ArgTypes::None, 8 }, // BC
    {"DD BD: CP IXl",                     OpcodeInfo::ArgTypes::None, 8 }, // BD
    {"DD BE %02X: CP (IX+%d)",            OpcodeInfo::ArgTypes::D,    19}, // BE
    {"DD BF: CP A",                       OpcodeInfo::ArgTypes::None, 8 }, // BF
    {"DD C0: RET NZ",                     OpcodeInfo::ArgTypes::None, 9 }, // C0
    {"DD C1: POP BC",                     OpcodeInfo::ArgTypes::None, 14}, // C1
    {"DD C2 %02X %02X: JP NZ,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // C2
    {"DD C3 %02X %02X: JP %04X",          OpcodeInfo::ArgTypes::NN,   14}, // C3
    {"DD C4 %02X %02X: CALL NZ,%04X",     OpcodeInfo::ArgTypes::NN,   14}, // C4
    {"DD C5: PUSH BC",                    OpcodeInfo::ArgTypes::None, 15}, // C5
    {"DD C6 %02X: ADD A,%02X",            OpcodeInfo::ArgTypes::N,    11}, // C6
    {"DD C7: RST 0",                      OpcodeInfo::ArgTypes::None, 15}, // C7
    {"DD C8: RET Z",                      OpcodeInfo::ArgTypes::None, 9 }, // C8
    {"DD C9: RET",                        OpcodeInfo::ArgTypes::None, 14}, // C9
    {"DD CA %02X %02X: JP Z,%04X",        OpcodeInfo::ArgTypes::NN,   14}, // CA
    {"DD CB %02X: [See DDCB i%02Xfo]",    OpcodeInfo::ArgTypes::N,    4 }, // CB
    {"DD CC %02X %02X: CALL Z,%04X",      OpcodeInfo::ArgTypes::NN,   14}, // CC
    {"DD CD %02X %02X: CALL %04X",        OpcodeInfo::ArgTypes::NN,   21}, // CD
    {"DD CE %02X: ADC A,%02X",            OpcodeInfo::ArgTypes::N,    11}, // CE
    {"DD CF: RST 8",                      OpcodeInfo::ArgTypes::None, 15}, // CF
    {"DD D0: RET NC",                     OpcodeInfo::ArgTypes::None, 9 }, // D0
    {"DD D1: POP DE",                     OpcodeInfo::ArgTypes::None, 14}, // D1
    {"DD D2 %02X %02X: JP NC,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // D2
    {"DD D3 %02X: OUT (%02X),A",          OpcodeInfo::ArgTypes::N,    15}, // D3
    {"DD D4 %02X %02X: CALL NC,%04X",     OpcodeInfo::ArgTypes::NN,   14}, // D4
    {"DD D5: PUSH DE",                    OpcodeInfo::ArgTypes::None, 15}, // D5
    {"DD D6 %02X: SUB %02X",              OpcodeInfo::ArgTypes::N,    11}, // D6
    {"DD D7: RST 10H",                    OpcodeInfo::ArgTypes::None, 15}, // D7
    {"DD D8: RET C",                      OpcodeInfo::ArgTypes::None, 9 }, // D8
    {"DD D9: EXX",                        OpcodeInfo::ArgTypes::None, 8 }, // D9
    {"DD DA %02X %02X: JP C,%04X",        OpcodeInfo::ArgTypes::NN,   14}, // DA
    {"DD DB %02X: IN A,(%02X)",           OpcodeInfo::ArgTypes::N,    15}, // DB
    {"DD DC %02X %02X: CALL C,%04X",      OpcodeInfo::ArgTypes::NN,   14}, // DC
    {"DD DD: [IX Prefix]",                OpcodeInfo::ArgTypes::None, 4 }, // DD
    {"DD DE %02X: SBC A,%02X",            OpcodeInfo::ArgTypes::N,    11}, // DE
    {"DD DF: RST 18H",                    OpcodeInfo::ArgTypes::None, 15}, // DF
    {"DD E0: RET PO",                     OpcodeInfo::ArgTypes::None, 9 }, // E0
    {"DD E1: POP IX",                     OpcodeInfo::ArgTypes::None, 14}, // E1
    {"DD E2 %02X %02X: JP PO,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // E2
    {"DD E3: EX (SP),IX",                 OpcodeInfo::ArgTypes::None, 23}, // E3
    {"DD E4 %02X %02X: CALL PO,%04X",     OpcodeInfo::ArgTypes::NN,   14}, // E4
    {"DD E5: PUSH IX",                    OpcodeInfo::ArgTypes::None, 15}, // E5
    {"DD E6 %02X: AND %02X",              OpcodeInfo::ArgTypes::N,    11}, // E6
    {"DD E7: RST 20H",                    OpcodeInfo::ArgTypes::None, 15}, // E7
    {"DD E8: RET PE",                     OpcodeInfo::ArgTypes::None, 9 }, // E8
    {"DD E9: JP (IX)",                    OpcodeInfo::ArgTypes::None, 8 }, // E9
    {"DD EA %02X %02X: JP PE,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // EA
    {"DD EB: EX DE,HL",                   OpcodeInfo::ArgTypes::None, 8 }, // EB
    {"DD EC %02X %02X: CALL PE,%04X",     OpcodeInfo::ArgTypes::NN,   14}, // EC
    {"DD ED: [Prefix]",                   OpcodeInfo::ArgTypes::None, 4 }, // ED
    {"DD EE %02X: XOR %02X",              OpcodeInfo::ArgTypes::N,    11}, // EE
    {"DD EF: RST 28H",                    OpcodeInfo::ArgTypes::None, 15}, // EF
    {"DD F0: RET P",                      OpcodeInfo::ArgTypes::None, 9 }, // F0
    {"DD F1: POP AF",                     OpcodeInfo::ArgTypes::None, 14}, // F1
    {"DD F2 %02X %02X: JP P,%04X",        OpcodeInfo::ArgTypes::NN,   14}, // F2
    {"DD F3: DI",                         OpcodeInfo::ArgTypes::None, 8 }, // F3
    {"DD F4 %02X %02X: CALL P,%04X",      OpcodeInfo::ArgTypes::NN,   14}, // F4
    {"DD F5: PUSH AF",                    OpcodeInfo::ArgTypes::None, 15}, // F5
    {"DD F6 %02X: OR %02X",               OpcodeInfo::ArgTypes::N,    11}, // F6
    {"DD F7: RST 30H",                    OpcodeInfo::ArgTypes::None, 15}, // F7
    {"DD F8: RET M",                      OpcodeInfo::ArgTypes::None, 9 }, // F8
    {"DD F9: LD SP,IX",                   OpcodeInfo::ArgTypes::None, 10}, // F9
    {"DD FA %02X %02X: JP M,%04X",        OpcodeInfo::ArgTypes::NN,   14}, // FA
    {"DD FB: EI",                         OpcodeInfo::ArgTypes::None, 8 }, // FB
    {"DD FC %02X %02X: CALL M,%04X",      OpcodeInfo::ArgTypes::NN,   14}, // FC
    {"DD FD: [IY Prefix]",                OpcodeInfo::ArgTypes::None, 4 }, // FD
    {"DD FE %02X: CP %02X",               OpcodeInfo::ArgTypes::N,    11}, // FE
    {"DD FF: RST 38H",                    OpcodeInfo::ArgTypes::None, 15}, // FF
}};

inline constexpr std::array<OpcodeInfo, 256> OpcodeTableED = {{
    {"ED 00: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 00
    {"ED 01: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 01
    {"ED 02: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 02
    {"ED 03: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 03
    {"ED 04: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 04
    {"ED 05: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 05
    {"ED 06: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 06
    {"ED 07: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 07
    {"ED 08: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 08
    {"ED 09: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 09
    {"ED 0A: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 0A
    {"ED 0B: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 0B
    {"ED 0C: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 0C
    {"ED 0D: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 0D
    {"ED 0E: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 0E
    {"ED 0F: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 0F
    {"ED 10: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 10
    {"ED 11: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 11
    {"ED 12: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 12
    {"ED 13: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 13
    {"ED 14: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 14
    {"ED 15: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 15
    {"ED 16: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 16
    {"ED 17: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 17
    {"ED 18: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 18
    {"ED 19: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 19
    {"ED 1A: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 1A
    {"ED 1B: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 1B
    {"ED 1C: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 1C
    {"ED 1D: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 1D
    {"ED 1E: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 1E
    {"ED 1F: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 1F
    {"ED 20: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 20
    {"ED 21: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 21
    {"ED 22: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 22
    {"ED 23: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 23
    {"ED 24: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 24
    {"ED 25: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 25
    {"ED 26: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 26
    {"ED 27: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 27
    {"ED 28: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 28
    {"ED 29: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 29
    {"ED 2A: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 2A
    {"ED 2B: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 2B
    {"ED 2C: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 2C
    {"ED 2D: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 2D
    {"ED 2E: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 2E
    {"ED 2F: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 2F
    {"ED 30: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 30
    {"ED 31: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 31
    {"ED 32: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 32
    {"ED 33: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 33
    {"ED 34: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 34
    {"ED 35: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 35
    {"ED 36: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 36
    {"ED 37: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 37
    {"ED 38: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 38
    {"ED 39: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 39
    {"ED 3A: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 3A
    {"ED 3B: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 3B
    {"ED 3C: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 3C
    {"ED 3D: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 3D
    {"ED 3E: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 3E
    {"ED 3F: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 3F
    {"ED 40: IN B,(C)",                   OpcodeInfo::ArgTypes::None, 12}, // 40
    {"ED 41: OUT (C),B",                  OpcodeInfo::ArgTypes::None, 12}, // 41
    {"ED 42: SBC HL,BC",                  OpcodeInfo::ArgTypes::None, 15}, // 42
    {"ED 43 %02X %02X: LD (%04X),BC",     OpcodeInfo::ArgTypes::NN,   20}, // 43
    {"ED 44: NEG",                        OpcodeInfo::ArgTypes::None, 8 }, // 44
    {"ED 45: RETN",                       OpcodeInfo::ArgTypes::None, 14}, // 45
    {"ED 46: IM 0",                       OpcodeInfo::ArgTypes::None, 8 }, // 46
    {"ED 47: LD I,A",                     OpcodeInfo::ArgTypes::None, 9 }, // 47
    {"ED 48: IN C,(C)",                   OpcodeInfo::ArgTypes::None, 12}, // 48
    {"ED 49: OUT (C),C",                  OpcodeInfo::ArgTypes::None, 12}, // 49
    {"ED 4A: ADC HL,BC",                  OpcodeInfo::ArgTypes::None, 15}, // 4A
    {"ED 4B %02X %02X: LD BC,(%04X)",     OpcodeInfo::ArgTypes::NN,   20}, // 4B
    {"ED 4C: NEG",                        OpcodeInfo::ArgTypes::None, 8 }, // 4C
    {"ED 4D: RETI",                       OpcodeInfo::ArgTypes::None, 14}, // 4D
    {"ED 4E: IM * (0?)",                  OpcodeInfo::ArgTypes::None, 8 }, // 4E
    {"ED 4F: LD R,A",                     OpcodeInfo::ArgTypes::None, 9 }, // 4F
    {"ED 50: IN D,(C)",                   OpcodeInfo::ArgTypes::None, 12}, // 50
    {"ED 51: OUT (C),D",                  OpcodeInfo::ArgTypes::None, 12}, // 51
    {"ED 52: SBC HL,DE",                  OpcodeInfo::ArgTypes::None, 15}, // 52
    {"ED 53 %02X %02X: LD (%04X),DE",     OpcodeInfo::ArgTypes::NN,   20}, // 53
    {"ED 54: NEG",                        OpcodeInfo::ArgTypes::None, 8 }, // 54
    {"ED 55: RETN",                       OpcodeInfo::ArgTypes::None, 14}, // 55
    {"ED 56: IM 1",                       OpcodeInfo::ArgTypes::None, 8 }, // 56
    {"ED 57: LD A,I",                     OpcodeInfo::ArgTypes::None, 9 }, // 57
    {"ED 58: IN E,(C)",                   OpcodeInfo::ArgTypes::None, 12}, // 58
    {"ED 59: OUT (C),E",                  OpcodeInfo::ArgTypes::None, 12}, // 59
    {"ED 5A: ADC HL,DE",                  OpcodeInfo::ArgTypes::None, 15}, // 5A
    {"ED 5B %02X %02X: LD DE,(%04X)",     OpcodeInfo::ArgTypes::NN,   20}, // 5B
    {"ED 5C: NEG",                        OpcodeInfo::ArgTypes::None, 8 }, // 5C
    {"ED 5D: RETI",                       OpcodeInfo::ArgTypes::None, 14}, // 5D
    {"ED 5E: IM 2",                       OpcodeInfo::ArgTypes::None, 8 }, // 5E
    {"ED 5F: LD A,R",                     OpcodeInfo::ArgTypes::None, 9 }, // 5F
    {"ED 60: IN H,(C)",                   OpcodeInfo::ArgTypes::None, 12}, // 60
    {"ED 61: OUT (C),H",                  OpcodeInfo::ArgTypes::None, 12}, // 61
    {"ED 62: SBC HL,HL",                  OpcodeInfo::ArgTypes::None, 15}, // 62
    {"ED 63 %02X %02X: LD (%04X),HL",     OpcodeInfo::ArgTypes::NN,   20}, // 63
    {"ED 64: NEG",                        OpcodeInfo::ArgTypes::None, 8 }, // 64
    {"ED 65: RETN",                       OpcodeInfo::ArgTypes::None, 14}, // 65
    {"ED 66: IM 0",                       OpcodeInfo::ArgTypes::None, 8 }, // 66
    {"ED 67: RRD",                        OpcodeInfo::ArgTypes::None, 18}, // 67
    {"ED 68: IN L,(C)",                   OpcodeInfo::ArgTypes::None, 12}, // 68
    {"ED 69: OUT (C),L",                  OpcodeInfo::ArgTypes::None, 12}, // 69
    {"ED 6A: ADC HL,HL",                  OpcodeInfo::ArgTypes::None, 15}, // 6A
    {"ED 6B %02X %02X: LD HL,(%04X)",     OpcodeInfo::ArgTypes::NN,   20}, // 6B
    {"ED 6C: NEG",                        OpcodeInfo::ArgTypes::None, 8 }, // 6C
    {"ED 6D: RETI",                       OpcodeInfo::ArgTypes::None, 14}, // 6D
    {"ED 6E: IM * (0?)",                  OpcodeInfo::ArgTypes::None, 8 }, // 6E
    {"ED 6F: RLD",                        OpcodeInfo::ArgTypes::None, 18}, // 6F
    {"ED 70: IN X,(C)",                   OpcodeInfo::ArgTypes::None, 12}, // 70
    {"ED 71: OUT (C),X(0)",               OpcodeInfo::ArgTypes::None, 12}, // 71
    {"ED 72: SBC HL,SP",                  OpcodeInfo::ArgTypes::None, 15}, // 72
    {"ED 73 %02X %02X: LD (%04X),SP",     OpcodeInfo::ArgTypes::NN,   20}, // 73
    {"ED 74: NEG",                        OpcodeInfo::ArgTypes::None, 8 }, // 74
    {"ED 75: RETN",                       OpcodeInfo::ArgTypes::None, 14}, // 75
    {"ED 76: IM 1",                       OpcodeInfo::ArgTypes::None, 8 }, // 76
    {"ED 77: NOP",                        OpcodeInfo::ArgTypes::None, 8 }, // 77
    {"ED 78: IN A,(C)",                   OpcodeInfo::ArgTypes::None, 12}, // 78
    {"ED 79: OUT (C),A",                  OpcodeInfo::ArgTypes::None, 12}, // 79
    {"ED 7A: ADC HL,SP",                  OpcodeInfo::ArgTypes::None, 15}, // 7A
    {"ED 7B %02X %02X: LD SP,(%04X)",     OpcodeInfo::ArgTypes::NN,   20}, // 7B
    {"ED 7C: NEG",                        OpcodeInfo::ArgTypes::None, 8 }, // 7C
    {"ED 7D: RETI",                       OpcodeInfo::ArgTypes::None, 14}, // 7D
    {"ED 7E: IM 2",                       OpcodeInfo::ArgTypes::None, 8 }, // 7E
    {"ED 7F: NOP",                        OpcodeInfo::ArgTypes::None, 8 }, // 7F
    {"ED 80: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 80
    {"ED 81: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 81
    {"ED 82: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 82
    {"ED 83: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 83
    {"ED 84: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 84
    {"ED 85: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 85
    {"ED 86: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 86
    {"ED 87: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 87
    {"ED 88: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 88
    {"ED 89: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 89
    {"ED 8A: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 8A
    {"ED 8B: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 8B
    {"ED 8C: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 8C
    {"ED 8D: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 8D
    {"ED 8E: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 8E
    {"ED 8F: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 8F
    {"ED 90: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 90
    {"ED 91: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 91
    {"ED 92: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 92
    {"ED 93: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 93
    {"ED 94: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 94
    {"ED 95: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 95
    {"ED 96: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 96
    {"ED 97: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 97
    {"ED 98: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 98
    {"ED 99: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 99
    {"ED 9A: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 9A
    {"ED 9B: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 9B
    {"ED 9C: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 9C
    {"ED 9D: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 9D
    {"ED 9E: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 9E
    {"ED 9F: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // 9F
    {"ED A0: LDI",                        OpcodeInfo::ArgTypes::None, 16}, // A0
    {"ED A1: CPI",                        OpcodeInfo::ArgTypes::None, 16}, // A1
    {"ED A2: INI",                        OpcodeInfo::ArgTypes::None, 16}, // A2
    {"ED A3: OUTI",                       OpcodeInfo::ArgTypes::None, 16}, // A3
    {"ED A4: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // A4
    {"ED A5: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // A5
    {"ED A6: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // A6
    {"ED A7: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // A7
    {"ED A8: LDD",                        OpcodeInfo::ArgTypes::None, 16}, // A8
    {"ED A9: CPD",                        OpcodeInfo::ArgTypes::None, 16}, // A9
    {"ED AA: IND",                        OpcodeInfo::ArgTypes::None, 16}, // AA
    {"ED AB: OUTD",                       OpcodeInfo::ArgTypes::None, 16}, // AB
    {"ED AC: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // AC
    {"ED AD: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // AD
    {"ED AE: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // AE
    {"ED AF: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // AF
    {"ED B0: LDIR",                       OpcodeInfo::ArgTypes::None, 21}, // B0
    {"ED B1: CPIR",                       OpcodeInfo::ArgTypes::None, 16}, // B1
    {"ED B2: INIR",                       OpcodeInfo::ArgTypes::None, 16}, // B2
    {"ED B3: OTIR",                       OpcodeInfo::ArgTypes::None, 16}, // B3
    {"ED B4: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // B4
    {"ED B5: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // B5
    {"ED B6: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // B6
    {"ED B7: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // B7
    {"ED B8: LDDR",                       OpcodeInfo::ArgTypes::None, 21}, // B8
    {"ED B9: CPDR",                       OpcodeInfo::ArgTypes::None, 16}, // B9
    {"ED BA: INDR",                       OpcodeInfo::ArgTypes::None, 16}, // BA
    {"ED BB: OTDR",                       OpcodeInfo::ArgTypes::None, 16}, // BB
    {"ED BC: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // BC
    {"ED BD: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // BD
    {"ED BE: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // BE
    {"ED BF: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // BF
    {"ED C0: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // C0
    {"ED C1: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // C1
    {"ED C2: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // C2
    {"ED C3: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // C3
    {"ED C4: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // C4
    {"ED C5: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // C5
    {"ED C6: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // C6
    {"ED C7: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // C7
    {"ED C8: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // C8
    {"ED C9: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // C9
    {"ED CA: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // CA
    {"ED CB: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // CB
    {"ED CC: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // CC
    {"ED CD: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // CD
    {"ED CE: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // CE
    {"ED CF: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // CF
    {"ED D0: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // D0
    {"ED D1: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // D1
    {"ED D2: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // D2
    {"ED D3: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // D3
    {"ED D4: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // D4
    {"ED D5: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // D5
    {"ED D6: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // D6
    {"ED D7: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // D7
    {"ED D8: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // D8
    {"ED D9: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // D9
    {"ED DA: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // DA
    {"ED DB: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // DB
    {"ED DC: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // DC
    {"ED DD: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // DD
    {"ED DE: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // DE
    {"ED DF: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // DF
    {"ED E0: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // E0
    {"ED E1: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // E1
    {"ED E2: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // E2
    {"ED E3: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // E3
    {"ED E4: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // E4
    {"ED E5: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // E5
    {"ED E6: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // E6
    {"ED E7: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // E7
    {"ED E8: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // E8
    {"ED E9: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // E9
    {"ED EA: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // EA
    {"ED EB: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // EB
    {"ED EC: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // EC
    {"ED ED: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // ED
    {"ED EE: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // EE
    {"ED EF: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // EF
    {"ED F0: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // F0
    {"ED F1: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // F1
    {"ED F2: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // F2
    {"ED F3: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // F3
    {"ED F4: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // F4
    {"ED F5: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // F5
    {"ED F6: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // F6
    {"ED F7: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // F7
    {"ED F8: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // F8
    {"ED F9: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // F9
    {"ED FA: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // FA
    {"ED FB: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // FB
    {"ED FC: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // FC
    {"ED FD: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // FD
    {"ED FE: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // FE
    {"ED FF: NOP",                        OpcodeInfo::ArgTypes::None, 4 }, // FF
}};

inline constexpr std::array<OpcodeInfo, 256> OpcodeTableFD = {{
    {"FD 00: NOP",                        OpcodeInfo::ArgTypes::None, 8 }, // 00
    {"FD 01 %02X %02X: LD BC,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // 01
    {"FD 02: LD (BC),A",                  OpcodeInfo::ArgTypes::None, 11}, // 02
    {"FD 03: INC BC",                     OpcodeInfo::ArgTypes::None, 10}, // 03
    {"FD 04: INC B",                      OpcodeInfo::ArgTypes::None, 8 }, // 04
    {"FD 05: DEC B",                      OpcodeInfo::ArgTypes::None, 8 }, // 05
    {"FD 06 %02X: LD B,%02X",             OpcodeInfo::ArgTypes::N,    11}, // 06
    {"FD 07: RLCA",                       OpcodeInfo::ArgTypes::None, 8 }, // 07
    {"FD 08: EX AF,AF'",                  OpcodeInfo::ArgTypes::None, 8 }, // 08
    {"FD 09: ADD IY,BC",                  OpcodeInfo::ArgTypes::None, 15}, // 09
    {"FD 0A: LD A,(BC)",                  OpcodeInfo::ArgTypes::None, 11}, // 0A
    {"FD 0B: DEC BC",                     OpcodeInfo::ArgTypes::None, 10}, // 0B
    {"FD 0C: INC C",                      OpcodeInfo::ArgTypes::None, 8 }, // 0C
    {"FD 0D: DEC C",                      OpcodeInfo::ArgTypes::None, 8 }, // 0D
    {"FD 0E %02X: LD C,%02X",             OpcodeInfo::ArgTypes::N,    11}, // 0E
    {"FD 0F: RRCA",                       OpcodeInfo::ArgTypes::None, 8 }, // 0F
    {"FD 10 %02X: DJNZ %d",               OpcodeInfo::ArgTypes::D,    12}, // 10
    {"FD 11 %02X %02X: LD DE,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // 11
    {"FD 12: LD (DE),A",                  OpcodeInfo::ArgTypes::None, 11}, // 12
    {"FD 13: INC DE",                     OpcodeInfo::ArgTypes::None, 10}, // 13
    {"FD 14: INC D",                      OpcodeInfo::ArgTypes::None, 8 }, // 14
    {"FD 15: DEC D",                      OpcodeInfo::ArgTypes::None, 8 }, // 15
    {"FD 16 %02X: LD D,%02X",             OpcodeInfo::ArgTypes::N,    11}, // 16
    {"FD 17: RLA",                        OpcodeInfo::ArgTypes::None, 8 }, // 17
    {"FD 18 %02X: JR %d",                 OpcodeInfo::ArgTypes::D,    16}, // 18
    {"FD 19: ADD IY,DE",                  OpcodeInfo::ArgTypes::None, 15}, // 19
    {"FD 1A: LD A,(DE)",                  OpcodeInfo::ArgTypes::None, 11}, // 1A
    {"FD 1B: DEC DE",                     OpcodeInfo::ArgTypes::None, 10}, // 1B
    {"FD 1C: INC E",                      OpcodeInfo::ArgTypes::None, 8 }, // 1C
    {"FD 1D: DEC E",                      OpcodeInfo::ArgTypes::None, 8 }, // 1D
    {"FD 1E %02X: LD E,%02X",             OpcodeInfo::ArgTypes::N,    11}, // 1E
    {"FD 1F: RRA",                        OpcodeInfo::ArgTypes::None, 8 }, // 1F
    {"FD 20 %02X: JR NZ,%d",              OpcodeInfo::ArgTypes::D,    11}, // 20
    {"FD 21 %02X %02X: LD IY,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // 21
    {"FD 22 %02X %02X: LD (%04X),IY",     OpcodeInfo::ArgTypes::NN,   20}, // 22
    {"FD 23: INC IY",                     OpcodeInfo::ArgTypes::None, 10}, // 23
    {"FD 24: INC IYh",                    OpcodeInfo::ArgTypes::None, 8 }, // 24
    {"FD 25: DEC IYh",                    OpcodeInfo::ArgTypes::None, 8 }, // 25
    {"FD 26 %02X: LD IYh,%02X",           OpcodeInfo::ArgTypes::N,    11}, // 26
    {"FD 27: DAA",                        OpcodeInfo::ArgTypes::None, 8 }, // 27
    {"FD 28 %02X: JR Z,%d",               OpcodeInfo::ArgTypes::D,    11}, // 28
    {"FD 29: ADD IY,IY",                  OpcodeInfo::ArgTypes::None, 15}, // 29
    {"FD 2A %02X %02X: LD IY,(%04X)",     OpcodeInfo::ArgTypes::NN,   20}, // 2A
    {"FD 2B: DEC IY",                     OpcodeInfo::ArgTypes::None, 10}, // 2B
    {"FD 2C: INC IYl",                    OpcodeInfo::ArgTypes::None, 8 }, // 2C
    {"FD 2D: DEC IYl",                    OpcodeInfo::ArgTypes::None, 8 }, // 2D
    {"FD 2E %02X: LD IYl,%02X",           OpcodeInfo::ArgTypes::N,    11}, // 2E
    {"FD 2F: CPL",                        OpcodeInfo::ArgTypes::None, 8 }, // 2F
    {"FD 30 %02X: JR NC,%d",              OpcodeInfo::ArgTypes::D,    11}, // 30
    {"FD 31 %02X %02X: LD SP,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // 31
    {"FD 32 %02X %02X: LD (%04X),A",      OpcodeInfo::ArgTypes::NN,   17}, // 32
    {"FD 33: INC SP",                     OpcodeInfo::ArgTypes::None, 10}, // 33
    {"FD 34 %02X: INC (IY+%d)",           OpcodeInfo::ArgTypes::D,    23}, // 34
    {"FD 35 %02X: DEC (IY+%d)",           OpcodeInfo::ArgTypes::D,    23}, // 35
    {"FD 36 %02X %02X: LD (IY+%d),%02X",  OpcodeInfo::ArgTypes::DN,   19}, // 36
    {"FD 37: SCF",                        OpcodeInfo::ArgTypes::None, 8 }, // 37
    {"FD 38 %02X: JR C,%d",               OpcodeInfo::ArgTypes::D,    11}, // 38
    {"FD 39: ADD IY,SP",                  OpcodeInfo::ArgTypes::None, 15}, // 39
    {"FD 3A %02X %02X: LD A,(%04X)",      OpcodeInfo::ArgTypes::NN,   17}, // 3A
    {"FD 3B: DEC SP",                     OpcodeInfo::ArgTypes::None, 10}, // 3B
    {"FD 3C: INC A",                      OpcodeInfo::ArgTypes::None, 8 }, // 3C
    {"FD 3D: DEC A",                      OpcodeInfo::ArgTypes::None, 8 }, // 3D
    {"FD 3E %02X: LD A,%02X",             OpcodeInfo::ArgTypes::N,    11}, // 3E
    {"FD 3F: CCF",                        OpcodeInfo::ArgTypes::None, 8 }, // 3F
    {"FD 40: LD B,B",                     OpcodeInfo::ArgTypes::None, 8 }, // 40
    {"FD 41: LD B,C",                     OpcodeInfo::ArgTypes::None, 8 }, // 41
    {"FD 42: LD B,D",                     OpcodeInfo::ArgTypes::None, 8 }, // 42
    {"FD 43: LD B,E",                     OpcodeInfo::ArgTypes::None, 8 }, // 43
    {"FD 44: LD B,IYh",                   OpcodeInfo::ArgTypes::None, 8 }, // 44
    {"FD 45: LD B,IYl",                   OpcodeInfo::ArgTypes::None, 8 }, // 45
    {"FD 46 %02X: LD B,(IY+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 46
    {"FD 47: LD B,A",                     OpcodeInfo::ArgTypes::None, 8 }, // 47
    {"FD 48: LD C,B",                     OpcodeInfo::ArgTypes::None, 8 }, // 48
    {"FD 49: LD C,C",                     OpcodeInfo::ArgTypes::None, 8 }, // 49
    {"FD 4A: LD C,D",                     OpcodeInfo::ArgTypes::None, 8 }, // 4A
    {"FD 4B: LD C,E",                     OpcodeInfo::ArgTypes::None, 8 }, // 4B
    {"FD 4C: LD C,IYh",                   OpcodeInfo::ArgTypes::None, 8 }, // 4C
    {"FD 4D: LD C,IYl",                   OpcodeInfo::ArgTypes::None, 8 }, // 4D
    {"FD 4E %02X: LD C,(IY+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 4E
    {"FD 4F: LD C,A",                     OpcodeInfo::ArgTypes::None, 8 }, // 4F
    {"FD 50: LD D,B",                     OpcodeInfo::ArgTypes::None, 8 }, // 50
    {"FD 51: LD D,C",                     OpcodeInfo::ArgTypes::None, 8 }, // 51
    {"FD 52: LD D,D",                     OpcodeInfo::ArgTypes::None, 8 }, // 52
    {"FD 53: LD D,E",                     OpcodeInfo::ArgTypes::None, 8 }, // 53
    {"FD 54: LD D,IYh",                   OpcodeInfo::ArgTypes::None, 8 }, // 54
    {"FD 55: LD D,IYl",                   OpcodeInfo::ArgTypes::None, 8 }, // 55
    {"FD 56 %02X: LD D,(IY+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 56
    {"FD 57: LD D,A",                     OpcodeInfo::ArgTypes::None, 8 }, // 57
    {"FD 58: LD E,B",                     OpcodeInfo::ArgTypes::None, 8 }, // 58
    {"FD 59: LD E,C",                     OpcodeInfo::ArgTypes::None, 8 }, // 59
    {"FD 5A: LD E,D",                     OpcodeInfo::ArgTypes::None, 8 }, // 5A
    {"FD 5B: LD E,E",                     OpcodeInfo::ArgTypes::None, 8 }, // 5B
    {"FD 5C: LD E,IYh",                   OpcodeInfo::ArgTypes::None, 8 }, // 5C
    {"FD 5D: LD E,IYl",                   OpcodeInfo::ArgTypes::None, 8 }, // 5D
    {"FD 5E %02X: LD E,(IY+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 5E
    {"FD 5F: LD E,A",                     OpcodeInfo::ArgTypes::None, 8 }, // 5F
    {"FD 60: LD IYh,B",                   OpcodeInfo::ArgTypes::None, 8 }, // 60
    {"FD 61: LD IYh,C",                   OpcodeInfo::ArgTypes::None, 8 }, // 61
    {"FD 62: LD IYh,D",                   OpcodeInfo::ArgTypes::None, 8 }, // 62
    {"FD 63: LD IYh,E",                   OpcodeInfo::ArgTypes::None, 8 }, // 63
    {"FD 64: LD IYh,IYh",                 OpcodeInfo::ArgTypes::None, 8 }, // 64
    {"FD 65: LD IYh,IYl",                 OpcodeInfo::ArgTypes::None, 8 }, // 65
    {"FD 66 %02X: LD H,(IY+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 66
    {"FD 67: LD IYh,A",                   OpcodeInfo::ArgTypes::None, 8 }, // 67
    {"FD 68: LD IYl,B",                   OpcodeInfo::ArgTypes::None, 8 }, // 68
    {"FD 69: LD IYl,C",                   OpcodeInfo::ArgTypes::None, 8 }, // 69
    {"FD 6A: LD IYl,D",                   OpcodeInfo::ArgTypes::None, 8 }, // 6A
    {"FD 6B: LD IYl,E",                   OpcodeInfo::ArgTypes::None, 8 }, // 6B
    {"FD 6C: LD IYl,IYh",                 OpcodeInfo::ArgTypes::None, 8 }, // 6C
    {"FD 6D: LD IYl,IYl",                 OpcodeInfo::ArgTypes::None, 8 }, // 6D
    {"FD 6E %02X: LD L,(IY+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 6E
    {"FD 6F: LD IYl,A",                   OpcodeInfo::ArgTypes::None, 8 }, // 6F
    {"FD 70 %02X: LD (IY+%d),B",          OpcodeInfo::ArgTypes::D,    19}, // 70
    {"FD 71 %02X: LD (IY+%d),C",          OpcodeInfo::ArgTypes::D,    19}, // 71
    {"FD 72 %02X: LD (IY+%d),D",          OpcodeInfo::ArgTypes::D,    19}, // 72
    {"FD 73 %02X: LD (IY+%d),E",          OpcodeInfo::ArgTypes::D,    19}, // 73
    {"FD 74 %02X: LD (IY+%d),H",          OpcodeInfo::ArgTypes::D,    19}, // 74
    {"FD 75 %02X: LD (IY+%d),L",          OpcodeInfo::ArgTypes::D,    19}, // 75
    {"FD 76: HALT",                       OpcodeInfo::ArgTypes::None, 8 }, // 76
    {"FD 77 %02X: LD (IY+%d),A",          OpcodeInfo::ArgTypes::D,    19}, // 77
    {"FD 78: LD A,B",                     OpcodeInfo::ArgTypes::None, 8 }, // 78
    {"FD 79: LD A,C",                     OpcodeInfo::ArgTypes::None, 8 }, // 79
    {"FD 7A: LD A,D",                     OpcodeInfo::ArgTypes::None, 8 }, // 7A
    {"FD 7B: LD A,E",                     OpcodeInfo::ArgTypes::None, 8 }, // 7B
    {"FD 7C: LD A,IYh",                   OpcodeInfo::ArgTypes::None, 8 }, // 7C
    {"FD 7D: LD A,IYl",                   OpcodeInfo::ArgTypes::None, 8 }, // 7D
    {"FD 7E %02X: LD A,(IY+%d)",          OpcodeInfo::ArgTypes::D,    19}, // 7E
    {"FD 7F: LD A,A",                     OpcodeInfo::ArgTypes::None, 8 }, // 7F
    {"FD 80: ADD A,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 80
    {"FD 81: ADD A,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 81
    {"FD 82: ADD A,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 82
    {"FD 83: ADD A,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 83
    {"FD 84: ADD A,IYh",                  OpcodeInfo::ArgTypes::None, 8 }, // 84
    {"FD 85: ADD A,IYl",                  OpcodeInfo::ArgTypes::None, 8 }, // 85
    {"FD 86 %02X: ADD A,(IY+%d)",         OpcodeInfo::ArgTypes::D,    19}, // 86
    {"FD 87: ADD A,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 87
    {"FD 88: ADC A,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 88
    {"FD 89: ADC A,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 89
    {"FD 8A: ADC A,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 8A
    {"FD 8B: ADC A,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 8B
    {"FD 8C: ADC A,IYh",                  OpcodeInfo::ArgTypes::None, 8 }, // 8C
    {"FD 8D: ADC A,IYl",                  OpcodeInfo::ArgTypes::None, 8 }, // 8D
    {"FD 8E %02X: ADC A,(IY+%d)",         OpcodeInfo::ArgTypes::D,    19}, // 8E
    {"FD 8F: ADC A,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 8F
    {"FD 90: SUB B",                      OpcodeInfo::ArgTypes::None, 8 }, // 90
    {"FD 91: SUB C",                      OpcodeInfo::ArgTypes::None, 8 }, // 91
    {"FD 92: SUB D",                      OpcodeInfo::ArgTypes::None, 8 }, // 92
    {"FD 93: SUB E",                      OpcodeInfo::ArgTypes::None, 8 }, // 93
    {"FD 94: SUB IYh",                    OpcodeInfo::ArgTypes::None, 8 }, // 94
    {"FD 95: SUB IYl",                    OpcodeInfo::ArgTypes::None, 8 }, // 95
    {"FD 96 %02X: SUB (IY+%d)",           OpcodeInfo::ArgTypes::D,    19}, // 96
    {"FD 97: SUB A",                      OpcodeInfo::ArgTypes::None, 8 }, // 97
    {"FD 98: SBC A,B",                    OpcodeInfo::ArgTypes::None, 8 }, // 98
    {"FD 99: SBC A,C",                    OpcodeInfo::ArgTypes::None, 8 }, // 99
    {"FD 9A: SBC A,D",                    OpcodeInfo::ArgTypes::None, 8 }, // 9A
    {"FD 9B: SBC A,E",                    OpcodeInfo::ArgTypes::None, 8 }, // 9B
    {"FD 9C: SBC A,IYh",                  OpcodeInfo::ArgTypes::None, 8 }, // 9C
    {"FD 9D: SBC A,IYl",                  OpcodeInfo::ArgTypes::None, 8 }, // 9D
    {"FD 9E %02X: SBC A,(IY+%d)",         OpcodeInfo::ArgTypes::D,    19}, // 9E
    {"FD 9F: SBC A,A",                    OpcodeInfo::ArgTypes::None, 8 }, // 9F
    {"FD A0: AND B",                      OpcodeInfo::ArgTypes::None, 8 }, // A0
    {"FD A1: AND C",                      OpcodeInfo::ArgTypes::None, 8 }, // A1
    {"FD A2: AND D",                      OpcodeInfo::ArgTypes::None, 8 }, // A2
    {"FD A3: AND E",                      OpcodeInfo::ArgTypes::None, 8 }, // A3
    {"FD A4: AND IYh",                    OpcodeInfo::ArgTypes::None, 8 }, // A4
    {"FD A5: AND IYl",                    OpcodeInfo::ArgTypes::None, 8 }, // A5
    {"FD A6 %02X: AND (IY+%d)",           OpcodeInfo::ArgTypes::D,    19}, // A6
    {"FD A7: AND A",                      OpcodeInfo::ArgTypes::None, 8 }, // A7
    {"FD A8: XOR B",                      OpcodeInfo::ArgTypes::None, 8 }, // A8
    {"FD A9: XOR C",                      OpcodeInfo::ArgTypes::None, 8 }, // A9
    {"FD AA: XOR D",                      OpcodeInfo::ArgTypes::None, 8 }, // AA
    {"FD AB: XOR E",                      OpcodeInfo::ArgTypes::None, 8 }, // AB
    {"FD AC: XOR IYh",                    OpcodeInfo::ArgTypes::None, 8 }, // AC
    {"FD AD: XOR IYl",                    OpcodeInfo::ArgTypes::None, 8 }, // AD
    {"FD AE %02X: XOR (IY+%d)",           OpcodeInfo::ArgTypes::D,    19}, // AE
    {"FD AF: XOR A",                      OpcodeInfo::ArgTypes::None, 8 }, // AF
    {"FD B0: OR B",                       OpcodeInfo::ArgTypes::None, 8 }, // B0
    {"FD B1: OR C",                       OpcodeInfo::ArgTypes::None, 8 }, // B1
    {"FD B2: OR D",                       OpcodeInfo::ArgTypes::None, 8 }, // B2
    {"FD B3: OR E",                       OpcodeInfo::ArgTypes::None, 8 }, // B3
    {"FD B4: OR IYh",                     OpcodeInfo::ArgTypes::None, 8 }, // B4
    {"FD B5: OR IYl",                     OpcodeInfo::ArgTypes::None, 8 }, // B5
    {"FD B6 %02X: OR (IY+%d)",            OpcodeInfo::ArgTypes::D,    19}, // B6
    {"FD B7: OR A",                       OpcodeInfo::ArgTypes::None, 8 }, // B7
    {"FD B8: CP B",                       OpcodeInfo::ArgTypes::None, 8 }, // B8
    {"FD B9: CP C",                       OpcodeInfo::ArgTypes::None, 8 }, // B9
    {"FD BA: CP D",                       OpcodeInfo::ArgTypes::None, 8 }, // BA
    {"FD BB: CP E",                       OpcodeInfo::ArgTypes::None, 8 }, // BB
    {"FD BC: CP IYh",                     OpcodeInfo::ArgTypes::None, 8 }, // BC
    {"FD BD: CP IYl",                     OpcodeInfo::ArgTypes::None, 8 }, // BD
    {"FD BE %02X: CP (IY+%d)",            OpcodeInfo::ArgTypes::D,    19}, // BE
    {"FD BF: CP A",                       OpcodeInfo::ArgTypes::None, 8 }, // BF
    {"FD C0: RET NZ",                     OpcodeInfo::ArgTypes::None, 9 }, // C0
    {"FD C1: POP BC",                     OpcodeInfo::ArgTypes::None, 14}, // C1
    {"FD C2 %02X %02X: JP NZ,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // C2
    {"FD C3 %02X %02X: JP %04X",          OpcodeInfo::ArgTypes::NN,   14}, // C3
    {"FD C4 %02X %02X: CALL NZ,%04X",     OpcodeInfo::ArgTypes::NN,   14}, // C4
    {"FD C5: PUSH BC",                    OpcodeInfo::ArgTypes::None, 15}, // C5
    {"FD C6 %02X: ADD A,%02X",            OpcodeInfo::ArgTypes::N,    11}, // C6
    {"FD C7: RST 0",                      OpcodeInfo::ArgTypes::None, 15}, // C7
    {"FD C8: RET Z",                      OpcodeInfo::ArgTypes::None, 9 }, // C8
    {"FD C9: RET",                        OpcodeInfo::ArgTypes::None, 14}, // C9
    {"FD CA %02X %02X: JP Z,%04X",        OpcodeInfo::ArgTypes::NN,   14}, // CA
    {"FD CB %02X: [See DDCB i%02Xfo]",    OpcodeInfo::ArgTypes::N,    4 }, // CB
    {"FD CC %02X %02X: CALL Z,%04X",      OpcodeInfo::ArgTypes::NN,   14}, // CC
    {"FD CD %02X %02X: CALL %04X",        OpcodeInfo::ArgTypes::NN,   21}, // CD
    {"FD CE %02X: ADC A,%02X",            OpcodeInfo::ArgTypes::N,    11}, // CE
    {"FD CF: RST 8",                      OpcodeInfo::ArgTypes::None, 15}, // CF
    {"FD D0: RET NC",                     OpcodeInfo::ArgTypes::None, 9 }, // D0
    {"FD D1: POP DE",                     OpcodeInfo::ArgTypes::None, 14}, // D1
    {"FD D2 %02X %02X: JP NC,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // D2
    {"FD D3 %02X: OUT (%02X),A",          OpcodeInfo::ArgTypes::N,    15}, // D3
    {"FD D4 %02X %02X: CALL NC,%04X",     OpcodeInfo::ArgTypes::NN,   14}, // D4
    {"FD D5: PUSH DE",                    OpcodeInfo::ArgTypes::None, 15}, // D5
    {"FD D6 %02X: SUB %02X",              OpcodeInfo::ArgTypes::N,    11}, // D6
    {"FD D7: RST 10H",                    OpcodeInfo::ArgTypes::None, 15}, // D7
    {"FD D8: RET C",                      OpcodeInfo::ArgTypes::None, 9 }, // D8
    {"FD D9: EXX",                        OpcodeInfo::ArgTypes::None, 8 }, // D9
    {"FD DA %02X %02X: JP C,%04X",        OpcodeInfo::ArgTypes::NN,   14}, // DA
    {"FD DB %02X: IN A,(%02X)",           OpcodeInfo::ArgTypes::N,    15}, // DB
    {"FD DC %02X %02X: CALL C,%04X",      OpcodeInfo::ArgTypes::NN,   14}, // DC
    {"FD DD: [IY Prefix]",                OpcodeInfo::ArgTypes::None, 4 }, // DD
    {"FD DE %02X: SBC A,%02X",            OpcodeInfo::ArgTypes::N,    11}, // DE
    {"FD DF: RST 18H",                    OpcodeInfo::ArgTypes::None, 15}, // DF
    {"FD E0: RET PO",                     OpcodeInfo::ArgTypes::None, 9 }, // E0
    {"FD E1: POP IY",                     OpcodeInfo::ArgTypes::None, 14}, // E1
    {"FD E2 %02X %02X: JP PO,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // E2
    {"FD E3: EX (SP),IY",                 OpcodeInfo::ArgTypes::None, 23}, // E3
    {"FD E4 %02X %02X: CALL PO,%04X",     OpcodeInfo::ArgTypes::NN,   14}, // E4
    {"FD E5: PUSH IY",                    OpcodeInfo::ArgTypes::None, 15}, // E5
    {"FD E6 %02X: AND %02X",              OpcodeInfo::ArgTypes::N,    11}, // E6
    {"FD E7: RST 20H",                    OpcodeInfo::ArgTypes::None, 15}, // E7
    {"FD E8: RET PE",                     OpcodeInfo::ArgTypes::None, 9 }, // E8
    {"FD E9: JP (IY)",                    OpcodeInfo::ArgTypes::None, 8 }, // E9
    {"FD EA %02X %02X: JP PE,%04X",       OpcodeInfo::ArgTypes::NN,   14}, // EA
    {"FD EB: EX DE,HL",                   OpcodeInfo::ArgTypes::None, 8 }, // EB
    {"FD EC %02X %02X: CALL PE,%04X",     OpcodeInfo::ArgTypes::NN,   14}, // EC
    {"FD ED: [Prefix]",                   OpcodeInfo::ArgTypes::None, 4 }, // ED
    {"FD EE %02X: XOR %02X",              OpcodeInfo::ArgTypes::N,    11}, // EE
    {"FD EF: RST 28H",                    OpcodeInfo::ArgTypes::None, 15}, // EF
    {"FD F0: RET P",                      OpcodeInfo::ArgTypes::None, 9 }, // F0
    {"FD F1: POP AF",                     OpcodeInfo::ArgTypes::None, 14}, // F1
    {"FD F2 %02X %02X: JP P,%04X",        OpcodeInfo::ArgTypes::NN,   14}, // F2
    {"FD F3: DI",                         OpcodeInfo::ArgTypes::None, 8 }, // F3
    {"FD F4 %02X %02X: CALL P,%04X",      OpcodeInfo::ArgTypes::NN,   14}, // F4
    {"FD F5: PUSH AF",                    OpcodeInfo::ArgTypes::None, 15}, // F5
    {"FD F6 %02X: OR %02X",               OpcodeInfo::ArgTypes::N,    11}, // F6
    {"FD F7: RST 30H",                    OpcodeInfo::ArgTypes::None, 15}, // F7
    {"FD F8: RET M",                      OpcodeInfo::ArgTypes::None, 9 }, // F8
    {"FD F9: LD SP,IY",                   OpcodeInfo::ArgTypes::None, 10}, // F9
    {"FD FA %02X %02X: JP M,%04X",        OpcodeInfo::ArgTypes::NN,   14}, // FA
    {"FD FB: EI",                         OpcodeInfo::ArgTypes::None, 8 }, // FB
    {"FD FC %02X %02X: CALL M,%04X",      OpcodeInfo::ArgTypes::NN,   14}, // FC
    {"FD FD: [IY Prefix]",                OpcodeInfo::ArgTypes::None, 4 }, // FD
    {"FD FE %02X: CP %02X",               OpcodeInfo::ArgTypes::N,    11}, // FE
    {"FD FF: RST 38H",                    OpcodeInfo::ArgTypes::None, 15}, // FF
}};

inline constexpr std::array<OpcodeInfo, 256> OpcodeTableDDCB = {{
    {"DD CB %02X 00: LD B,RLC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 00
    {"DD CB %02X 01: LD C,RLC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 01
    {"DD CB %02X 02: LD D,RLC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 02
    {"DD CB %02X 03: LD E,RLC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 03
    {"DD CB %02X 04: LD H,RLC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 04
    {"DD CB %02X 05: LD L,RLC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 05
    {"DD CB %02X 06: RLC (IX+%d)",        OpcodeInfo::ArgTypes::D,    23}, // 06
    {"DD CB %02X 07: LD A,RLC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 07
    {"DD CB %02X 08: LD B,RRC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 08
    {"DD CB %02X 09: LD C,RRC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 09
    {"DD CB %02X 0A: LD D,RRC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 0A
    {"DD CB %02X 0B: LD E,RRC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 0B
    {"DD CB %02X 0C: LD H,RRC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 0C
    {"DD CB %02X 0D: LD L,RRC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 0D
    {"DD CB %02X 0E: RRC (IX+%d)",        OpcodeInfo::ArgTypes::D,    23}, // 0E
    {"DD CB %02X 0F: LD A,RRC (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 0F
    {"DD CB %02X 10: LD B,RL (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 10
    {"DD CB %02X 11: LD C,RL (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 11
    {"DD CB %02X 12: LD D,RL (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 12
    {"DD CB %02X 13: LD E,RL (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 13
    {"DD CB %02X 14: LD H,RL (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 14
    {"DD CB %02X 15: LD L,RL (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 15
    {"DD CB %02X 16: RL (IX+%d)",         OpcodeInfo::ArgTypes::D,    23}, // 16
    {"DD CB %02X 17: LD A,RL (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 17
    {"DD CB %02X 18: LD B,RR (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 18
    {"DD CB %02X 19: LD C,RR (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 19
    {"DD CB %02X 1A: LD D,RR (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 1A
    {"DD CB %02X 1B: LD E,RR (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 1B
    {"DD CB %02X 1C: LD H,RR (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 1C
    {"DD CB %02X 1D: LD L,RR (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 1D
    {"DD CB %02X 1E: RR (IX+%d)",         OpcodeInfo::ArgTypes::D,    23}, // 1E
    {"DD CB %02X 1F: LD A,RR (IX+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 1F
    {"DD CB %02X 20: LD B,SLA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 20
    {"DD CB %02X 21: LD C,SLA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 21
    {"DD CB %02X 22: LD D,SLA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 22
    {"DD CB %02X 23: LD E,SLA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 23
    {"DD CB %02X 24: LD H,SLA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 24
    {"DD CB %02X 25: LD L,SLA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 25
    {"DD CB %02X 26: SLA (IX+%d)",        OpcodeInfo::ArgTypes::D,    23}, // 26
    {"DD CB %02X 27: LD A,SLA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 27
    {"DD CB %02X 28: LD B,SRA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 28
    {"DD CB %02X 29: LD C,SRA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 29
    {"DD CB %02X 2A: LD D,SRA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 2A
    {"DD CB %02X 2B: LD E,SRA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 2B
    {"DD CB %02X 2C: LD H,SRA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 2C
    {"DD CB %02X 2D: LD L,SRA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 2D
    {"DD CB %02X 2E: SRA (IX+%d)",        OpcodeInfo::ArgTypes::D,    23}, // 2E
    {"DD CB %02X 2F: LD A,SRA (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 2F
    {"DD CB %02X 30: LD B,SLL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 30
    {"DD CB %02X 31: LD C,SLL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 31
    {"DD CB %02X 32: LD D,SLL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 32
    {"DD CB %02X 33: LD E,SLL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 33
    {"DD CB %02X 34: LD H,SLL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 34
    {"DD CB %02X 35: LD L,SLL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 35
    {"DD CB %02X 36: SLL (IX+%d)",        OpcodeInfo::ArgTypes::D,    23}, // 36
    {"DD CB %02X 37: LD A,SLL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 37
    {"DD CB %02X 38: LD B,SRL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 38
    {"DD CB %02X 39: LD C,SRL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 39
    {"DD CB %02X 3A: LD D,SRL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 3A
    {"DD CB %02X 3B: LD E,SRL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 3B
    {"DD CB %02X 3C: LD H,SRL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 3C
    {"DD CB %02X 3D: LD L,SRL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 3D
    {"DD CB %02X 3E: SRL (IX+%d)",        OpcodeInfo::ArgTypes::D,    23}, // 3E
    {"DD CB %02X 3F: LD A,SRL (IX+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 3F
    {"DD CB %02X 40: BIT 0,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 40
    {"DD CB %02X 41: BIT 0,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 41
    {"DD CB %02X 42: BIT 0,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 42
    {"DD CB %02X 43: BIT 0,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 43
    {"DD CB %02X 44: BIT 0,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 44
    {"DD CB %02X 45: BIT 0,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 45
    {"DD CB %02X 46: BIT 0,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 46
    {"DD CB %02X 47: BIT 0,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 47
    {"DD CB %02X 48: BIT 1,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 48
    {"DD CB %02X 49: BIT 1,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 49
    {"DD CB %02X 4A: BIT 1,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 4A
    {"DD CB %02X 4B: BIT 1,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 4B
    {"DD CB %02X 4C: BIT 1,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 4C
    {"DD CB %02X 4D: BIT 1,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 4D
    {"DD CB %02X 4E: BIT 1,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 4E
    {"DD CB %02X 4F: BIT 1,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 4F
    {"DD CB %02X 50: BIT 2,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 50
    {"DD CB %02X 51: BIT 2,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 51
    {"DD CB %02X 52: BIT 2,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 52
    {"DD CB %02X 53: BIT 2,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 53
    {"DD CB %02X 54: BIT 2,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 54
    {"DD CB %02X 55: BIT 2,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 55
    {"DD CB %02X 56: BIT 2,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 56
    {"DD CB %02X 57: BIT 2,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 57
    {"DD CB %02X 58: BIT 3,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 58
    {"DD CB %02X 59: BIT 3,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 59
    {"DD CB %02X 5A: BIT 3,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 5A
    {"DD CB %02X 5B: BIT 3,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 5B
    {"DD CB %02X 5C: BIT 3,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 5C
    {"DD CB %02X 5D: BIT 3,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 5D
    {"DD CB %02X 5E: BIT 3,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 5E
    {"DD CB %02X 5F: BIT 3,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 5F
    {"DD CB %02X 60: BIT 4,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 60
    {"DD CB %02X 61: BIT 4,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 61
    {"DD CB %02X 62: BIT 4,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 62
    {"DD CB %02X 63: BIT 4,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 63
    {"DD CB %02X 64: BIT 4,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 64
    {"DD CB %02X 65: BIT 4,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 65
    {"DD CB %02X 66: BIT 4,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 66
    {"DD CB %02X 67: BIT 4,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 67
    {"DD CB %02X 68: BIT 5,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 68
    {"DD CB %02X 69: BIT 5,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 69
    {"DD CB %02X 6A: BIT 5,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 6A
    {"DD CB %02X 6B: BIT 5,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 6B
    {"DD CB %02X 6C: BIT 5,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 6C
    {"DD CB %02X 6D: BIT 5,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 6D
    {"DD CB %02X 6E: BIT 5,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 6E
    {"DD CB %02X 6F: BIT 5,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 6F
    {"DD CB %02X 70: BIT 6,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 70
    {"DD CB %02X 71: BIT 6,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 71
    {"DD CB %02X 72: BIT 6,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 72
    {"DD CB %02X 73: BIT 6,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 73
    {"DD CB %02X 74: BIT 6,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 74
    {"DD CB %02X 75: BIT 6,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 75
    {"DD CB %02X 76: BIT 6,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 76
    {"DD CB %02X 77: BIT 6,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 77
    {"DD CB %02X 78: BIT 7,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 78
    {"DD CB %02X 79: BIT 7,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 79
    {"DD CB %02X 7A: BIT 7,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 7A
    {"DD CB %02X 7B: BIT 7,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 7B
    {"DD CB %02X 7C: BIT 7,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 7C
    {"DD CB %02X 7D: BIT 7,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 7D
    {"DD CB %02X 7E: BIT 7,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 7E
    {"DD CB %02X 7F: BIT 7,(IX+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 7F
    {"DD CB %02X 80: LD B,RES 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 80
    {"DD CB %02X 81: LD C,RES 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 81
    {"DD CB %02X 82: LD D,RES 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 82
    {"DD CB %02X 83: LD E,RES 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 83
    {"DD CB %02X 84: LD H,RES 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 84
    {"DD CB %02X 85: LD L,RES 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 85
    {"DD CB %02X 86: RES 0,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // 86
    {"DD CB %02X 87: LD A,RES 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 87
    {"DD CB %02X 88: LD B,RES 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 88
    {"DD CB %02X 89: LD C,RES 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 89
    {"DD CB %02X 8A: LD D,RES 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 8A
    {"DD CB %02X 8B: LD E,RES 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 8B
    {"DD CB %02X 8C: LD H,RES 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 8C
    {"DD CB %02X 8D: LD L,RES 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 8D
    {"DD CB %02X 8E: RES 1,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // 8E
    {"DD CB %02X 8F: LD A,RES 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 8F
    {"DD CB %02X 90: LD B,RES 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 90
    {"DD CB %02X 91: LD C,RES 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 91
    {"DD CB %02X 92: LD D,RES 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 92
    {"DD CB %02X 93: LD E,RES 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 93
    {"DD CB %02X 94: LD H,RES 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 94
    {"DD CB %02X 95: LD L,RES 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 95
    {"DD CB %02X 96: RES 2,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // 96
    {"DD CB %02X 97: LD A,RES 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 97
    {"DD CB %02X 98: LD B,RES 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 98
    {"DD CB %02X 99: LD C,RES 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 99
    {"DD CB %02X 9A: LD D,RES 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 9A
    {"DD CB %02X 9B: LD E,RES 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 9B
    {"DD CB %02X 9C: LD H,RES 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 9C
    {"DD CB %02X 9D: LD L,RES 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 9D
    {"DD CB %02X 9E: RES 3,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // 9E
    {"DD CB %02X 9F: LD A,RES 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // 9F
    {"DD CB %02X A0: LD B,RES 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // A0
    {"DD CB %02X A1: LD C,RES 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // A1
    {"DD CB %02X A2: LD D,RES 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // A2
    {"DD CB %02X A3: LD E,RES 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // A3
    {"DD CB %02X A4: LD H,RES 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // A4
    {"DD CB %02X A5: LD L,RES 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // A5
    {"DD CB %02X A6: RES 4,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // A6
    {"DD CB %02X A7: LD A,RES 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // A7
    {"DD CB %02X A8: LD B,RES 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // A8
    {"DD CB %02X A9: LD C,RES 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // A9
    {"DD CB %02X AA: LD D,RES 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // AA
    {"DD CB %02X AB: LD E,RES 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // AB
    {"DD CB %02X AC: LD H,RES 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // AC
    {"DD CB %02X AD: LD L,RES 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // AD
    {"DD CB %02X AE: RES 5,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // AE
    {"DD CB %02X AF: LD A,RES 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // AF
    {"DD CB %02X B0: LD B,RES 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // B0
    {"DD CB %02X B1: LD C,RES 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // B1
    {"DD CB %02X B2: LD D,RES 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // B2
    {"DD CB %02X B3: LD E,RES 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // B3
    {"DD CB %02X B4: LD H,RES 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // B4
    {"DD CB %02X B5: LD L,RES 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // B5
    {"DD CB %02X B6: RES 6,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // B6
    {"DD CB %02X B7: LD A,RES 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // B7
    {"DD CB %02X B8: LD B,RES 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // B8
    {"DD CB %02X B9: LD C,RES 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // B9
    {"DD CB %02X BA: LD D,RES 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // BA
    {"DD CB %02X BB: LD E,RES 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // BB
    {"DD CB %02X BC: LD H,RES 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // BC
    {"DD CB %02X BD: LD L,RES 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // BD
    {"DD CB %02X BE: RES 7,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // BE
    {"DD CB %02X BF: LD A,RES 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // BF
    {"DD CB %02X C0: LD B,SET 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // C0
    {"DD CB %02X C1: LD C,SET 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // C1
    {"DD CB %02X C2: LD D,SET 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // C2
    {"DD CB %02X C3: LD E,SET 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // C3
    {"DD CB %02X C4: LD H,SET 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // C4
    {"DD CB %02X C5: LD L,SET 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // C5
    {"DD CB %02X C6: SET 0,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // C6
    {"DD CB %02X C7: LD A,SET 0,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // C7
    {"DD CB %02X C8: LD B,SET 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // C8
    {"DD CB %02X C9: LD C,SET 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // C9
    {"DD CB %02X CA: LD D,SET 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // CA
    {"DD CB %02X CB: LD E,SET 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // CB
    {"DD CB %02X CC: LD H,SET 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // CC
    {"DD CB %02X CD: LD L,SET 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // CD
    {"DD CB %02X CE: SET 1,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // CE
    {"DD CB %02X CF: LD A,SET 1,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // CF
    {"DD CB %02X D0: LD B,SET 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // D0
    {"DD CB %02X D1: LD C,SET 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // D1
    {"DD CB %02X D2: LD D,SET 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // D2
    {"DD CB %02X D3: LD E,SET 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // D3
    {"DD CB %02X D4: LD H,SET 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // D4
    {"DD CB %02X D5: LD L,SET 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // D5
    {"DD CB %02X D6: SET 2,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // D6
    {"DD CB %02X D7: LD A,SET 2,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // D7
    {"DD CB %02X D8: LD B,SET 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // D8
    {"DD CB %02X D9: LD C,SET 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // D9
    {"DD CB %02X DA: LD D,SET 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // DA
    {"DD CB %02X DB: LD E,SET 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // DB
    {"DD CB %02X DC: LD H,SET 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // DC
    {"DD CB %02X DD: LD L,SET 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // DD
    {"DD CB %02X DE: SET 3,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // DE
    {"DD CB %02X DF: LD A,SET 3,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // DF
    {"DD CB %02X E0: LD B,SET 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // E0
    {"DD CB %02X E1: LD C,SET 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // E1
    {"DD CB %02X E2: LD D,SET 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // E2
    {"DD CB %02X E3: LD E,SET 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // E3
    {"DD CB %02X E4: LD H,SET 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // E4
    {"DD CB %02X E5: LD L,SET 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // E5
    {"DD CB %02X E6: SET 4,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // E6
    {"DD CB %02X E7: LD A,SET 4,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // E7
    {"DD CB %02X E8: LD B,SET 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // E8
    {"DD CB %02X E9: LD C,SET 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // E9
    {"DD CB %02X EA: LD D,SET 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // EA
    {"DD CB %02X EB: LD E,SET 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // EB
    {"DD CB %02X EC: LD H,SET 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // EC
    {"DD CB %02X ED: LD L,SET 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // ED
    {"DD CB %02X EE: SET 5,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // EE
    {"DD CB %02X EF: LD A,SET 5,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // EF
    {"DD CB %02X F0: LD B,SET 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // F0
    {"DD CB %02X F1: LD C,SET 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // F1
    {"DD CB %02X F2: LD D,SET 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // F2
    {"DD CB %02X F3: LD E,SET 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // F3
    {"DD CB %02X F4: LD H,SET 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // F4
    {"DD CB %02X F5: LD L,SET 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // F5
    {"DD CB %02X F6: SET 6,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // F6
    {"DD CB %02X F7: LD A,SET 6,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // F7
    {"DD CB %02X F8: LD B,SET 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // F8
    {"DD CB %02X F9: LD C,SET 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // F9
    {"DD CB %02X FA: LD D,SET 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // FA
    {"DD CB %02X FB: LD E,SET 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // FB
    {"DD CB %02X FC: LD H,SET 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // FC
    {"DD CB %02X FD: LD L,SET 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // FD
    {"DD CB %02X FE: SET 7,(IX+%d)",      OpcodeInfo::ArgTypes::D,    23}, // FE
    {"DD CB %02X FF: LD A,SET 7,(IX+%d)", OpcodeInfo::ArgTypes::D,    23}, // FF
}};

inline constexpr std::array<OpcodeInfo, 256> OpcodeTableFDCB = {{
    {"FD CB %02X 00: LD B,RLC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 00
    {"FD CB %02X 01: LD C,RLC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 01
    {"FD CB %02X 02: LD D,RLC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 02
    {"FD CB %02X 03: LD E,RLC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 03
    {"FD CB %02X 04: LD H,RLC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 04
    {"FD CB %02X 05: LD L,RLC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 05
    {"FD CB %02X 06: RLC (IY+%d)",        OpcodeInfo::ArgTypes::D,    23}, // 06
    {"FD CB %02X 07: LD A,RLC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 07
    {"FD CB %02X 08: LD B,RRC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 08
    {"FD CB %02X 09: LD C,RRC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 09
    {"FD CB %02X 0A: LD D,RRC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 0A
    {"FD CB %02X 0B: LD E,RRC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 0B
    {"FD CB %02X 0C: LD H,RRC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 0C
    {"FD CB %02X 0D: LD L,RRC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 0D
    {"FD CB %02X 0E: RRC (IY+%d)",        OpcodeInfo::ArgTypes::D,    23}, // 0E
    {"FD CB %02X 0F: LD A,RRC (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 0F
    {"FD CB %02X 10: LD B,RL (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 10
    {"FD CB %02X 11: LD C,RL (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 11
    {"FD CB %02X 12: LD D,RL (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 12
    {"FD CB %02X 13: LD E,RL (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 13
    {"FD CB %02X 14: LD H,RL (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 14
    {"FD CB %02X 15: LD L,RL (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 15
    {"FD CB %02X 16: RL (IY+%d)",         OpcodeInfo::ArgTypes::D,    23}, // 16
    {"FD CB %02X 17: LD A,RL (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 17
    {"FD CB %02X 18: LD B,RR (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 18
    {"FD CB %02X 19: LD C,RR (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 19
    {"FD CB %02X 1A: LD D,RR (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 1A
    {"FD CB %02X 1B: LD E,RR (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 1B
    {"FD CB %02X 1C: LD H,RR (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 1C
    {"FD CB %02X 1D: LD L,RR (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 1D
    {"FD CB %02X 1E: RR (IY+%d)",         OpcodeInfo::ArgTypes::D,    23}, // 1E
    {"FD CB %02X 1F: LD A,RR (IY+%d)",    OpcodeInfo::ArgTypes::D,    23}, // 1F
    {"FD CB %02X 20: LD B,SLA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 20
    {"FD CB %02X 21: LD C,SLA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 21
    {"FD CB %02X 22: LD D,SLA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 22
    {"FD CB %02X 23: LD E,SLA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 23
    {"FD CB %02X 24: LD H,SLA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 24
    {"FD CB %02X 25: LD L,SLA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 25
    {"FD CB %02X 26: SLA (IY+%d)",        OpcodeInfo::ArgTypes::D,    23}, // 26
    {"FD CB %02X 27: LD A,SLA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 27
    {"FD CB %02X 28: LD B,SRA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 28
    {"FD CB %02X 29: LD C,SRA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 29
    {"FD CB %02X 2A: LD D,SRA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 2A
    {"FD CB %02X 2B: LD E,SRA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 2B
    {"FD CB %02X 2C: LD H,SRA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 2C
    {"FD CB %02X 2D: LD L,SRA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 2D
    {"FD CB %02X 2E: SRA (IY+%d)",        OpcodeInfo::ArgTypes::D,    23}, // 2E
    {"FD CB %02X 2F: LD A,SRA (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 2F
    {"FD CB %02X 30: LD B,SLL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 30
    {"FD CB %02X 31: LD C,SLL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 31
    {"FD CB %02X 32: LD D,SLL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 32
    {"FD CB %02X 33: LD E,SLL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 33
    {"FD CB %02X 34: LD H,SLL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 34
    {"FD CB %02X 35: LD L,SLL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 35
    {"FD CB %02X 36: SLL (IY+%d)",        OpcodeInfo::ArgTypes::D,    23}, // 36
    {"FD CB %02X 37: LD A,SLL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 37
    {"FD CB %02X 38: LD B,SRL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 38
    {"FD CB %02X 39: LD C,SRL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 39
    {"FD CB %02X 3A: LD D,SRL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 3A
    {"FD CB %02X 3B: LD E,SRL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 3B
    {"FD CB %02X 3C: LD H,SRL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 3C
    {"FD CB %02X 3D: LD L,SRL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 3D
    {"FD CB %02X 3E: SRL (IY+%d)",        OpcodeInfo::ArgTypes::D,    23}, // 3E
    {"FD CB %02X 3F: LD A,SRL (IY+%d)",   OpcodeInfo::ArgTypes::D,    23}, // 3F
    {"FD CB %02X 40: BIT 0,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 40
    {"FD CB %02X 41: BIT 0,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 41
    {"FD CB %02X 42: BIT 0,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 42
    {"FD CB %02X 43: BIT 0,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 43
    {"FD CB %02X 44: BIT 0,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 44
    {"FD CB %02X 45: BIT 0,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 45
    {"FD CB %02X 46: BIT 0,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 46
    {"FD CB %02X 47: BIT 0,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 47
    {"FD CB %02X 48: BIT 1,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 48
    {"FD CB %02X 49: BIT 1,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 49
    {"FD CB %02X 4A: BIT 1,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 4A
    {"FD CB %02X 4B: BIT 1,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 4B
    {"FD CB %02X 4C: BIT 1,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 4C
    {"FD CB %02X 4D: BIT 1,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 4D
    {"FD CB %02X 4E: BIT 1,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 4E
    {"FD CB %02X 4F: BIT 1,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 4F
    {"FD CB %02X 50: BIT 2,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 50
    {"FD CB %02X 51: BIT 2,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 51
    {"FD CB %02X 52: BIT 2,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 52
    {"FD CB %02X 53: BIT 2,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 53
    {"FD CB %02X 54: BIT 2,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 54
    {"FD CB %02X 55: BIT 2,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 55
    {"FD CB %02X 56: BIT 2,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 56
    {"FD CB %02X 57: BIT 2,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 57
    {"FD CB %02X 58: BIT 3,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 58
    {"FD CB %02X 59: BIT 3,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 59
    {"FD CB %02X 5A: BIT 3,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 5A
    {"FD CB %02X 5B: BIT 3,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 5B
    {"FD CB %02X 5C: BIT 3,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 5C
    {"FD CB %02X 5D: BIT 3,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 5D
    {"FD CB %02X 5E: BIT 3,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 5E
    {"FD CB %02X 5F: BIT 3,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 5F
    {"FD CB %02X 60: BIT 4,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 60
    {"FD CB %02X 61: BIT 4,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 61
    {"FD CB %02X 62: BIT 4,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 62
    {"FD CB %02X 63: BIT 4,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 63
    {"FD CB %02X 64: BIT 4,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 64
    {"FD CB %02X 65: BIT 4,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 65
    {"FD CB %02X 66: BIT 4,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 66
    {"FD CB %02X 67: BIT 4,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 67
    {"FD CB %02X 68: BIT 5,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 68
    {"FD CB %02X 69: BIT 5,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 69
    {"FD CB %02X 6A: BIT 5,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 6A
    {"FD CB %02X 6B: BIT 5,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 6B
    {"FD CB %02X 6C: BIT 5,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 6C
    {"FD CB %02X 6D: BIT 5,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 6D
    {"FD CB %02X 6E: BIT 5,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 6E
    {"FD CB %02X 6F: BIT 5,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 6F
    {"FD CB %02X 70: BIT 6,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 70
    {"FD CB %02X 71: BIT 6,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 71
    {"FD CB %02X 72: BIT 6,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 72
    {"FD CB %02X 73: BIT 6,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 73
    {"FD CB %02X 74: BIT 6,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 74
    {"FD CB %02X 75: BIT 6,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 75
    {"FD CB %02X 76: BIT 6,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 76
    {"FD CB %02X 77: BIT 6,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 77
    {"FD CB %02X 78: BIT 7,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 78
    {"FD CB %02X 79: BIT 7,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 79
    {"FD CB %02X 7A: BIT 7,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 7A
    {"FD CB %02X 7B: BIT 7,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 7B
    {"FD CB %02X 7C: BIT 7,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 7C
    {"FD CB %02X 7D: BIT 7,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 7D
    {"FD CB %02X 7E: BIT 7,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 7E
    {"FD CB %02X 7F: BIT 7,(IY+%d)",      OpcodeInfo::ArgTypes::D,    20}, // 7F
    {"FD CB %02X 80: LD B,RES 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 80
    {"FD CB %02X 81: LD C,RES 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 81
    {"FD CB %02X 82: LD D,RES 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 82
    {"FD CB %02X 83: LD E,RES 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 83
    {"FD CB %02X 84: LD H,RES 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 84
    {"FD CB %02X 85: LD L,RES 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 85
    {"FD CB %02X 86: RES 0,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // 86
    {"FD CB %02X 87: LD A,RES 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 87
    {"FD CB %02X 88: LD B,RES 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 88
    {"FD CB %02X 89: LD C,RES 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 89
    {"FD CB %02X 8A: LD D,RES 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 8A
    {"FD CB %02X 8B: LD E,RES 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 8B
    {"FD CB %02X 8C: LD H,RES 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 8C
    {"FD CB %02X 8D: LD L,RES 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 8D
    {"FD CB %02X 8E: RES 1,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // 8E
    {"FD CB %02X 8F: LD A,RES 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 8F
    {"FD CB %02X 90: LD B,RES 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 90
    {"FD CB %02X 91: LD C,RES 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 91
    {"FD CB %02X 92: LD D,RES 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 92
    {"FD CB %02X 93: LD E,RES 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 93
    {"FD CB %02X 94: LD H,RES 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 94
    {"FD CB %02X 95: LD L,RES 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 95
    {"FD CB %02X 96: RES 2,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // 96
    {"FD CB %02X 97: LD A,RES 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 97
    {"FD CB %02X 98: LD B,RES 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 98
    {"FD CB %02X 99: LD C,RES 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 99
    {"FD CB %02X 9A: LD D,RES 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 9A
    {"FD CB %02X 9B: LD E,RES 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 9B
    {"FD CB %02X 9C: LD H,RES 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 9C
    {"FD CB %02X 9D: LD L,RES 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 9D
    {"FD CB %02X 9E: RES 3,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // 9E
    {"FD CB %02X 9F: LD A,RES 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // 9F
    {"FD CB %02X A0: LD B,RES 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // A0
    {"FD CB %02X A1: LD C,RES 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // A1
    {"FD CB %02X A2: LD D,RES 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // A2
    {"FD CB %02X A3: LD E,RES 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // A3
    {"FD CB %02X A4: LD H,RES 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // A4
    {"FD CB %02X A5: LD L,RES 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // A5
    {"FD CB %02X A6: RES 4,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // A6
    {"FD CB %02X A7: LD A,RES 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // A7
    {"FD CB %02X A8: LD B,RES 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // A8
    {"FD CB %02X A9: LD C,RES 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // A9
    {"FD CB %02X AA: LD D,RES 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // AA
    {"FD CB %02X AB: LD E,RES 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // AB
    {"FD CB %02X AC: LD H,RES 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // AC
    {"FD CB %02X AD: LD L,RES 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // AD
    {"FD CB %02X AE: RES 5,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // AE
    {"FD CB %02X AF: LD A,RES 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // AF
    {"FD CB %02X B0: LD B,RES 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // B0
    {"FD CB %02X B1: LD C,RES 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // B1
    {"FD CB %02X B2: LD D,RES 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // B2
    {"FD CB %02X B3: LD E,RES 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // B3
    {"FD CB %02X B4: LD H,RES 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // B4
    {"FD CB %02X B5: LD L,RES 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // B5
    {"FD CB %02X B6: RES 6,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // B6
    {"FD CB %02X B7: LD A,RES 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // B7
    {"FD CB %02X B8: LD B,RES 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // B8
    {"FD CB %02X B9: LD C,RES 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // B9
    {"FD CB %02X BA: LD D,RES 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // BA
    {"FD CB %02X BB: LD E,RES 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // BB
    {"FD CB %02X BC: LD H,RES 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // BC
    {"FD CB %02X BD: LD L,RES 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // BD
    {"FD CB %02X BE: RES 7,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // BE
    {"FD CB %02X BF: LD A,RES 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // BF
    {"FD CB %02X C0: LD B,SET 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // C0
    {"FD CB %02X C1: LD C,SET 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // C1
    {"FD CB %02X C2: LD D,SET 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // C2
    {"FD CB %02X C3: LD E,SET 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // C3
    {"FD CB %02X C4: LD H,SET 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // C4
    {"FD CB %02X C5: LD L,SET 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // C5
    {"FD CB %02X C6: SET 0,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // C6
    {"FD CB %02X C7: LD A,SET 0,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // C7
    {"FD CB %02X C8: LD B,SET 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // C8
    {"FD CB %02X C9: LD C,SET 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // C9
    {"FD CB %02X CA: LD D,SET 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // CA
    {"FD CB %02X CB: LD E,SET 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // CB
    {"FD CB %02X CC: LD H,SET 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // CC
    {"FD CB %02X CD: LD L,SET 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // CD
    {"FD CB %02X CE: SET 1,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // CE
    {"FD CB %02X CF: LD A,SET 1,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // CF
    {"FD CB %02X D0: LD B,SET 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // D0
    {"FD CB %02X D1: LD C,SET 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // D1
    {"FD CB %02X D2: LD D,SET 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // D2
    {"FD CB %02X D3: LD E,SET 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // D3
    {"FD CB %02X D4: LD H,SET 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // D4
    {"FD CB %02X D5: LD L,SET 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // D5
    {"FD CB %02X D6: SET 2,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // D6
    {"FD CB %02X D7: LD A,SET 2,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // D7
    {"FD CB %02X D8: LD B,SET 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // D8
    {"FD CB %02X D9: LD C,SET 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // D9
    {"FD CB %02X DA: LD D,SET 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // DA
    {"FD CB %02X DB: LD E,SET 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // DB
    {"FD CB %02X DC: LD H,SET 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // DC
    {"FD CB %02X DD: LD L,SET 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // DD
    {"FD CB %02X DE: SET 3,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // DE
    {"FD CB %02X DF: LD A,SET 3,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // DF
    {"FD CB %02X E0: LD B,SET 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // E0
    {"FD CB %02X E1: LD C,SET 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // E1
    {"FD CB %02X E2: LD D,SET 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // E2
    {"FD CB %02X E3: LD E,SET 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // E3
    {"FD CB %02X E4: LD H,SET 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // E4
    {"FD CB %02X E5: LD L,SET 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // E5
    {"FD CB %02X E6: SET 4,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // E6
    {"FD CB %02X E7: LD A,SET 4,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // E7
    {"FD CB %02X E8: LD B,SET 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // E8
    {"FD CB %02X E9: LD C,SET 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // E9
    {"FD CB %02X EA: LD D,SET 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // EA
    {"FD CB %02X EB: LD E,SET 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // EB
    {"FD CB %02X EC: LD H,SET 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // EC
    {"FD CB %02X ED: LD L,SET 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // ED
    {"FD CB %02X EE: SET 5,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // EE
    {"FD CB %02X EF: LD A,SET 5,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // EF
    {"FD CB %02X F0: LD B,SET 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // F0
    {"FD CB %02X F1: LD C,SET 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // F1
    {"FD CB %02X F2: LD D,SET 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // F2
    {"FD CB %02X F3: LD E,SET 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // F3
    {"FD CB %02X F4: LD H,SET 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // F4
    {"FD CB %02X F5: LD L,SET 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // F5
    {"FD CB %02X F6: SET 6,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // F6
    {"FD CB %02X F7: LD A,SET 6,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // F7
    {"FD CB %02X F8: LD B,SET 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // F8
    {"FD CB %02X F9: LD C,SET 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // F9
    {"FD CB %02X FA: LD D,SET 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // FA
    {"FD CB %02X FB: LD E,SET 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // FB
    {"FD CB %02X FC: LD H,SET 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // FC
    {"FD CB %02X FD: LD L,SET 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // FD
    {"FD CB %02X FE: SET 7,(IY+%d)",      OpcodeInfo::ArgTypes::D,    23}, // FE
    {"FD CB %02X FF: LD A,SET 7,(IY+%d)", OpcodeInfo::ArgTypes::D,    23}, // FF
}};


}


#endif

