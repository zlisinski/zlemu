#ifndef ZLEMU_CORE_SMS_Z80OPCODES_H
#define ZLEMU_CORE_SMS_Z80OPCODES_H

#include <array>

#include "Zlemu.h"


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
};


inline constexpr std::array<OpcodeInfo, 256> OpcodeTable = {{
    {"00: NOP",                            OpcodeInfo::ArgTypes::None},     // 00
    {"01 %02X %02X: LD BC,%04X",           OpcodeInfo::ArgTypes::NN},       // 01
    {"02: LD (BC),A",                      OpcodeInfo::ArgTypes::None},     // 02
    {"03: INC BC",                         OpcodeInfo::ArgTypes::None},     // 03
    {"04: INC B",                          OpcodeInfo::ArgTypes::None},     // 04
    {"05: DEC B",                          OpcodeInfo::ArgTypes::None},     // 05
    {"06 %02X: LD B,%02X",                 OpcodeInfo::ArgTypes::N},        // 06
    {"07: RLCA",                           OpcodeInfo::ArgTypes::None},     // 07
    {"08: EX AF,AF'",                      OpcodeInfo::ArgTypes::None},     // 08
    {"09: ADD HL,BC",                      OpcodeInfo::ArgTypes::None},     // 09
    {"0A: LD A,(BC)",                      OpcodeInfo::ArgTypes::None},     // 0A
    {"0B: DEC BC",                         OpcodeInfo::ArgTypes::None},     // 0B
    {"0C: INC C",                          OpcodeInfo::ArgTypes::None},     // 0C
    {"0D: DEC C",                          OpcodeInfo::ArgTypes::None},     // 0D
    {"0E %02X: LD C,%02X",                 OpcodeInfo::ArgTypes::N},        // 0E
    {"0F: RRCA",                           OpcodeInfo::ArgTypes::None},     // 0F
    {"10 %02X: DJNZ %d",                   OpcodeInfo::ArgTypes::D},        // 10
    {"11 %02X %02X: LD DE,%04X",           OpcodeInfo::ArgTypes::NN},       // 11
    {"12: LD (DE),A",                      OpcodeInfo::ArgTypes::None},     // 12
    {"13: INC DE",                         OpcodeInfo::ArgTypes::None},     // 13
    {"14: INC D",                          OpcodeInfo::ArgTypes::None},     // 14
    {"15: DEC D",                          OpcodeInfo::ArgTypes::None},     // 15
    {"16 %02X: LD D,%02X",                 OpcodeInfo::ArgTypes::N},        // 16
    {"17: RLA",                            OpcodeInfo::ArgTypes::None},     // 17
    {"18 %02X: JR %d",                     OpcodeInfo::ArgTypes::D},        // 18
    {"19: ADD HL,DE",                      OpcodeInfo::ArgTypes::None},     // 19
    {"1A: LD A,(DE)",                      OpcodeInfo::ArgTypes::None},     // 1A
    {"1B: DEC DE",                         OpcodeInfo::ArgTypes::None},     // 1B
    {"1C: INC E",                          OpcodeInfo::ArgTypes::None},     // 1C
    {"1D: DEC E",                          OpcodeInfo::ArgTypes::None},     // 1D
    {"1E %02X: LD E,%02X",                 OpcodeInfo::ArgTypes::N},        // 1E
    {"1F: RRA",                            OpcodeInfo::ArgTypes::None},     // 1F
    {"20 %02X: JR NZ,%d",                  OpcodeInfo::ArgTypes::D},        // 20
    {"21 %02X %02X: LD HL,%04X",           OpcodeInfo::ArgTypes::NN},       // 21
    {"22 %02X %02X: LD (%04X),HL",         OpcodeInfo::ArgTypes::NN},       // 22
    {"23: INC HL",                         OpcodeInfo::ArgTypes::None},     // 23
    {"24: INC H",                          OpcodeInfo::ArgTypes::None},     // 24
    {"25: DEC H",                          OpcodeInfo::ArgTypes::None},     // 25
    {"26 %02X: LD H,%02X",                 OpcodeInfo::ArgTypes::N},        // 26
    {"27: DAA",                            OpcodeInfo::ArgTypes::None},     // 27
    {"28 %02X: JR Z,%d",                   OpcodeInfo::ArgTypes::D},        // 28
    {"29: ADD HL,HL",                      OpcodeInfo::ArgTypes::None},     // 29
    {"2A %02X %02X: LD HL,(%04X)",         OpcodeInfo::ArgTypes::NN},       // 2A
    {"2B: DEC HL",                         OpcodeInfo::ArgTypes::None},     // 2B
    {"2C: INC L",                          OpcodeInfo::ArgTypes::None},     // 2C
    {"2D: DEC L",                          OpcodeInfo::ArgTypes::None},     // 2D
    {"2E %02X: LD L,%02X",                 OpcodeInfo::ArgTypes::N},        // 2E
    {"2F: CPL",                            OpcodeInfo::ArgTypes::None},     // 2F
    {"30 %02X: JR NC,%d",                  OpcodeInfo::ArgTypes::D},        // 30
    {"31 %02X %02X: LD SP,%04X",           OpcodeInfo::ArgTypes::NN},       // 31
    {"32 %02X %02X: LD (%04X),A",          OpcodeInfo::ArgTypes::NN},       // 32
    {"33: INC SP",                         OpcodeInfo::ArgTypes::None},     // 33
    {"34: INC (HL)",                       OpcodeInfo::ArgTypes::None},     // 34
    {"35: DEC (HL)",                       OpcodeInfo::ArgTypes::None},     // 35
    {"36 %02X: LD (HL),%02X",              OpcodeInfo::ArgTypes::N},        // 36
    {"37: SCF",                            OpcodeInfo::ArgTypes::None},     // 37
    {"38 %02X: JR C,%d",                   OpcodeInfo::ArgTypes::D},        // 38
    {"39: ADD HL,SP",                      OpcodeInfo::ArgTypes::None},     // 39
    {"3A %02X %02X: LD A,(%04X)",          OpcodeInfo::ArgTypes::NN},       // 3A
    {"3B: DEC SP",                         OpcodeInfo::ArgTypes::None},     // 3B
    {"3C: INC A",                          OpcodeInfo::ArgTypes::None},     // 3C
    {"3D: DEC A",                          OpcodeInfo::ArgTypes::None},     // 3D
    {"3E %02X: LD A,%02X",                 OpcodeInfo::ArgTypes::N},        // 3E
    {"3F: CCF",                            OpcodeInfo::ArgTypes::None},     // 3F
    {"40: LD B,B",                         OpcodeInfo::ArgTypes::None},     // 40
    {"41: LD B,C",                         OpcodeInfo::ArgTypes::None},     // 41
    {"42: LD B,D",                         OpcodeInfo::ArgTypes::None},     // 42
    {"43: LD B,E",                         OpcodeInfo::ArgTypes::None},     // 43
    {"44: LD B,H",                         OpcodeInfo::ArgTypes::None},     // 44
    {"45: LD B,L",                         OpcodeInfo::ArgTypes::None},     // 45
    {"46: LD B,(HL)",                      OpcodeInfo::ArgTypes::None},     // 46
    {"47: LD B,A",                         OpcodeInfo::ArgTypes::None},     // 47
    {"48: LD C,B",                         OpcodeInfo::ArgTypes::None},     // 48
    {"49: LD C,C",                         OpcodeInfo::ArgTypes::None},     // 49
    {"4A: LD C,D",                         OpcodeInfo::ArgTypes::None},     // 4A
    {"4B: LD C,E",                         OpcodeInfo::ArgTypes::None},     // 4B
    {"4C: LD C,H",                         OpcodeInfo::ArgTypes::None},     // 4C
    {"4D: LD C,L",                         OpcodeInfo::ArgTypes::None},     // 4D
    {"4E: LD C,(HL)",                      OpcodeInfo::ArgTypes::None},     // 4E
    {"4F: LD C,A",                         OpcodeInfo::ArgTypes::None},     // 4F
    {"50: LD D,B",                         OpcodeInfo::ArgTypes::None},     // 50
    {"51: LD D,C",                         OpcodeInfo::ArgTypes::None},     // 51
    {"52: LD D,D",                         OpcodeInfo::ArgTypes::None},     // 52
    {"53: LD D,E",                         OpcodeInfo::ArgTypes::None},     // 53
    {"54: LD D,H",                         OpcodeInfo::ArgTypes::None},     // 54
    {"55: LD D,L",                         OpcodeInfo::ArgTypes::None},     // 55
    {"56: LD D,(HL)",                      OpcodeInfo::ArgTypes::None},     // 56
    {"57: LD D,A",                         OpcodeInfo::ArgTypes::None},     // 57
    {"58: LD E,B",                         OpcodeInfo::ArgTypes::None},     // 58
    {"59: LD E,C",                         OpcodeInfo::ArgTypes::None},     // 59
    {"5A: LD E,D",                         OpcodeInfo::ArgTypes::None},     // 5A
    {"5B: LD E,E",                         OpcodeInfo::ArgTypes::None},     // 5B
    {"5C: LD E,H",                         OpcodeInfo::ArgTypes::None},     // 5C
    {"5D: LD E,L",                         OpcodeInfo::ArgTypes::None},     // 5D
    {"5E: LD E,(HL)",                      OpcodeInfo::ArgTypes::None},     // 5E
    {"5F: LD E,A",                         OpcodeInfo::ArgTypes::None},     // 5F
    {"60: LD H,B",                         OpcodeInfo::ArgTypes::None},     // 60
    {"61: LD H,C",                         OpcodeInfo::ArgTypes::None},     // 61
    {"62: LD H,D",                         OpcodeInfo::ArgTypes::None},     // 62
    {"63: LD H,E",                         OpcodeInfo::ArgTypes::None},     // 63
    {"64: LD H,H",                         OpcodeInfo::ArgTypes::None},     // 64
    {"65: LD H,L",                         OpcodeInfo::ArgTypes::None},     // 65
    {"66: LD H,(HL)",                      OpcodeInfo::ArgTypes::None},     // 66
    {"67: LD H,A",                         OpcodeInfo::ArgTypes::None},     // 67
    {"68: LD L,B",                         OpcodeInfo::ArgTypes::None},     // 68
    {"69: LD L,C",                         OpcodeInfo::ArgTypes::None},     // 69
    {"6A: LD L,D",                         OpcodeInfo::ArgTypes::None},     // 6A
    {"6B: LD L,E",                         OpcodeInfo::ArgTypes::None},     // 6B
    {"6C: LD L,H",                         OpcodeInfo::ArgTypes::None},     // 6C
    {"6D: LD L,L",                         OpcodeInfo::ArgTypes::None},     // 6D
    {"6E: LD L,(HL)",                      OpcodeInfo::ArgTypes::None},     // 6E
    {"6F: LD L,A",                         OpcodeInfo::ArgTypes::None},     // 6F
    {"70: LD (HL),B",                      OpcodeInfo::ArgTypes::None},     // 70
    {"71: LD (HL),C",                      OpcodeInfo::ArgTypes::None},     // 71
    {"72: LD (HL),D",                      OpcodeInfo::ArgTypes::None},     // 72
    {"73: LD (HL),E",                      OpcodeInfo::ArgTypes::None},     // 73
    {"74: LD (HL),H",                      OpcodeInfo::ArgTypes::None},     // 74
    {"75: LD (HL),L",                      OpcodeInfo::ArgTypes::None},     // 75
    {"76: HALT",                           OpcodeInfo::ArgTypes::None},     // 76
    {"77: LD (HL),A",                      OpcodeInfo::ArgTypes::None},     // 77
    {"78: LD A,B",                         OpcodeInfo::ArgTypes::None},     // 78
    {"79: LD A,C",                         OpcodeInfo::ArgTypes::None},     // 79
    {"7A: LD A,D",                         OpcodeInfo::ArgTypes::None},     // 7A
    {"7B: LD A,E",                         OpcodeInfo::ArgTypes::None},     // 7B
    {"7C: LD A,H",                         OpcodeInfo::ArgTypes::None},     // 7C
    {"7D: LD A,L",                         OpcodeInfo::ArgTypes::None},     // 7D
    {"7E: LD A,(HL)",                      OpcodeInfo::ArgTypes::None},     // 7E
    {"7F: LD A,A",                         OpcodeInfo::ArgTypes::None},     // 7F
    {"80: ADD A,B",                        OpcodeInfo::ArgTypes::None},     // 80
    {"81: ADD A,C",                        OpcodeInfo::ArgTypes::None},     // 81
    {"82: ADD A,D",                        OpcodeInfo::ArgTypes::None},     // 82
    {"83: ADD A,E",                        OpcodeInfo::ArgTypes::None},     // 83
    {"84: ADD A,H",                        OpcodeInfo::ArgTypes::None},     // 84
    {"85: ADD A,L",                        OpcodeInfo::ArgTypes::None},     // 85
    {"86: ADD A,(HL)",                     OpcodeInfo::ArgTypes::None},     // 86
    {"87: ADD A,A",                        OpcodeInfo::ArgTypes::None},     // 87
    {"88: ADC A,B",                        OpcodeInfo::ArgTypes::None},     // 88
    {"89: ADC A,C",                        OpcodeInfo::ArgTypes::None},     // 89
    {"8A: ADC A,D",                        OpcodeInfo::ArgTypes::None},     // 8A
    {"8B: ADC A,E",                        OpcodeInfo::ArgTypes::None},     // 8B
    {"8C: ADC A,H",                        OpcodeInfo::ArgTypes::None},     // 8C
    {"8D: ADC A,L",                        OpcodeInfo::ArgTypes::None},     // 8D
    {"8E: ADC A,(HL)",                     OpcodeInfo::ArgTypes::None},     // 8E
    {"8F: ADC A,A",                        OpcodeInfo::ArgTypes::None},     // 8F
    {"90: SUB B",                          OpcodeInfo::ArgTypes::None},     // 90
    {"91: SUB C",                          OpcodeInfo::ArgTypes::None},     // 91
    {"92: SUB D",                          OpcodeInfo::ArgTypes::None},     // 92
    {"93: SUB E",                          OpcodeInfo::ArgTypes::None},     // 93
    {"94: SUB H",                          OpcodeInfo::ArgTypes::None},     // 94
    {"95: SUB L",                          OpcodeInfo::ArgTypes::None},     // 95
    {"96: SUB (HL)",                       OpcodeInfo::ArgTypes::None},     // 96
    {"97: SUB A",                          OpcodeInfo::ArgTypes::None},     // 97
    {"98: SBC A,B",                        OpcodeInfo::ArgTypes::None},     // 98
    {"99: SBC A,C",                        OpcodeInfo::ArgTypes::None},     // 99
    {"9A: SBC A,D",                        OpcodeInfo::ArgTypes::None},     // 9A
    {"9B: SBC A,E",                        OpcodeInfo::ArgTypes::None},     // 9B
    {"9C: SBC A,H",                        OpcodeInfo::ArgTypes::None},     // 9C
    {"9D: SBC A,L",                        OpcodeInfo::ArgTypes::None},     // 9D
    {"9E: SBC A,(HL)",                     OpcodeInfo::ArgTypes::None},     // 9E
    {"9F: SBC A,A",                        OpcodeInfo::ArgTypes::None},     // 9F
    {"A0: AND B",                          OpcodeInfo::ArgTypes::None},     // A0
    {"A1: AND C",                          OpcodeInfo::ArgTypes::None},     // A1
    {"A2: AND D",                          OpcodeInfo::ArgTypes::None},     // A2
    {"A3: AND E",                          OpcodeInfo::ArgTypes::None},     // A3
    {"A4: AND H",                          OpcodeInfo::ArgTypes::None},     // A4
    {"A5: AND L",                          OpcodeInfo::ArgTypes::None},     // A5
    {"A6: AND (HL)",                       OpcodeInfo::ArgTypes::None},     // A6
    {"A7: AND A",                          OpcodeInfo::ArgTypes::None},     // A7
    {"A8: XOR B",                          OpcodeInfo::ArgTypes::None},     // A8
    {"A9: XOR C",                          OpcodeInfo::ArgTypes::None},     // A9
    {"AA: XOR D",                          OpcodeInfo::ArgTypes::None},     // AA
    {"AB: XOR E",                          OpcodeInfo::ArgTypes::None},     // AB
    {"AC: XOR H",                          OpcodeInfo::ArgTypes::None},     // AC
    {"AD: XOR L",                          OpcodeInfo::ArgTypes::None},     // AD
    {"AE: XOR (HL)",                       OpcodeInfo::ArgTypes::None},     // AE
    {"AF: XOR A",                          OpcodeInfo::ArgTypes::None},     // AF
    {"B0: OR B",                           OpcodeInfo::ArgTypes::None},     // B0
    {"B1: OR C",                           OpcodeInfo::ArgTypes::None},     // B1
    {"B2: OR D",                           OpcodeInfo::ArgTypes::None},     // B2
    {"B3: OR E",                           OpcodeInfo::ArgTypes::None},     // B3
    {"B4: OR H",                           OpcodeInfo::ArgTypes::None},     // B4
    {"B5: OR L",                           OpcodeInfo::ArgTypes::None},     // B5
    {"B6: OR (HL)",                        OpcodeInfo::ArgTypes::None},     // B6
    {"B7: OR A",                           OpcodeInfo::ArgTypes::None},     // B7
    {"B8: CP B",                           OpcodeInfo::ArgTypes::None},     // B8
    {"B9: CP C",                           OpcodeInfo::ArgTypes::None},     // B9
    {"BA: CP D",                           OpcodeInfo::ArgTypes::None},     // BA
    {"BB: CP E",                           OpcodeInfo::ArgTypes::None},     // BB
    {"BC: CP H",                           OpcodeInfo::ArgTypes::None},     // BC
    {"BD: CP L",                           OpcodeInfo::ArgTypes::None},     // BD
    {"BE: CP (HL)",                        OpcodeInfo::ArgTypes::None},     // BE
    {"BF: CP A",                           OpcodeInfo::ArgTypes::None},     // BF
    {"C0: RET NZ",                         OpcodeInfo::ArgTypes::None},     // C0
    {"C1: POP BC",                         OpcodeInfo::ArgTypes::None},     // C1
    {"C2 %02X %02X: JP NZ,%04X",           OpcodeInfo::ArgTypes::NN},       // C2
    {"C3 %02X %02X: JP %04X",              OpcodeInfo::ArgTypes::NN},       // C3
    {"C4 %02X %02X: CALL NZ,%04X",         OpcodeInfo::ArgTypes::NN},       // C4
    {"C5: PUSH BC",                        OpcodeInfo::ArgTypes::None},     // C5
    {"C6 %02X: ADD A,%02X",                OpcodeInfo::ArgTypes::N},        // C6
    {"C7: RST 0",                          OpcodeInfo::ArgTypes::None},     // C7
    {"C8: RET Z",                          OpcodeInfo::ArgTypes::None},     // C8
    {"C9: RET",                            OpcodeInfo::ArgTypes::None},     // C9
    {"CA %02X %02X: JP Z,%04X",            OpcodeInfo::ArgTypes::NN},       // CA
    {"CB: [Prefix]",                       OpcodeInfo::ArgTypes::None},     // CB
    {"CC %02X %02X: CALL Z,%04X",          OpcodeInfo::ArgTypes::NN},       // CC
    {"CD %02X %02X: CALL %04X",            OpcodeInfo::ArgTypes::NN},       // CD
    {"CE %02X: ADC A,%02X",                OpcodeInfo::ArgTypes::N},        // CE
    {"CF: RST 8",                          OpcodeInfo::ArgTypes::None},     // CF
    {"D0: RET NC",                         OpcodeInfo::ArgTypes::None},     // D0
    {"D1: POP DE",                         OpcodeInfo::ArgTypes::None},     // D1
    {"D2 %02X %02X: JP NC,%04X",           OpcodeInfo::ArgTypes::NN},       // D2
    {"D3 %02X: OUT (%02X),A",              OpcodeInfo::ArgTypes::N},        // D3
    {"D4 %02X %02X: CALL NC,%04X",         OpcodeInfo::ArgTypes::NN},       // D4
    {"D5: PUSH DE",                        OpcodeInfo::ArgTypes::None},     // D5
    {"D6 %02X: SUB %02X",                  OpcodeInfo::ArgTypes::N},        // D6
    {"D7: RST 10H",                        OpcodeInfo::ArgTypes::None},     // D7
    {"D8: RET C",                          OpcodeInfo::ArgTypes::None},     // D8
    {"D9: EXX",                            OpcodeInfo::ArgTypes::None},     // D9
    {"DA %02X %02X: JP C,%04X",            OpcodeInfo::ArgTypes::NN},       // DA
    {"DB %02X: IN A,(%02X)",               OpcodeInfo::ArgTypes::N},        // DB
    {"DC %02X %02X: CALL C,%04X",          OpcodeInfo::ArgTypes::NN},       // DC
    {"DD: [IX Prefix]",                    OpcodeInfo::ArgTypes::None},     // DD
    {"DE %02X: SBC A,%02X",                OpcodeInfo::ArgTypes::N},        // DE
    {"DF: RST 18H",                        OpcodeInfo::ArgTypes::None},     // DF
    {"E0: RET PO",                         OpcodeInfo::ArgTypes::None},     // E0
    {"E1: POP HL",                         OpcodeInfo::ArgTypes::None},     // E1
    {"E2 %02X %02X: JP PO,%04X",           OpcodeInfo::ArgTypes::NN},       // E2
    {"E3: EX (SP),HL",                     OpcodeInfo::ArgTypes::None},     // E3
    {"E4 %02X %02X: CALL PO,%04X",         OpcodeInfo::ArgTypes::NN},       // E4
    {"E5: PUSH HL",                        OpcodeInfo::ArgTypes::None},     // E5
    {"E6 %02X: AND %02X",                  OpcodeInfo::ArgTypes::N},        // E6
    {"E7: RST 20H",                        OpcodeInfo::ArgTypes::None},     // E7
    {"E8: RET PE",                         OpcodeInfo::ArgTypes::None},     // E8
    {"E9: JP (HL)",                        OpcodeInfo::ArgTypes::None},     // E9
    {"EA %02X %02X: JP PE,%04X",           OpcodeInfo::ArgTypes::NN},       // EA
    {"EB: EX DE,HL",                       OpcodeInfo::ArgTypes::None},     // EB
    {"EC %02X %02X: CALL PE,%04X",         OpcodeInfo::ArgTypes::NN},       // EC
    {"ED: [Prefix]",                       OpcodeInfo::ArgTypes::None},     // ED
    {"EE %02X: XOR %02X",                  OpcodeInfo::ArgTypes::N},        // EE
    {"EF: RST 28H",                        OpcodeInfo::ArgTypes::None},     // EF
    {"F0: RET P",                          OpcodeInfo::ArgTypes::None},     // F0
    {"F1: POP AF",                         OpcodeInfo::ArgTypes::None},     // F1
    {"F2 %02X %02X: JP P,%04X",            OpcodeInfo::ArgTypes::NN},       // F2
    {"F3: DI",                             OpcodeInfo::ArgTypes::None},     // F3
    {"F4 %02X %02X: CALL P,%04X",          OpcodeInfo::ArgTypes::NN},       // F4
    {"F5: PUSH AF",                        OpcodeInfo::ArgTypes::None},     // F5
    {"F6 %02X: OR %02X",                   OpcodeInfo::ArgTypes::N},        // F6
    {"F7: RST 30H",                        OpcodeInfo::ArgTypes::None},     // F7
    {"F8: RET M",                          OpcodeInfo::ArgTypes::None},     // F8
    {"F9: LD SP,HL",                       OpcodeInfo::ArgTypes::None},     // F9
    {"FA %02X %02X: JP M,%04X",            OpcodeInfo::ArgTypes::NN},       // FA
    {"FB: EI",                             OpcodeInfo::ArgTypes::None},     // FB
    {"FC %02X %02X: CALL M,%04X",          OpcodeInfo::ArgTypes::NN},       // FC
    {"FD: [IY Prefix]",                    OpcodeInfo::ArgTypes::None},     // FD
    {"FE %02X: CP %02X",                   OpcodeInfo::ArgTypes::N},        // FE
    {"FF: RST 38H",                        OpcodeInfo::ArgTypes::None},     // FF
}};

inline constexpr std::array<OpcodeInfo, 256> OpcodeTableCB = {{
    {"CB 00: RLC B",                       OpcodeInfo::ArgTypes::None},     // 00
    {"CB 01: RLC C",                       OpcodeInfo::ArgTypes::None},     // 01
    {"CB 02: RLC D",                       OpcodeInfo::ArgTypes::None},     // 02
    {"CB 03: RLC E",                       OpcodeInfo::ArgTypes::None},     // 03
    {"CB 04: RLC H",                       OpcodeInfo::ArgTypes::None},     // 04
    {"CB 05: RLC L",                       OpcodeInfo::ArgTypes::None},     // 05
    {"CB 06: RLC (HL)",                    OpcodeInfo::ArgTypes::None},     // 06
    {"CB 07: RLC A",                       OpcodeInfo::ArgTypes::None},     // 07
    {"CB 08: RRC B",                       OpcodeInfo::ArgTypes::None},     // 08
    {"CB 09: RRC C",                       OpcodeInfo::ArgTypes::None},     // 09
    {"CB 0A: RRC D",                       OpcodeInfo::ArgTypes::None},     // 0A
    {"CB 0B: RRC E",                       OpcodeInfo::ArgTypes::None},     // 0B
    {"CB 0C: RRC H",                       OpcodeInfo::ArgTypes::None},     // 0C
    {"CB 0D: RRC L",                       OpcodeInfo::ArgTypes::None},     // 0D
    {"CB 0E: RRC (HL)",                    OpcodeInfo::ArgTypes::None},     // 0E
    {"CB 0F: RRC A",                       OpcodeInfo::ArgTypes::None},     // 0F
    {"CB 10: RL B",                        OpcodeInfo::ArgTypes::None},     // 10
    {"CB 11: RL C",                        OpcodeInfo::ArgTypes::None},     // 11
    {"CB 12: RL D",                        OpcodeInfo::ArgTypes::None},     // 12
    {"CB 13: RL E",                        OpcodeInfo::ArgTypes::None},     // 13
    {"CB 14: RL H",                        OpcodeInfo::ArgTypes::None},     // 14
    {"CB 15: RL L",                        OpcodeInfo::ArgTypes::None},     // 15
    {"CB 16: RL (HL)",                     OpcodeInfo::ArgTypes::None},     // 16
    {"CB 17: RL A",                        OpcodeInfo::ArgTypes::None},     // 17
    {"CB 18: RR B",                        OpcodeInfo::ArgTypes::None},     // 18
    {"CB 19: RR C",                        OpcodeInfo::ArgTypes::None},     // 19
    {"CB 1A: RR D",                        OpcodeInfo::ArgTypes::None},     // 1A
    {"CB 1B: RR E",                        OpcodeInfo::ArgTypes::None},     // 1B
    {"CB 1C: RR H",                        OpcodeInfo::ArgTypes::None},     // 1C
    {"CB 1D: RR L",                        OpcodeInfo::ArgTypes::None},     // 1D
    {"CB 1E: RR (HL)",                     OpcodeInfo::ArgTypes::None},     // 1E
    {"CB 1F: RR A",                        OpcodeInfo::ArgTypes::None},     // 1F
    {"CB 20: SLA B",                       OpcodeInfo::ArgTypes::None},     // 20
    {"CB 21: SLA C",                       OpcodeInfo::ArgTypes::None},     // 21
    {"CB 22: SLA D",                       OpcodeInfo::ArgTypes::None},     // 22
    {"CB 23: SLA E",                       OpcodeInfo::ArgTypes::None},     // 23
    {"CB 24: SLA H",                       OpcodeInfo::ArgTypes::None},     // 24
    {"CB 25: SLA L",                       OpcodeInfo::ArgTypes::None},     // 25
    {"CB 26: SLA (HL)",                    OpcodeInfo::ArgTypes::None},     // 26
    {"CB 27: SLA A",                       OpcodeInfo::ArgTypes::None},     // 27
    {"CB 28: SRA B",                       OpcodeInfo::ArgTypes::None},     // 28
    {"CB 29: SRA C",                       OpcodeInfo::ArgTypes::None},     // 29
    {"CB 2A: SRA D",                       OpcodeInfo::ArgTypes::None},     // 2A
    {"CB 2B: SRA E",                       OpcodeInfo::ArgTypes::None},     // 2B
    {"CB 2C: SRA H",                       OpcodeInfo::ArgTypes::None},     // 2C
    {"CB 2D: SRA L",                       OpcodeInfo::ArgTypes::None},     // 2D
    {"CB 2E: SRA (HL)",                    OpcodeInfo::ArgTypes::None},     // 2E
    {"CB 2F: SRA A",                       OpcodeInfo::ArgTypes::None},     // 2F
    {"CB 30: SLL B",                       OpcodeInfo::ArgTypes::None},     // 30
    {"CB 31: SLL C",                       OpcodeInfo::ArgTypes::None},     // 31
    {"CB 32: SLL D",                       OpcodeInfo::ArgTypes::None},     // 32
    {"CB 33: SLL E",                       OpcodeInfo::ArgTypes::None},     // 33
    {"CB 34: SLL H",                       OpcodeInfo::ArgTypes::None},     // 34
    {"CB 35: SLL L",                       OpcodeInfo::ArgTypes::None},     // 35
    {"CB 36: SLL (HL)",                    OpcodeInfo::ArgTypes::None},     // 36
    {"CB 37: SLL A",                       OpcodeInfo::ArgTypes::None},     // 37
    {"CB 38: SRL B",                       OpcodeInfo::ArgTypes::None},     // 38
    {"CB 39: SRL C",                       OpcodeInfo::ArgTypes::None},     // 39
    {"CB 3A: SRL D",                       OpcodeInfo::ArgTypes::None},     // 3A
    {"CB 3B: SRL E",                       OpcodeInfo::ArgTypes::None},     // 3B
    {"CB 3C: SRL H",                       OpcodeInfo::ArgTypes::None},     // 3C
    {"CB 3D: SRL L",                       OpcodeInfo::ArgTypes::None},     // 3D
    {"CB 3E: SRL (HL)",                    OpcodeInfo::ArgTypes::None},     // 3E
    {"CB 3F: SRL A",                       OpcodeInfo::ArgTypes::None},     // 3F
    {"CB 40: BIT 0,B",                     OpcodeInfo::ArgTypes::None},     // 40
    {"CB 41: BIT 0,C",                     OpcodeInfo::ArgTypes::None},     // 41
    {"CB 42: BIT 0,D",                     OpcodeInfo::ArgTypes::None},     // 42
    {"CB 43: BIT 0,E",                     OpcodeInfo::ArgTypes::None},     // 43
    {"CB 44: BIT 0,H",                     OpcodeInfo::ArgTypes::None},     // 44
    {"CB 45: BIT 0,L",                     OpcodeInfo::ArgTypes::None},     // 45
    {"CB 46: BIT 0,(HL)",                  OpcodeInfo::ArgTypes::None},     // 46
    {"CB 47: BIT 0,A",                     OpcodeInfo::ArgTypes::None},     // 47
    {"CB 48: BIT 1,B",                     OpcodeInfo::ArgTypes::None},     // 48
    {"CB 49: BIT 1,C",                     OpcodeInfo::ArgTypes::None},     // 49
    {"CB 4A: BIT 1,D",                     OpcodeInfo::ArgTypes::None},     // 4A
    {"CB 4B: BIT 1,E",                     OpcodeInfo::ArgTypes::None},     // 4B
    {"CB 4C: BIT 1,H",                     OpcodeInfo::ArgTypes::None},     // 4C
    {"CB 4D: BIT 1,L",                     OpcodeInfo::ArgTypes::None},     // 4D
    {"CB 4E: BIT 1,(HL)",                  OpcodeInfo::ArgTypes::None},     // 4E
    {"CB 4F: BIT 1,A",                     OpcodeInfo::ArgTypes::None},     // 4F
    {"CB 50: BIT 2,B",                     OpcodeInfo::ArgTypes::None},     // 50
    {"CB 51: BIT 2,C",                     OpcodeInfo::ArgTypes::None},     // 51
    {"CB 52: BIT 2,D",                     OpcodeInfo::ArgTypes::None},     // 52
    {"CB 53: BIT 2,E",                     OpcodeInfo::ArgTypes::None},     // 53
    {"CB 54: BIT 2,H",                     OpcodeInfo::ArgTypes::None},     // 54
    {"CB 55: BIT 2,L",                     OpcodeInfo::ArgTypes::None},     // 55
    {"CB 56: BIT 2,(HL)",                  OpcodeInfo::ArgTypes::None},     // 56
    {"CB 57: BIT 2,A",                     OpcodeInfo::ArgTypes::None},     // 57
    {"CB 58: BIT 3,B",                     OpcodeInfo::ArgTypes::None},     // 58
    {"CB 59: BIT 3,C",                     OpcodeInfo::ArgTypes::None},     // 59
    {"CB 5A: BIT 3,D",                     OpcodeInfo::ArgTypes::None},     // 5A
    {"CB 5B: BIT 3,E",                     OpcodeInfo::ArgTypes::None},     // 5B
    {"CB 5C: BIT 3,H",                     OpcodeInfo::ArgTypes::None},     // 5C
    {"CB 5D: BIT 3,L",                     OpcodeInfo::ArgTypes::None},     // 5D
    {"CB 5E: BIT 3,(HL)",                  OpcodeInfo::ArgTypes::None},     // 5E
    {"CB 5F: BIT 3,A",                     OpcodeInfo::ArgTypes::None},     // 5F
    {"CB 60: BIT 4,B",                     OpcodeInfo::ArgTypes::None},     // 60
    {"CB 61: BIT 4,C",                     OpcodeInfo::ArgTypes::None},     // 61
    {"CB 62: BIT 4,D",                     OpcodeInfo::ArgTypes::None},     // 62
    {"CB 63: BIT 4,E",                     OpcodeInfo::ArgTypes::None},     // 63
    {"CB 64: BIT 4,H",                     OpcodeInfo::ArgTypes::None},     // 64
    {"CB 65: BIT 4,L",                     OpcodeInfo::ArgTypes::None},     // 65
    {"CB 66: BIT 4,(HL)",                  OpcodeInfo::ArgTypes::None},     // 66
    {"CB 67: BIT 4,A",                     OpcodeInfo::ArgTypes::None},     // 67
    {"CB 68: BIT 5,B",                     OpcodeInfo::ArgTypes::None},     // 68
    {"CB 69: BIT 5,C",                     OpcodeInfo::ArgTypes::None},     // 69
    {"CB 6A: BIT 5,D",                     OpcodeInfo::ArgTypes::None},     // 6A
    {"CB 6B: BIT 5,E",                     OpcodeInfo::ArgTypes::None},     // 6B
    {"CB 6C: BIT 5,H",                     OpcodeInfo::ArgTypes::None},     // 6C
    {"CB 6D: BIT 5,L",                     OpcodeInfo::ArgTypes::None},     // 6D
    {"CB 6E: BIT 5,(HL)",                  OpcodeInfo::ArgTypes::None},     // 6E
    {"CB 6F: BIT 5,A",                     OpcodeInfo::ArgTypes::None},     // 6F
    {"CB 70: BIT 6,B",                     OpcodeInfo::ArgTypes::None},     // 70
    {"CB 71: BIT 6,C",                     OpcodeInfo::ArgTypes::None},     // 71
    {"CB 72: BIT 6,D",                     OpcodeInfo::ArgTypes::None},     // 72
    {"CB 73: BIT 6,E",                     OpcodeInfo::ArgTypes::None},     // 73
    {"CB 74: BIT 6,H",                     OpcodeInfo::ArgTypes::None},     // 74
    {"CB 75: BIT 6,L",                     OpcodeInfo::ArgTypes::None},     // 75
    {"CB 76: BIT 6,(HL)",                  OpcodeInfo::ArgTypes::None},     // 76
    {"CB 77: BIT 6,A",                     OpcodeInfo::ArgTypes::None},     // 77
    {"CB 78: BIT 7,B",                     OpcodeInfo::ArgTypes::None},     // 78
    {"CB 79: BIT 7,C",                     OpcodeInfo::ArgTypes::None},     // 79
    {"CB 7A: BIT 7,D",                     OpcodeInfo::ArgTypes::None},     // 7A
    {"CB 7B: BIT 7,E",                     OpcodeInfo::ArgTypes::None},     // 7B
    {"CB 7C: BIT 7,H",                     OpcodeInfo::ArgTypes::None},     // 7C
    {"CB 7D: BIT 7,L",                     OpcodeInfo::ArgTypes::None},     // 7D
    {"CB 7E: BIT 7,(HL)",                  OpcodeInfo::ArgTypes::None},     // 7E
    {"CB 7F: BIT 7,A",                     OpcodeInfo::ArgTypes::None},     // 7F
    {"CB 80: RES 0,B",                     OpcodeInfo::ArgTypes::None},     // 80
    {"CB 81: RES 0,C",                     OpcodeInfo::ArgTypes::None},     // 81
    {"CB 82: RES 0,D",                     OpcodeInfo::ArgTypes::None},     // 82
    {"CB 83: RES 0,E",                     OpcodeInfo::ArgTypes::None},     // 83
    {"CB 84: RES 0,H",                     OpcodeInfo::ArgTypes::None},     // 84
    {"CB 85: RES 0,L",                     OpcodeInfo::ArgTypes::None},     // 85
    {"CB 86: RES 0,(HL)",                  OpcodeInfo::ArgTypes::None},     // 86
    {"CB 87: RES 0,A",                     OpcodeInfo::ArgTypes::None},     // 87
    {"CB 88: RES 1,B",                     OpcodeInfo::ArgTypes::None},     // 88
    {"CB 89: RES 1,C",                     OpcodeInfo::ArgTypes::None},     // 89
    {"CB 8A: RES 1,D",                     OpcodeInfo::ArgTypes::None},     // 8A
    {"CB 8B: RES 1,E",                     OpcodeInfo::ArgTypes::None},     // 8B
    {"CB 8C: RES 1,H",                     OpcodeInfo::ArgTypes::None},     // 8C
    {"CB 8D: RES 1,L",                     OpcodeInfo::ArgTypes::None},     // 8D
    {"CB 8E: RES 1,(HL)",                  OpcodeInfo::ArgTypes::None},     // 8E
    {"CB 8F: RES 1,A",                     OpcodeInfo::ArgTypes::None},     // 8F
    {"CB 90: RES 2,B",                     OpcodeInfo::ArgTypes::None},     // 90
    {"CB 91: RES 2,C",                     OpcodeInfo::ArgTypes::None},     // 91
    {"CB 92: RES 2,D",                     OpcodeInfo::ArgTypes::None},     // 92
    {"CB 93: RES 2,E",                     OpcodeInfo::ArgTypes::None},     // 93
    {"CB 94: RES 2,H",                     OpcodeInfo::ArgTypes::None},     // 94
    {"CB 95: RES 2,L",                     OpcodeInfo::ArgTypes::None},     // 95
    {"CB 96: RES 2,(HL)",                  OpcodeInfo::ArgTypes::None},     // 96
    {"CB 97: RES 2,A",                     OpcodeInfo::ArgTypes::None},     // 97
    {"CB 98: RES 3,B",                     OpcodeInfo::ArgTypes::None},     // 98
    {"CB 99: RES 3,C",                     OpcodeInfo::ArgTypes::None},     // 99
    {"CB 9A: RES 3,D",                     OpcodeInfo::ArgTypes::None},     // 9A
    {"CB 9B: RES 3,E",                     OpcodeInfo::ArgTypes::None},     // 9B
    {"CB 9C: RES 3,H",                     OpcodeInfo::ArgTypes::None},     // 9C
    {"CB 9D: RES 3,L",                     OpcodeInfo::ArgTypes::None},     // 9D
    {"CB 9E: RES 3,(HL)",                  OpcodeInfo::ArgTypes::None},     // 9E
    {"CB 9F: RES 3,A",                     OpcodeInfo::ArgTypes::None},     // 9F
    {"CB A0: RES 4,B",                     OpcodeInfo::ArgTypes::None},     // A0
    {"CB A1: RES 4,C",                     OpcodeInfo::ArgTypes::None},     // A1
    {"CB A2: RES 4,D",                     OpcodeInfo::ArgTypes::None},     // A2
    {"CB A3: RES 4,E",                     OpcodeInfo::ArgTypes::None},     // A3
    {"CB A4: RES 4,H",                     OpcodeInfo::ArgTypes::None},     // A4
    {"CB A5: RES 4,L",                     OpcodeInfo::ArgTypes::None},     // A5
    {"CB A6: RES 4,(HL)",                  OpcodeInfo::ArgTypes::None},     // A6
    {"CB A7: RES 4,A",                     OpcodeInfo::ArgTypes::None},     // A7
    {"CB A8: RES 5,B",                     OpcodeInfo::ArgTypes::None},     // A8
    {"CB A9: RES 5,C",                     OpcodeInfo::ArgTypes::None},     // A9
    {"CB AA: RES 5,D",                     OpcodeInfo::ArgTypes::None},     // AA
    {"CB AB: RES 5,E",                     OpcodeInfo::ArgTypes::None},     // AB
    {"CB AC: RES 5,H",                     OpcodeInfo::ArgTypes::None},     // AC
    {"CB AD: RES 5,L",                     OpcodeInfo::ArgTypes::None},     // AD
    {"CB AE: RES 5,(HL)",                  OpcodeInfo::ArgTypes::None},     // AE
    {"CB AF: RES 5,A",                     OpcodeInfo::ArgTypes::None},     // AF
    {"CB B0: RES 6,B",                     OpcodeInfo::ArgTypes::None},     // B0
    {"CB B1: RES 6,C",                     OpcodeInfo::ArgTypes::None},     // B1
    {"CB B2: RES 6,D",                     OpcodeInfo::ArgTypes::None},     // B2
    {"CB B3: RES 6,E",                     OpcodeInfo::ArgTypes::None},     // B3
    {"CB B4: RES 6,H",                     OpcodeInfo::ArgTypes::None},     // B4
    {"CB B5: RES 6,L",                     OpcodeInfo::ArgTypes::None},     // B5
    {"CB B6: RES 6,(HL)",                  OpcodeInfo::ArgTypes::None},     // B6
    {"CB B7: RES 6,A",                     OpcodeInfo::ArgTypes::None},     // B7
    {"CB B8: RES 7,B",                     OpcodeInfo::ArgTypes::None},     // B8
    {"CB B9: RES 7,C",                     OpcodeInfo::ArgTypes::None},     // B9
    {"CB BA: RES 7,D",                     OpcodeInfo::ArgTypes::None},     // BA
    {"CB BB: RES 7,E",                     OpcodeInfo::ArgTypes::None},     // BB
    {"CB BC: RES 7,H",                     OpcodeInfo::ArgTypes::None},     // BC
    {"CB BD: RES 7,L",                     OpcodeInfo::ArgTypes::None},     // BD
    {"CB BE: RES 7,(HL)",                  OpcodeInfo::ArgTypes::None},     // BE
    {"CB BF: RES 7,A",                     OpcodeInfo::ArgTypes::None},     // BF
    {"CB C0: SET 0,B",                     OpcodeInfo::ArgTypes::None},     // C0
    {"CB C1: SET 0,C",                     OpcodeInfo::ArgTypes::None},     // C1
    {"CB C2: SET 0,D",                     OpcodeInfo::ArgTypes::None},     // C2
    {"CB C3: SET 0,E",                     OpcodeInfo::ArgTypes::None},     // C3
    {"CB C4: SET 0,H",                     OpcodeInfo::ArgTypes::None},     // C4
    {"CB C5: SET 0,L",                     OpcodeInfo::ArgTypes::None},     // C5
    {"CB C6: SET 0,(HL)",                  OpcodeInfo::ArgTypes::None},     // C6
    {"CB C7: SET 0,A",                     OpcodeInfo::ArgTypes::None},     // C7
    {"CB C8: SET 1,B",                     OpcodeInfo::ArgTypes::None},     // C8
    {"CB C9: SET 1,C",                     OpcodeInfo::ArgTypes::None},     // C9
    {"CB CA: SET 1,D",                     OpcodeInfo::ArgTypes::None},     // CA
    {"CB CB: SET 1,E",                     OpcodeInfo::ArgTypes::None},     // CB
    {"CB CC: SET 1,H",                     OpcodeInfo::ArgTypes::None},     // CC
    {"CB CD: SET 1,L",                     OpcodeInfo::ArgTypes::None},     // CD
    {"CB CE: SET 1,(HL)",                  OpcodeInfo::ArgTypes::None},     // CE
    {"CB CF: SET 1,A",                     OpcodeInfo::ArgTypes::None},     // CF
    {"CB D0: SET 2,B",                     OpcodeInfo::ArgTypes::None},     // D0
    {"CB D1: SET 2,C",                     OpcodeInfo::ArgTypes::None},     // D1
    {"CB D2: SET 2,D",                     OpcodeInfo::ArgTypes::None},     // D2
    {"CB D3: SET 2,E",                     OpcodeInfo::ArgTypes::None},     // D3
    {"CB D4: SET 2,H",                     OpcodeInfo::ArgTypes::None},     // D4
    {"CB D5: SET 2,L",                     OpcodeInfo::ArgTypes::None},     // D5
    {"CB D6: SET 2,(HL)",                  OpcodeInfo::ArgTypes::None},     // D6
    {"CB D7: SET 2,A",                     OpcodeInfo::ArgTypes::None},     // D7
    {"CB D8: SET 3,B",                     OpcodeInfo::ArgTypes::None},     // D8
    {"CB D9: SET 3,C",                     OpcodeInfo::ArgTypes::None},     // D9
    {"CB DA: SET 3,D",                     OpcodeInfo::ArgTypes::None},     // DA
    {"CB DB: SET 3,E",                     OpcodeInfo::ArgTypes::None},     // DB
    {"CB DC: SET 3,H",                     OpcodeInfo::ArgTypes::None},     // DC
    {"CB DD: SET 3,L",                     OpcodeInfo::ArgTypes::None},     // DD
    {"CB DE: SET 3,(HL)",                  OpcodeInfo::ArgTypes::None},     // DE
    {"CB DF: SET 3,A",                     OpcodeInfo::ArgTypes::None},     // DF
    {"CB E0: SET 4,B",                     OpcodeInfo::ArgTypes::None},     // E0
    {"CB E1: SET 4,C",                     OpcodeInfo::ArgTypes::None},     // E1
    {"CB E2: SET 4,D",                     OpcodeInfo::ArgTypes::None},     // E2
    {"CB E3: SET 4,E",                     OpcodeInfo::ArgTypes::None},     // E3
    {"CB E4: SET 4,H",                     OpcodeInfo::ArgTypes::None},     // E4
    {"CB E5: SET 4,L",                     OpcodeInfo::ArgTypes::None},     // E5
    {"CB E6: SET 4,(HL)",                  OpcodeInfo::ArgTypes::None},     // E6
    {"CB E7: SET 4,A",                     OpcodeInfo::ArgTypes::None},     // E7
    {"CB E8: SET 5,B",                     OpcodeInfo::ArgTypes::None},     // E8
    {"CB E9: SET 5,C",                     OpcodeInfo::ArgTypes::None},     // E9
    {"CB EA: SET 5,D",                     OpcodeInfo::ArgTypes::None},     // EA
    {"CB EB: SET 5,E",                     OpcodeInfo::ArgTypes::None},     // EB
    {"CB EC: SET 5,H",                     OpcodeInfo::ArgTypes::None},     // EC
    {"CB ED: SET 5,L",                     OpcodeInfo::ArgTypes::None},     // ED
    {"CB EE: SET 5,(HL)",                  OpcodeInfo::ArgTypes::None},     // EE
    {"CB EF: SET 5,A",                     OpcodeInfo::ArgTypes::None},     // EF
    {"CB F0: SET 6,B",                     OpcodeInfo::ArgTypes::None},     // F0
    {"CB F1: SET 6,C",                     OpcodeInfo::ArgTypes::None},     // F1
    {"CB F2: SET 6,D",                     OpcodeInfo::ArgTypes::None},     // F2
    {"CB F3: SET 6,E",                     OpcodeInfo::ArgTypes::None},     // F3
    {"CB F4: SET 6,H",                     OpcodeInfo::ArgTypes::None},     // F4
    {"CB F5: SET 6,L",                     OpcodeInfo::ArgTypes::None},     // F5
    {"CB F6: SET 6,(HL)",                  OpcodeInfo::ArgTypes::None},     // F6
    {"CB F7: SET 6,A",                     OpcodeInfo::ArgTypes::None},     // F7
    {"CB F8: SET 7,B",                     OpcodeInfo::ArgTypes::None},     // F8
    {"CB F9: SET 7,C",                     OpcodeInfo::ArgTypes::None},     // F9
    {"CB FA: SET 7,D",                     OpcodeInfo::ArgTypes::None},     // FA
    {"CB FB: SET 7,E",                     OpcodeInfo::ArgTypes::None},     // FB
    {"CB FC: SET 7,H",                     OpcodeInfo::ArgTypes::None},     // FC
    {"CB FD: SET 7,L",                     OpcodeInfo::ArgTypes::None},     // FD
    {"CB FE: SET 7,(HL)",                  OpcodeInfo::ArgTypes::None},     // FE
    {"CB FF: SET 7,A",                     OpcodeInfo::ArgTypes::None},     // FF
}};

inline constexpr std::array<OpcodeInfo, 256> OpcodeTableDD = {{
    {"DD 00: NOP",                         OpcodeInfo::ArgTypes::None},     // 00
    {"DD 01 %02X %02X: LD BC,%04X",        OpcodeInfo::ArgTypes::NN},       // 01
    {"DD 02: LD (BC),A",                   OpcodeInfo::ArgTypes::None},     // 02
    {"DD 03: INC BC",                      OpcodeInfo::ArgTypes::None},     // 03
    {"DD 04: INC B",                       OpcodeInfo::ArgTypes::None},     // 04
    {"DD 05: DEC B",                       OpcodeInfo::ArgTypes::None},     // 05
    {"DD 06 %02X: LD B,%02X",              OpcodeInfo::ArgTypes::N},        // 06
    {"DD 07: RLCA",                        OpcodeInfo::ArgTypes::None},     // 07
    {"DD 08: EX AF,AF'",                   OpcodeInfo::ArgTypes::None},     // 08
    {"DD 09: ADD IX,BC",                   OpcodeInfo::ArgTypes::None},     // 09
    {"DD 0A: LD A,(BC)",                   OpcodeInfo::ArgTypes::None},     // 0A
    {"DD 0B: DEC BC",                      OpcodeInfo::ArgTypes::None},     // 0B
    {"DD 0C: INC C",                       OpcodeInfo::ArgTypes::None},     // 0C
    {"DD 0D: DEC C",                       OpcodeInfo::ArgTypes::None},     // 0D
    {"DD 0E %02X: LD C,%02X",              OpcodeInfo::ArgTypes::N},        // 0E
    {"DD 0F: RRCA",                        OpcodeInfo::ArgTypes::None},     // 0F
    {"DD 10 %02X: DJNZ %d",                OpcodeInfo::ArgTypes::D},        // 10
    {"DD 11 %02X %02X: LD DE,%04X",        OpcodeInfo::ArgTypes::NN},       // 11
    {"DD 12: LD (DE),A",                   OpcodeInfo::ArgTypes::None},     // 12
    {"DD 13: INC DE",                      OpcodeInfo::ArgTypes::None},     // 13
    {"DD 14: INC D",                       OpcodeInfo::ArgTypes::None},     // 14
    {"DD 15: DEC D",                       OpcodeInfo::ArgTypes::None},     // 15
    {"DD 16 %02X: LD D,%02X",              OpcodeInfo::ArgTypes::N},        // 16
    {"DD 17: RLA",                         OpcodeInfo::ArgTypes::None},     // 17
    {"DD 18 %02X: JR %d",                  OpcodeInfo::ArgTypes::D},        // 18
    {"DD 19: ADD IX,DE",                   OpcodeInfo::ArgTypes::None},     // 19
    {"DD 1A: LD A,(DE)",                   OpcodeInfo::ArgTypes::None},     // 1A
    {"DD 1B: DEC DE",                      OpcodeInfo::ArgTypes::None},     // 1B
    {"DD 1C: INC E",                       OpcodeInfo::ArgTypes::None},     // 1C
    {"DD 1D: DEC E",                       OpcodeInfo::ArgTypes::None},     // 1D
    {"DD 1E %02X: LD E,%02X",              OpcodeInfo::ArgTypes::N},        // 1E
    {"DD 1F: RRA",                         OpcodeInfo::ArgTypes::None},     // 1F
    {"DD 20 %02X: JR NZ,%d",               OpcodeInfo::ArgTypes::D},        // 20
    {"DD 21 %02X %02X: LD IX,%04X",        OpcodeInfo::ArgTypes::NN},       // 21
    {"DD 22 %02X %02X: LD (%04X),IX",      OpcodeInfo::ArgTypes::NN},       // 22
    {"DD 23: INC IX",                      OpcodeInfo::ArgTypes::None},     // 23
    {"DD 24: INC IXh",                     OpcodeInfo::ArgTypes::None},     // 24
    {"DD 25: DEC IXh",                     OpcodeInfo::ArgTypes::None},     // 25
    {"DD 26 %02X: LD IXh,%02X",            OpcodeInfo::ArgTypes::N},        // 26
    {"DD 27: DAA",                         OpcodeInfo::ArgTypes::None},     // 27
    {"DD 28 %02X: JR Z,%d",                OpcodeInfo::ArgTypes::D},        // 28
    {"DD 29: ADD IX,IX",                   OpcodeInfo::ArgTypes::None},     // 29
    {"DD 2A %02X %02X: LD IX,(%04X)",      OpcodeInfo::ArgTypes::NN},       // 2A
    {"DD 2B: DEC IX",                      OpcodeInfo::ArgTypes::None},     // 2B
    {"DD 2C: INC IXl",                     OpcodeInfo::ArgTypes::None},     // 2C
    {"DD 2D: DEC IXl",                     OpcodeInfo::ArgTypes::None},     // 2D
    {"DD 2E %02X: LD IXl,%02X",            OpcodeInfo::ArgTypes::N},        // 2E
    {"DD 2F: CPL",                         OpcodeInfo::ArgTypes::None},     // 2F
    {"DD 30 %02X: JR NC,%d",               OpcodeInfo::ArgTypes::D},        // 30
    {"DD 31 %02X %02X: LD SP,%04X",        OpcodeInfo::ArgTypes::NN},       // 31
    {"DD 32 %02X %02X: LD (%04X),A",       OpcodeInfo::ArgTypes::NN},       // 32
    {"DD 33: INC SP",                      OpcodeInfo::ArgTypes::None},     // 33
    {"DD 34 %02X: INC (IX+%d)",            OpcodeInfo::ArgTypes::D},        // 34
    {"DD 35 %02X: DEC (IX+%d)",            OpcodeInfo::ArgTypes::D},        // 35
    {"DD 36 %02X %02X: LD (IX+%d),%02X",   OpcodeInfo::ArgTypes::DN},       // 36
    {"DD 37: SCF",                         OpcodeInfo::ArgTypes::None},     // 37
    {"DD 38 %02X: JR C,%d",                OpcodeInfo::ArgTypes::D},        // 38
    {"DD 39: ADD IX,SP",                   OpcodeInfo::ArgTypes::None},     // 39
    {"DD 3A %02X %02X: LD A,(%04X)",       OpcodeInfo::ArgTypes::NN},       // 3A
    {"DD 3B: DEC SP",                      OpcodeInfo::ArgTypes::None},     // 3B
    {"DD 3C: INC A",                       OpcodeInfo::ArgTypes::None},     // 3C
    {"DD 3D: DEC A",                       OpcodeInfo::ArgTypes::None},     // 3D
    {"DD 3E %02X: LD A,%02X",              OpcodeInfo::ArgTypes::N},        // 3E
    {"DD 3F: CCF",                         OpcodeInfo::ArgTypes::None},     // 3F
    {"DD 40: LD B,B",                      OpcodeInfo::ArgTypes::None},     // 40
    {"DD 41: LD B,C",                      OpcodeInfo::ArgTypes::None},     // 41
    {"DD 42: LD B,D",                      OpcodeInfo::ArgTypes::None},     // 42
    {"DD 43: LD B,E",                      OpcodeInfo::ArgTypes::None},     // 43
    {"DD 44: LD B,IXh",                    OpcodeInfo::ArgTypes::None},     // 44
    {"DD 45: LD B,IXl",                    OpcodeInfo::ArgTypes::None},     // 45
    {"DD 46 %02X: LD B,(IX+%d)",           OpcodeInfo::ArgTypes::D},        // 46
    {"DD 47: LD B,A",                      OpcodeInfo::ArgTypes::None},     // 47
    {"DD 48: LD C,B",                      OpcodeInfo::ArgTypes::None},     // 48
    {"DD 49: LD C,C",                      OpcodeInfo::ArgTypes::None},     // 49
    {"DD 4A: LD C,D",                      OpcodeInfo::ArgTypes::None},     // 4A
    {"DD 4B: LD C,E",                      OpcodeInfo::ArgTypes::None},     // 4B
    {"DD 4C: LD C,IXh",                    OpcodeInfo::ArgTypes::None},     // 4C
    {"DD 4D: LD C,IXl",                    OpcodeInfo::ArgTypes::None},     // 4D
    {"DD 4E %02X: LD C,(IX+%d)",           OpcodeInfo::ArgTypes::D},        // 4E
    {"DD 4F: LD C,A",                      OpcodeInfo::ArgTypes::None},     // 4F
    {"DD 50: LD D,B",                      OpcodeInfo::ArgTypes::None},     // 50
    {"DD 51: LD D,C",                      OpcodeInfo::ArgTypes::None},     // 51
    {"DD 52: LD D,D",                      OpcodeInfo::ArgTypes::None},     // 52
    {"DD 53: LD D,E",                      OpcodeInfo::ArgTypes::None},     // 53
    {"DD 54: LD D,IXh",                    OpcodeInfo::ArgTypes::None},     // 54
    {"DD 55: LD D,IXl",                    OpcodeInfo::ArgTypes::None},     // 55
    {"DD 56 %02X: LD D,(IX+%d)",           OpcodeInfo::ArgTypes::D},        // 56
    {"DD 57: LD D,A",                      OpcodeInfo::ArgTypes::None},     // 57
    {"DD 58: LD E,B",                      OpcodeInfo::ArgTypes::None},     // 58
    {"DD 59: LD E,C",                      OpcodeInfo::ArgTypes::None},     // 59
    {"DD 5A: LD E,D",                      OpcodeInfo::ArgTypes::None},     // 5A
    {"DD 5B: LD E,E",                      OpcodeInfo::ArgTypes::None},     // 5B
    {"DD 5C: LD E,IXh",                    OpcodeInfo::ArgTypes::None},     // 5C
    {"DD 5D: LD E,IXl",                    OpcodeInfo::ArgTypes::None},     // 5D
    {"DD 5E %02X: LD E,(IX+%d)",           OpcodeInfo::ArgTypes::D},        // 5E
    {"DD 5F: LD E,A",                      OpcodeInfo::ArgTypes::None},     // 5F
    {"DD 60: LD IXh,B",                    OpcodeInfo::ArgTypes::None},     // 60
    {"DD 61: LD IXh,C",                    OpcodeInfo::ArgTypes::None},     // 61
    {"DD 62: LD IXh,D",                    OpcodeInfo::ArgTypes::None},     // 62
    {"DD 63: LD IXh,E",                    OpcodeInfo::ArgTypes::None},     // 63
    {"DD 64: LD IXh,IXh",                  OpcodeInfo::ArgTypes::None},     // 64
    {"DD 65: LD IXh,IXl",                  OpcodeInfo::ArgTypes::None},     // 65
    {"DD 66 %02X: LD H,(IX+%d)",           OpcodeInfo::ArgTypes::D},        // 66
    {"DD 67: LD IXh,A",                    OpcodeInfo::ArgTypes::None},     // 67
    {"DD 68: LD IXl,B",                    OpcodeInfo::ArgTypes::None},     // 68
    {"DD 69: LD IXl,C",                    OpcodeInfo::ArgTypes::None},     // 69
    {"DD 6A: LD IXl,D",                    OpcodeInfo::ArgTypes::None},     // 6A
    {"DD 6B: LD IXl,E",                    OpcodeInfo::ArgTypes::None},     // 6B
    {"DD 6C: LD IXl,IXh",                  OpcodeInfo::ArgTypes::None},     // 6C
    {"DD 6D: LD IXl,IXl",                  OpcodeInfo::ArgTypes::None},     // 6D
    {"DD 6E %02X: LD L,(IX+%d)",           OpcodeInfo::ArgTypes::D},        // 6E
    {"DD 6F: LD IXl,A",                    OpcodeInfo::ArgTypes::None},     // 6F
    {"DD 70 %02X: LD (IX+%d),B",           OpcodeInfo::ArgTypes::D},        // 70
    {"DD 71 %02X: LD (IX+%d),C",           OpcodeInfo::ArgTypes::D},        // 71
    {"DD 72 %02X: LD (IX+%d),D",           OpcodeInfo::ArgTypes::D},        // 72
    {"DD 73 %02X: LD (IX+%d),E",           OpcodeInfo::ArgTypes::D},        // 73
    {"DD 74 %02X: LD (IX+%d),H",           OpcodeInfo::ArgTypes::D},        // 74
    {"DD 75 %02X: LD (IX+%d),L",           OpcodeInfo::ArgTypes::D},        // 75
    {"DD 76: HALT",                        OpcodeInfo::ArgTypes::None},     // 76
    {"DD 77 %02X: LD (IX+%d),A",           OpcodeInfo::ArgTypes::D},        // 77
    {"DD 78: LD A,B",                      OpcodeInfo::ArgTypes::None},     // 78
    {"DD 79: LD A,C",                      OpcodeInfo::ArgTypes::None},     // 79
    {"DD 7A: LD A,D",                      OpcodeInfo::ArgTypes::None},     // 7A
    {"DD 7B: LD A,E",                      OpcodeInfo::ArgTypes::None},     // 7B
    {"DD 7C: LD A,IXh",                    OpcodeInfo::ArgTypes::None},     // 7C
    {"DD 7D: LD A,IXl",                    OpcodeInfo::ArgTypes::None},     // 7D
    {"DD 7E %02X: LD A,(IX+%d)",           OpcodeInfo::ArgTypes::D},        // 7E
    {"DD 7F: LD A,A",                      OpcodeInfo::ArgTypes::None},     // 7F
    {"DD 80: ADD A,B",                     OpcodeInfo::ArgTypes::None},     // 80
    {"DD 81: ADD A,C",                     OpcodeInfo::ArgTypes::None},     // 81
    {"DD 82: ADD A,D",                     OpcodeInfo::ArgTypes::None},     // 82
    {"DD 83: ADD A,E",                     OpcodeInfo::ArgTypes::None},     // 83
    {"DD 84: ADD A,IXh",                   OpcodeInfo::ArgTypes::None},     // 84
    {"DD 85: ADD A,IXl",                   OpcodeInfo::ArgTypes::None},     // 85
    {"DD 86 %02X: ADD A,(IX+%d)",          OpcodeInfo::ArgTypes::D},        // 86
    {"DD 87: ADD A,A",                     OpcodeInfo::ArgTypes::None},     // 87
    {"DD 88: ADC A,B",                     OpcodeInfo::ArgTypes::None},     // 88
    {"DD 89: ADC A,C",                     OpcodeInfo::ArgTypes::None},     // 89
    {"DD 8A: ADC A,D",                     OpcodeInfo::ArgTypes::None},     // 8A
    {"DD 8B: ADC A,E",                     OpcodeInfo::ArgTypes::None},     // 8B
    {"DD 8C: ADC A,IXh",                   OpcodeInfo::ArgTypes::None},     // 8C
    {"DD 8D: ADC A,IXl",                   OpcodeInfo::ArgTypes::None},     // 8D
    {"DD 8E %02X: ADC A,(IX+%d)",          OpcodeInfo::ArgTypes::D},        // 8E
    {"DD 8F: ADC A,A",                     OpcodeInfo::ArgTypes::None},     // 8F
    {"DD 90: SUB B",                       OpcodeInfo::ArgTypes::None},     // 90
    {"DD 91: SUB C",                       OpcodeInfo::ArgTypes::None},     // 91
    {"DD 92: SUB D",                       OpcodeInfo::ArgTypes::None},     // 92
    {"DD 93: SUB E",                       OpcodeInfo::ArgTypes::None},     // 93
    {"DD 94: SUB IXh",                     OpcodeInfo::ArgTypes::None},     // 94
    {"DD 95: SUB IXl",                     OpcodeInfo::ArgTypes::None},     // 95
    {"DD 96 %02X: SUB (IX+%d)",            OpcodeInfo::ArgTypes::D},        // 96
    {"DD 97: SUB A",                       OpcodeInfo::ArgTypes::None},     // 97
    {"DD 98: SBC A,B",                     OpcodeInfo::ArgTypes::None},     // 98
    {"DD 99: SBC A,C",                     OpcodeInfo::ArgTypes::None},     // 99
    {"DD 9A: SBC A,D",                     OpcodeInfo::ArgTypes::None},     // 9A
    {"DD 9B: SBC A,E",                     OpcodeInfo::ArgTypes::None},     // 9B
    {"DD 9C: SBC A,IXh",                   OpcodeInfo::ArgTypes::None},     // 9C
    {"DD 9D: SBC A,IXl",                   OpcodeInfo::ArgTypes::None},     // 9D
    {"DD 9E %02X: SBC A,(IX+%d)",          OpcodeInfo::ArgTypes::D},        // 9E
    {"DD 9F: SBC A,A",                     OpcodeInfo::ArgTypes::None},     // 9F
    {"DD A0: AND B",                       OpcodeInfo::ArgTypes::None},     // A0
    {"DD A1: AND C",                       OpcodeInfo::ArgTypes::None},     // A1
    {"DD A2: AND D",                       OpcodeInfo::ArgTypes::None},     // A2
    {"DD A3: AND E",                       OpcodeInfo::ArgTypes::None},     // A3
    {"DD A4: AND IXh",                     OpcodeInfo::ArgTypes::None},     // A4
    {"DD A5: AND IXl",                     OpcodeInfo::ArgTypes::None},     // A5
    {"DD A6 %02X: AND (IX+%d)",            OpcodeInfo::ArgTypes::D},        // A6
    {"DD A7: AND A",                       OpcodeInfo::ArgTypes::None},     // A7
    {"DD A8: XOR B",                       OpcodeInfo::ArgTypes::None},     // A8
    {"DD A9: XOR C",                       OpcodeInfo::ArgTypes::None},     // A9
    {"DD AA: XOR D",                       OpcodeInfo::ArgTypes::None},     // AA
    {"DD AB: XOR E",                       OpcodeInfo::ArgTypes::None},     // AB
    {"DD AC: XOR IXh",                     OpcodeInfo::ArgTypes::None},     // AC
    {"DD AD: XOR IXl",                     OpcodeInfo::ArgTypes::None},     // AD
    {"DD AE %02X: XOR (IX+%d)",            OpcodeInfo::ArgTypes::D},        // AE
    {"DD AF: XOR A",                       OpcodeInfo::ArgTypes::None},     // AF
    {"DD B0: OR B",                        OpcodeInfo::ArgTypes::None},     // B0
    {"DD B1: OR C",                        OpcodeInfo::ArgTypes::None},     // B1
    {"DD B2: OR D",                        OpcodeInfo::ArgTypes::None},     // B2
    {"DD B3: OR E",                        OpcodeInfo::ArgTypes::None},     // B3
    {"DD B4: OR IXh",                      OpcodeInfo::ArgTypes::None},     // B4
    {"DD B5: OR IXl",                      OpcodeInfo::ArgTypes::None},     // B5
    {"DD B6 %02X: OR (IX+%d)",             OpcodeInfo::ArgTypes::D},        // B6
    {"DD B7: OR A",                        OpcodeInfo::ArgTypes::None},     // B7
    {"DD B8: CP B",                        OpcodeInfo::ArgTypes::None},     // B8
    {"DD B9: CP C",                        OpcodeInfo::ArgTypes::None},     // B9
    {"DD BA: CP D",                        OpcodeInfo::ArgTypes::None},     // BA
    {"DD BB: CP E",                        OpcodeInfo::ArgTypes::None},     // BB
    {"DD BC: CP IXh",                      OpcodeInfo::ArgTypes::None},     // BC
    {"DD BD: CP IXl",                      OpcodeInfo::ArgTypes::None},     // BD
    {"DD BE %02X: CP (IX+%d)",             OpcodeInfo::ArgTypes::D},        // BE
    {"DD BF: CP A",                        OpcodeInfo::ArgTypes::None},     // BF
    {"DD C0: RET NZ",                      OpcodeInfo::ArgTypes::None},     // C0
    {"DD C1: POP BC",                      OpcodeInfo::ArgTypes::None},     // C1
    {"DD C2 %02X %02X: JP NZ,%04X",        OpcodeInfo::ArgTypes::NN},       // C2
    {"DD C3 %02X %02X: JP %04X",           OpcodeInfo::ArgTypes::NN},       // C3
    {"DD C4 %02X %02X: CALL NZ,%04X",      OpcodeInfo::ArgTypes::NN},       // C4
    {"DD C5: PUSH BC",                     OpcodeInfo::ArgTypes::None},     // C5
    {"DD C6 %02X: ADD A,%02X",             OpcodeInfo::ArgTypes::N},        // C6
    {"DD C7: RST 0",                       OpcodeInfo::ArgTypes::None},     // C7
    {"DD C8: RET Z",                       OpcodeInfo::ArgTypes::None},     // C8
    {"DD C9: RET",                         OpcodeInfo::ArgTypes::None},     // C9
    {"DD CA %02X %02X: JP Z,%04X",         OpcodeInfo::ArgTypes::NN},       // CA
    {"DD CB %02X: [See DDCB i%02Xfo]",     OpcodeInfo::ArgTypes::N},        // CB
    {"DD CC %02X %02X: CALL Z,%04X",       OpcodeInfo::ArgTypes::NN},       // CC
    {"DD CD %02X %02X: CALL %04X",         OpcodeInfo::ArgTypes::NN},       // CD
    {"DD CE %02X: ADC A,%02X",             OpcodeInfo::ArgTypes::N},        // CE
    {"DD CF: RST 8",                       OpcodeInfo::ArgTypes::None},     // CF
    {"DD D0: RET NC",                      OpcodeInfo::ArgTypes::None},     // D0
    {"DD D1: POP DE",                      OpcodeInfo::ArgTypes::None},     // D1
    {"DD D2 %02X %02X: JP NC,%04X",        OpcodeInfo::ArgTypes::NN},       // D2
    {"DD D3 %02X: OUT (%02X),A",           OpcodeInfo::ArgTypes::N},        // D3
    {"DD D4 %02X %02X: CALL NC,%04X",      OpcodeInfo::ArgTypes::NN},       // D4
    {"DD D5: PUSH DE",                     OpcodeInfo::ArgTypes::None},     // D5
    {"DD D6 %02X: SUB %02X",               OpcodeInfo::ArgTypes::N},        // D6
    {"DD D7: RST 10H",                     OpcodeInfo::ArgTypes::None},     // D7
    {"DD D8: RET C",                       OpcodeInfo::ArgTypes::None},     // D8
    {"DD D9: EXX",                         OpcodeInfo::ArgTypes::None},     // D9
    {"DD DA %02X %02X: JP C,%04X",         OpcodeInfo::ArgTypes::NN},       // DA
    {"DD DB %02X: IN A,(%02X)",            OpcodeInfo::ArgTypes::N},        // DB
    {"DD DC %02X %02X: CALL C,%04X",       OpcodeInfo::ArgTypes::NN},       // DC
    {"DD DD: [IX Prefix]",                 OpcodeInfo::ArgTypes::None},     // DD
    {"DD DE %02X: SBC A,%02X",             OpcodeInfo::ArgTypes::N},        // DE
    {"DD DF: RST 18H",                     OpcodeInfo::ArgTypes::None},     // DF
    {"DD E0: RET PO",                      OpcodeInfo::ArgTypes::None},     // E0
    {"DD E1: POP IX",                      OpcodeInfo::ArgTypes::None},     // E1
    {"DD E2 %02X %02X: JP PO,%04X",        OpcodeInfo::ArgTypes::NN},       // E2
    {"DD E3: EX (SP),IX",                  OpcodeInfo::ArgTypes::None},     // E3
    {"DD E4 %02X %02X: CALL PO,%04X",      OpcodeInfo::ArgTypes::NN},       // E4
    {"DD E5: PUSH IX",                     OpcodeInfo::ArgTypes::None},     // E5
    {"DD E6 %02X: AND %02X",               OpcodeInfo::ArgTypes::N},        // E6
    {"DD E7: RST 20H",                     OpcodeInfo::ArgTypes::None},     // E7
    {"DD E8: RET PE",                      OpcodeInfo::ArgTypes::None},     // E8
    {"DD E9: JP (IX)",                     OpcodeInfo::ArgTypes::None},     // E9
    {"DD EA %02X %02X: JP PE,%04X",        OpcodeInfo::ArgTypes::NN},       // EA
    {"DD EB: EX DE,HL",                    OpcodeInfo::ArgTypes::None},     // EB
    {"DD EC %02X %02X: CALL PE,%04X",      OpcodeInfo::ArgTypes::NN},       // EC
    {"DD ED: [Prefix]",                    OpcodeInfo::ArgTypes::None},     // ED
    {"DD EE %02X: XOR %02X",               OpcodeInfo::ArgTypes::N},        // EE
    {"DD EF: RST 28H",                     OpcodeInfo::ArgTypes::None},     // EF
    {"DD F0: RET P",                       OpcodeInfo::ArgTypes::None},     // F0
    {"DD F1: POP AF",                      OpcodeInfo::ArgTypes::None},     // F1
    {"DD F2 %02X %02X: JP P,%04X",         OpcodeInfo::ArgTypes::NN},       // F2
    {"DD F3: DI",                          OpcodeInfo::ArgTypes::None},     // F3
    {"DD F4 %02X %02X: CALL P,%04X",       OpcodeInfo::ArgTypes::NN},       // F4
    {"DD F5: PUSH AF",                     OpcodeInfo::ArgTypes::None},     // F5
    {"DD F6 %02X: OR %02X",                OpcodeInfo::ArgTypes::N},        // F6
    {"DD F7: RST 30H",                     OpcodeInfo::ArgTypes::None},     // F7
    {"DD F8: RET M",                       OpcodeInfo::ArgTypes::None},     // F8
    {"DD F9: LD SP,IX",                    OpcodeInfo::ArgTypes::None},     // F9
    {"DD FA %02X %02X: JP M,%04X",         OpcodeInfo::ArgTypes::NN},       // FA
    {"DD FB: EI",                          OpcodeInfo::ArgTypes::None},     // FB
    {"DD FC %02X %02X: CALL M,%04X",       OpcodeInfo::ArgTypes::NN},       // FC
    {"DD FD: [IY Prefix]",                 OpcodeInfo::ArgTypes::None},     // FD
    {"DD FE %02X: CP %02X",                OpcodeInfo::ArgTypes::N},        // FE
    {"DD FF: RST 38H",                     OpcodeInfo::ArgTypes::None},     // FF
}};

inline constexpr std::array<OpcodeInfo, 256> OpcodeTableED = {{
    {"ED 00: NOP",                         OpcodeInfo::ArgTypes::None},     // 00
    {"ED 01: NOP",                         OpcodeInfo::ArgTypes::None},     // 01
    {"ED 02: NOP",                         OpcodeInfo::ArgTypes::None},     // 02
    {"ED 03: NOP",                         OpcodeInfo::ArgTypes::None},     // 03
    {"ED 04: NOP",                         OpcodeInfo::ArgTypes::None},     // 04
    {"ED 05: NOP",                         OpcodeInfo::ArgTypes::None},     // 05
    {"ED 06: NOP",                         OpcodeInfo::ArgTypes::None},     // 06
    {"ED 07: NOP",                         OpcodeInfo::ArgTypes::None},     // 07
    {"ED 08: NOP",                         OpcodeInfo::ArgTypes::None},     // 08
    {"ED 09: NOP",                         OpcodeInfo::ArgTypes::None},     // 09
    {"ED 0A: NOP",                         OpcodeInfo::ArgTypes::None},     // 0A
    {"ED 0B: NOP",                         OpcodeInfo::ArgTypes::None},     // 0B
    {"ED 0C: NOP",                         OpcodeInfo::ArgTypes::None},     // 0C
    {"ED 0D: NOP",                         OpcodeInfo::ArgTypes::None},     // 0D
    {"ED 0E: NOP",                         OpcodeInfo::ArgTypes::None},     // 0E
    {"ED 0F: NOP",                         OpcodeInfo::ArgTypes::None},     // 0F
    {"ED 10: NOP",                         OpcodeInfo::ArgTypes::None},     // 10
    {"ED 11: NOP",                         OpcodeInfo::ArgTypes::None},     // 11
    {"ED 12: NOP",                         OpcodeInfo::ArgTypes::None},     // 12
    {"ED 13: NOP",                         OpcodeInfo::ArgTypes::None},     // 13
    {"ED 14: NOP",                         OpcodeInfo::ArgTypes::None},     // 14
    {"ED 15: NOP",                         OpcodeInfo::ArgTypes::None},     // 15
    {"ED 16: NOP",                         OpcodeInfo::ArgTypes::None},     // 16
    {"ED 17: NOP",                         OpcodeInfo::ArgTypes::None},     // 17
    {"ED 18: NOP",                         OpcodeInfo::ArgTypes::None},     // 18
    {"ED 19: NOP",                         OpcodeInfo::ArgTypes::None},     // 19
    {"ED 1A: NOP",                         OpcodeInfo::ArgTypes::None},     // 1A
    {"ED 1B: NOP",                         OpcodeInfo::ArgTypes::None},     // 1B
    {"ED 1C: NOP",                         OpcodeInfo::ArgTypes::None},     // 1C
    {"ED 1D: NOP",                         OpcodeInfo::ArgTypes::None},     // 1D
    {"ED 1E: NOP",                         OpcodeInfo::ArgTypes::None},     // 1E
    {"ED 1F: NOP",                         OpcodeInfo::ArgTypes::None},     // 1F
    {"ED 20: NOP",                         OpcodeInfo::ArgTypes::None},     // 20
    {"ED 21: NOP",                         OpcodeInfo::ArgTypes::None},     // 21
    {"ED 22: NOP",                         OpcodeInfo::ArgTypes::None},     // 22
    {"ED 23: NOP",                         OpcodeInfo::ArgTypes::None},     // 23
    {"ED 24: NOP",                         OpcodeInfo::ArgTypes::None},     // 24
    {"ED 25: NOP",                         OpcodeInfo::ArgTypes::None},     // 25
    {"ED 26: NOP",                         OpcodeInfo::ArgTypes::None},     // 26
    {"ED 27: NOP",                         OpcodeInfo::ArgTypes::None},     // 27
    {"ED 28: NOP",                         OpcodeInfo::ArgTypes::None},     // 28
    {"ED 29: NOP",                         OpcodeInfo::ArgTypes::None},     // 29
    {"ED 2A: NOP",                         OpcodeInfo::ArgTypes::None},     // 2A
    {"ED 2B: NOP",                         OpcodeInfo::ArgTypes::None},     // 2B
    {"ED 2C: NOP",                         OpcodeInfo::ArgTypes::None},     // 2C
    {"ED 2D: NOP",                         OpcodeInfo::ArgTypes::None},     // 2D
    {"ED 2E: NOP",                         OpcodeInfo::ArgTypes::None},     // 2E
    {"ED 2F: NOP",                         OpcodeInfo::ArgTypes::None},     // 2F
    {"ED 30: NOP",                         OpcodeInfo::ArgTypes::None},     // 30
    {"ED 31: NOP",                         OpcodeInfo::ArgTypes::None},     // 31
    {"ED 32: NOP",                         OpcodeInfo::ArgTypes::None},     // 32
    {"ED 33: NOP",                         OpcodeInfo::ArgTypes::None},     // 33
    {"ED 34: NOP",                         OpcodeInfo::ArgTypes::None},     // 34
    {"ED 35: NOP",                         OpcodeInfo::ArgTypes::None},     // 35
    {"ED 36: NOP",                         OpcodeInfo::ArgTypes::None},     // 36
    {"ED 37: NOP",                         OpcodeInfo::ArgTypes::None},     // 37
    {"ED 38: NOP",                         OpcodeInfo::ArgTypes::None},     // 38
    {"ED 39: NOP",                         OpcodeInfo::ArgTypes::None},     // 39
    {"ED 3A: NOP",                         OpcodeInfo::ArgTypes::None},     // 3A
    {"ED 3B: NOP",                         OpcodeInfo::ArgTypes::None},     // 3B
    {"ED 3C: NOP",                         OpcodeInfo::ArgTypes::None},     // 3C
    {"ED 3D: NOP",                         OpcodeInfo::ArgTypes::None},     // 3D
    {"ED 3E: NOP",                         OpcodeInfo::ArgTypes::None},     // 3E
    {"ED 3F: NOP",                         OpcodeInfo::ArgTypes::None},     // 3F
    {"ED 40: IN B,(C)",                    OpcodeInfo::ArgTypes::None},     // 40
    {"ED 41: OUT (C),B",                   OpcodeInfo::ArgTypes::None},     // 41
    {"ED 42: SBC HL,BC",                   OpcodeInfo::ArgTypes::None},     // 42
    {"ED 43 %02X %02X: LD (%04X),BC",      OpcodeInfo::ArgTypes::NN},       // 43
    {"ED 44: NEG",                         OpcodeInfo::ArgTypes::None},     // 44
    {"ED 45: RETN",                        OpcodeInfo::ArgTypes::None},     // 45
    {"ED 46: IM 0",                        OpcodeInfo::ArgTypes::None},     // 46
    {"ED 47: LD I,A",                      OpcodeInfo::ArgTypes::None},     // 47
    {"ED 48: IN C,(C)",                    OpcodeInfo::ArgTypes::None},     // 48
    {"ED 49: OUT (C),C",                   OpcodeInfo::ArgTypes::None},     // 49
    {"ED 4A: ADC HL,BC",                   OpcodeInfo::ArgTypes::None},     // 4A
    {"ED 4B %02X %02X: LD BC,(%04X)",      OpcodeInfo::ArgTypes::NN},       // 4B
    {"ED 4C: NEG",                         OpcodeInfo::ArgTypes::None},     // 4C
    {"ED 4D: RETI",                        OpcodeInfo::ArgTypes::None},     // 4D
    {"ED 4E: IM * (0?)",                   OpcodeInfo::ArgTypes::None},     // 4E
    {"ED 4F: LD R,A",                      OpcodeInfo::ArgTypes::None},     // 4F
    {"ED 50: IN D,(C)",                    OpcodeInfo::ArgTypes::None},     // 50
    {"ED 51: OUT (C),D",                   OpcodeInfo::ArgTypes::None},     // 51
    {"ED 52: SBC HL,DE",                   OpcodeInfo::ArgTypes::None},     // 52
    {"ED 53 %02X %02X: LD (%04X),DE",      OpcodeInfo::ArgTypes::NN},       // 53
    {"ED 54: NEG",                         OpcodeInfo::ArgTypes::None},     // 54
    {"ED 55: RETN",                        OpcodeInfo::ArgTypes::None},     // 55
    {"ED 56: IM 1",                        OpcodeInfo::ArgTypes::None},     // 56
    {"ED 57: LD A,I",                      OpcodeInfo::ArgTypes::None},     // 57
    {"ED 58: IN E,(C)",                    OpcodeInfo::ArgTypes::None},     // 58
    {"ED 59: OUT (C),E",                   OpcodeInfo::ArgTypes::None},     // 59
    {"ED 5A: ADC HL,DE",                   OpcodeInfo::ArgTypes::None},     // 5A
    {"ED 5B %02X %02X: LD DE,(%04X)",      OpcodeInfo::ArgTypes::NN},       // 5B
    {"ED 5C: NEG",                         OpcodeInfo::ArgTypes::None},     // 5C
    {"ED 5D: RETI",                        OpcodeInfo::ArgTypes::None},     // 5D
    {"ED 5E: IM 2",                        OpcodeInfo::ArgTypes::None},     // 5E
    {"ED 5F: LD A,R",                      OpcodeInfo::ArgTypes::None},     // 5F
    {"ED 60: IN H,(C)",                    OpcodeInfo::ArgTypes::None},     // 60
    {"ED 61: OUT (C),H",                   OpcodeInfo::ArgTypes::None},     // 61
    {"ED 62: SBC HL,HL",                   OpcodeInfo::ArgTypes::None},     // 62
    {"ED 63 %02X %02X: LD (%04X),HL",      OpcodeInfo::ArgTypes::NN},       // 63
    {"ED 64: NEG",                         OpcodeInfo::ArgTypes::None},     // 64
    {"ED 65: RETN",                        OpcodeInfo::ArgTypes::None},     // 65
    {"ED 66: IM 0",                        OpcodeInfo::ArgTypes::None},     // 66
    {"ED 67: RRD",                         OpcodeInfo::ArgTypes::None},     // 67
    {"ED 68: IN L,(C)",                    OpcodeInfo::ArgTypes::None},     // 68
    {"ED 69: OUT (C),L",                   OpcodeInfo::ArgTypes::None},     // 69
    {"ED 6A: ADC HL,HL",                   OpcodeInfo::ArgTypes::None},     // 6A
    {"ED 6B %02X %02X: LD HL,(%04X)",      OpcodeInfo::ArgTypes::NN},       // 6B
    {"ED 6C: NEG",                         OpcodeInfo::ArgTypes::None},     // 6C
    {"ED 6D: RETI",                        OpcodeInfo::ArgTypes::None},     // 6D
    {"ED 6E: IM * (0?)",                   OpcodeInfo::ArgTypes::None},     // 6E
    {"ED 6F: RLD",                         OpcodeInfo::ArgTypes::None},     // 6F
    {"ED 70: IN X,(C)",                    OpcodeInfo::ArgTypes::None},     // 70
    {"ED 71: OUT (C),X(0)",                OpcodeInfo::ArgTypes::None},     // 71
    {"ED 72: SBC HL,SP",                   OpcodeInfo::ArgTypes::None},     // 72
    {"ED 73 %02X %02X: LD (%04X),SP",      OpcodeInfo::ArgTypes::NN},       // 73
    {"ED 74: NEG",                         OpcodeInfo::ArgTypes::None},     // 74
    {"ED 75: RETN",                        OpcodeInfo::ArgTypes::None},     // 75
    {"ED 76: IM 1",                        OpcodeInfo::ArgTypes::None},     // 76
    {"ED 77: NOP",                         OpcodeInfo::ArgTypes::None},     // 77
    {"ED 78: IN A,(C)",                    OpcodeInfo::ArgTypes::None},     // 78
    {"ED 79: OUT (C),A",                   OpcodeInfo::ArgTypes::None},     // 79
    {"ED 7A: ADC HL,SP",                   OpcodeInfo::ArgTypes::None},     // 7A
    {"ED 7B %02X %02X: LD SP,(%04X)",      OpcodeInfo::ArgTypes::NN},       // 7B
    {"ED 7C: NEG",                         OpcodeInfo::ArgTypes::None},     // 7C
    {"ED 7D: RETI",                        OpcodeInfo::ArgTypes::None},     // 7D
    {"ED 7E: IM 2",                        OpcodeInfo::ArgTypes::None},     // 7E
    {"ED 7F: NOP",                         OpcodeInfo::ArgTypes::None},     // 7F
    {"ED 80: NOP",                         OpcodeInfo::ArgTypes::None},     // 80
    {"ED 81: NOP",                         OpcodeInfo::ArgTypes::None},     // 81
    {"ED 82: NOP",                         OpcodeInfo::ArgTypes::None},     // 82
    {"ED 83: NOP",                         OpcodeInfo::ArgTypes::None},     // 83
    {"ED 84: NOP",                         OpcodeInfo::ArgTypes::None},     // 84
    {"ED 85: NOP",                         OpcodeInfo::ArgTypes::None},     // 85
    {"ED 86: NOP",                         OpcodeInfo::ArgTypes::None},     // 86
    {"ED 87: NOP",                         OpcodeInfo::ArgTypes::None},     // 87
    {"ED 88: NOP",                         OpcodeInfo::ArgTypes::None},     // 88
    {"ED 89: NOP",                         OpcodeInfo::ArgTypes::None},     // 89
    {"ED 8A: NOP",                         OpcodeInfo::ArgTypes::None},     // 8A
    {"ED 8B: NOP",                         OpcodeInfo::ArgTypes::None},     // 8B
    {"ED 8C: NOP",                         OpcodeInfo::ArgTypes::None},     // 8C
    {"ED 8D: NOP",                         OpcodeInfo::ArgTypes::None},     // 8D
    {"ED 8E: NOP",                         OpcodeInfo::ArgTypes::None},     // 8E
    {"ED 8F: NOP",                         OpcodeInfo::ArgTypes::None},     // 8F
    {"ED 90: NOP",                         OpcodeInfo::ArgTypes::None},     // 90
    {"ED 91: NOP",                         OpcodeInfo::ArgTypes::None},     // 91
    {"ED 92: NOP",                         OpcodeInfo::ArgTypes::None},     // 92
    {"ED 93: NOP",                         OpcodeInfo::ArgTypes::None},     // 93
    {"ED 94: NOP",                         OpcodeInfo::ArgTypes::None},     // 94
    {"ED 95: NOP",                         OpcodeInfo::ArgTypes::None},     // 95
    {"ED 96: NOP",                         OpcodeInfo::ArgTypes::None},     // 96
    {"ED 97: NOP",                         OpcodeInfo::ArgTypes::None},     // 97
    {"ED 98: NOP",                         OpcodeInfo::ArgTypes::None},     // 98
    {"ED 99: NOP",                         OpcodeInfo::ArgTypes::None},     // 99
    {"ED 9A: NOP",                         OpcodeInfo::ArgTypes::None},     // 9A
    {"ED 9B: NOP",                         OpcodeInfo::ArgTypes::None},     // 9B
    {"ED 9C: NOP",                         OpcodeInfo::ArgTypes::None},     // 9C
    {"ED 9D: NOP",                         OpcodeInfo::ArgTypes::None},     // 9D
    {"ED 9E: NOP",                         OpcodeInfo::ArgTypes::None},     // 9E
    {"ED 9F: NOP",                         OpcodeInfo::ArgTypes::None},     // 9F
    {"ED A0: LDI",                         OpcodeInfo::ArgTypes::None},     // A0
    {"ED A1: CPI",                         OpcodeInfo::ArgTypes::None},     // A1
    {"ED A2: INI",                         OpcodeInfo::ArgTypes::None},     // A2
    {"ED A3: OUTI",                        OpcodeInfo::ArgTypes::None},     // A3
    {"ED A4: NOP",                         OpcodeInfo::ArgTypes::None},     // A4
    {"ED A5: NOP",                         OpcodeInfo::ArgTypes::None},     // A5
    {"ED A6: NOP",                         OpcodeInfo::ArgTypes::None},     // A6
    {"ED A7: NOP",                         OpcodeInfo::ArgTypes::None},     // A7
    {"ED A8: LDD",                         OpcodeInfo::ArgTypes::None},     // A8
    {"ED A9: CPD",                         OpcodeInfo::ArgTypes::None},     // A9
    {"ED AA: IND",                         OpcodeInfo::ArgTypes::None},     // AA
    {"ED AB: OUTD",                        OpcodeInfo::ArgTypes::None},     // AB
    {"ED AC: NOP",                         OpcodeInfo::ArgTypes::None},     // AC
    {"ED AD: NOP",                         OpcodeInfo::ArgTypes::None},     // AD
    {"ED AE: NOP",                         OpcodeInfo::ArgTypes::None},     // AE
    {"ED AF: NOP",                         OpcodeInfo::ArgTypes::None},     // AF
    {"ED B0: LDIR",                        OpcodeInfo::ArgTypes::None},     // B0
    {"ED B1: CPIR",                        OpcodeInfo::ArgTypes::None},     // B1
    {"ED B2: INIR",                        OpcodeInfo::ArgTypes::None},     // B2
    {"ED B3: OTIR",                        OpcodeInfo::ArgTypes::None},     // B3
    {"ED B4: NOP",                         OpcodeInfo::ArgTypes::None},     // B4
    {"ED B5: NOP",                         OpcodeInfo::ArgTypes::None},     // B5
    {"ED B6: NOP",                         OpcodeInfo::ArgTypes::None},     // B6
    {"ED B7: NOP",                         OpcodeInfo::ArgTypes::None},     // B7
    {"ED B8: LDDR",                        OpcodeInfo::ArgTypes::None},     // B8
    {"ED B9: CPDR",                        OpcodeInfo::ArgTypes::None},     // B9
    {"ED BA: INDR",                        OpcodeInfo::ArgTypes::None},     // BA
    {"ED BB: OTDR",                        OpcodeInfo::ArgTypes::None},     // BB
    {"ED BC: NOP",                         OpcodeInfo::ArgTypes::None},     // BC
    {"ED BD: NOP",                         OpcodeInfo::ArgTypes::None},     // BD
    {"ED BE: NOP",                         OpcodeInfo::ArgTypes::None},     // BE
    {"ED BF: NOP",                         OpcodeInfo::ArgTypes::None},     // BF
    {"ED C0: NOP",                         OpcodeInfo::ArgTypes::None},     // C0
    {"ED C1: NOP",                         OpcodeInfo::ArgTypes::None},     // C1
    {"ED C2: NOP",                         OpcodeInfo::ArgTypes::None},     // C2
    {"ED C3: NOP",                         OpcodeInfo::ArgTypes::None},     // C3
    {"ED C4: NOP",                         OpcodeInfo::ArgTypes::None},     // C4
    {"ED C5: NOP",                         OpcodeInfo::ArgTypes::None},     // C5
    {"ED C6: NOP",                         OpcodeInfo::ArgTypes::None},     // C6
    {"ED C7: NOP",                         OpcodeInfo::ArgTypes::None},     // C7
    {"ED C8: NOP",                         OpcodeInfo::ArgTypes::None},     // C8
    {"ED C9: NOP",                         OpcodeInfo::ArgTypes::None},     // C9
    {"ED CA: NOP",                         OpcodeInfo::ArgTypes::None},     // CA
    {"ED CB: NOP",                         OpcodeInfo::ArgTypes::None},     // CB
    {"ED CC: NOP",                         OpcodeInfo::ArgTypes::None},     // CC
    {"ED CD: NOP",                         OpcodeInfo::ArgTypes::None},     // CD
    {"ED CE: NOP",                         OpcodeInfo::ArgTypes::None},     // CE
    {"ED CF: NOP",                         OpcodeInfo::ArgTypes::None},     // CF
    {"ED D0: NOP",                         OpcodeInfo::ArgTypes::None},     // D0
    {"ED D1: NOP",                         OpcodeInfo::ArgTypes::None},     // D1
    {"ED D2: NOP",                         OpcodeInfo::ArgTypes::None},     // D2
    {"ED D3: NOP",                         OpcodeInfo::ArgTypes::None},     // D3
    {"ED D4: NOP",                         OpcodeInfo::ArgTypes::None},     // D4
    {"ED D5: NOP",                         OpcodeInfo::ArgTypes::None},     // D5
    {"ED D6: NOP",                         OpcodeInfo::ArgTypes::None},     // D6
    {"ED D7: NOP",                         OpcodeInfo::ArgTypes::None},     // D7
    {"ED D8: NOP",                         OpcodeInfo::ArgTypes::None},     // D8
    {"ED D9: NOP",                         OpcodeInfo::ArgTypes::None},     // D9
    {"ED DA: NOP",                         OpcodeInfo::ArgTypes::None},     // DA
    {"ED DB: NOP",                         OpcodeInfo::ArgTypes::None},     // DB
    {"ED DC: NOP",                         OpcodeInfo::ArgTypes::None},     // DC
    {"ED DD: NOP",                         OpcodeInfo::ArgTypes::None},     // DD
    {"ED DE: NOP",                         OpcodeInfo::ArgTypes::None},     // DE
    {"ED DF: NOP",                         OpcodeInfo::ArgTypes::None},     // DF
    {"ED E0: NOP",                         OpcodeInfo::ArgTypes::None},     // E0
    {"ED E1: NOP",                         OpcodeInfo::ArgTypes::None},     // E1
    {"ED E2: NOP",                         OpcodeInfo::ArgTypes::None},     // E2
    {"ED E3: NOP",                         OpcodeInfo::ArgTypes::None},     // E3
    {"ED E4: NOP",                         OpcodeInfo::ArgTypes::None},     // E4
    {"ED E5: NOP",                         OpcodeInfo::ArgTypes::None},     // E5
    {"ED E6: NOP",                         OpcodeInfo::ArgTypes::None},     // E6
    {"ED E7: NOP",                         OpcodeInfo::ArgTypes::None},     // E7
    {"ED E8: NOP",                         OpcodeInfo::ArgTypes::None},     // E8
    {"ED E9: NOP",                         OpcodeInfo::ArgTypes::None},     // E9
    {"ED EA: NOP",                         OpcodeInfo::ArgTypes::None},     // EA
    {"ED EB: NOP",                         OpcodeInfo::ArgTypes::None},     // EB
    {"ED EC: NOP",                         OpcodeInfo::ArgTypes::None},     // EC
    {"ED ED: NOP",                         OpcodeInfo::ArgTypes::None},     // ED
    {"ED EE: NOP",                         OpcodeInfo::ArgTypes::None},     // EE
    {"ED EF: NOP",                         OpcodeInfo::ArgTypes::None},     // EF
    {"ED F0: NOP",                         OpcodeInfo::ArgTypes::None},     // F0
    {"ED F1: NOP",                         OpcodeInfo::ArgTypes::None},     // F1
    {"ED F2: NOP",                         OpcodeInfo::ArgTypes::None},     // F2
    {"ED F3: NOP",                         OpcodeInfo::ArgTypes::None},     // F3
    {"ED F4: NOP",                         OpcodeInfo::ArgTypes::None},     // F4
    {"ED F5: NOP",                         OpcodeInfo::ArgTypes::None},     // F5
    {"ED F6: NOP",                         OpcodeInfo::ArgTypes::None},     // F6
    {"ED F7: NOP",                         OpcodeInfo::ArgTypes::None},     // F7
    {"ED F8: NOP",                         OpcodeInfo::ArgTypes::None},     // F8
    {"ED F9: NOP",                         OpcodeInfo::ArgTypes::None},     // F9
    {"ED FA: NOP",                         OpcodeInfo::ArgTypes::None},     // FA
    {"ED FB: NOP",                         OpcodeInfo::ArgTypes::None},     // FB
    {"ED FC: NOP",                         OpcodeInfo::ArgTypes::None},     // FC
    {"ED FD: NOP",                         OpcodeInfo::ArgTypes::None},     // FD
    {"ED FE: NOP",                         OpcodeInfo::ArgTypes::None},     // FE
    {"ED FF: NOP",                         OpcodeInfo::ArgTypes::None},     // FF
}};

inline constexpr std::array<OpcodeInfo, 256> OpcodeTableFD = {{
    {"FD 00: NOP",                         OpcodeInfo::ArgTypes::None},     // 00
    {"FD 01 %02X %02X: LD BC,%04X",        OpcodeInfo::ArgTypes::NN},       // 01
    {"FD 02: LD (BC),A",                   OpcodeInfo::ArgTypes::None},     // 02
    {"FD 03: INC BC",                      OpcodeInfo::ArgTypes::None},     // 03
    {"FD 04: INC B",                       OpcodeInfo::ArgTypes::None},     // 04
    {"FD 05: DEC B",                       OpcodeInfo::ArgTypes::None},     // 05
    {"FD 06 %02X: LD B,%02X",              OpcodeInfo::ArgTypes::N},        // 06
    {"FD 07: RLCA",                        OpcodeInfo::ArgTypes::None},     // 07
    {"FD 08: EX AF,AF'",                   OpcodeInfo::ArgTypes::None},     // 08
    {"FD 09: ADD IY,BC",                   OpcodeInfo::ArgTypes::None},     // 09
    {"FD 0A: LD A,(BC)",                   OpcodeInfo::ArgTypes::None},     // 0A
    {"FD 0B: DEC BC",                      OpcodeInfo::ArgTypes::None},     // 0B
    {"FD 0C: INC C",                       OpcodeInfo::ArgTypes::None},     // 0C
    {"FD 0D: DEC C",                       OpcodeInfo::ArgTypes::None},     // 0D
    {"FD 0E %02X: LD C,%02X",              OpcodeInfo::ArgTypes::N},        // 0E
    {"FD 0F: RRCA",                        OpcodeInfo::ArgTypes::None},     // 0F
    {"FD 10 %02X: DJNZ %d",                OpcodeInfo::ArgTypes::D},        // 10
    {"FD 11 %02X %02X: LD DE,%04X",        OpcodeInfo::ArgTypes::NN},       // 11
    {"FD 12: LD (DE),A",                   OpcodeInfo::ArgTypes::None},     // 12
    {"FD 13: INC DE",                      OpcodeInfo::ArgTypes::None},     // 13
    {"FD 14: INC D",                       OpcodeInfo::ArgTypes::None},     // 14
    {"FD 15: DEC D",                       OpcodeInfo::ArgTypes::None},     // 15
    {"FD 16 %02X: LD D,%02X",              OpcodeInfo::ArgTypes::N},        // 16
    {"FD 17: RLA",                         OpcodeInfo::ArgTypes::None},     // 17
    {"FD 18 %02X: JR %d",                  OpcodeInfo::ArgTypes::D},        // 18
    {"FD 19: ADD IY,DE",                   OpcodeInfo::ArgTypes::None},     // 19
    {"FD 1A: LD A,(DE)",                   OpcodeInfo::ArgTypes::None},     // 1A
    {"FD 1B: DEC DE",                      OpcodeInfo::ArgTypes::None},     // 1B
    {"FD 1C: INC E",                       OpcodeInfo::ArgTypes::None},     // 1C
    {"FD 1D: DEC E",                       OpcodeInfo::ArgTypes::None},     // 1D
    {"FD 1E %02X: LD E,%02X",              OpcodeInfo::ArgTypes::N},        // 1E
    {"FD 1F: RRA",                         OpcodeInfo::ArgTypes::None},     // 1F
    {"FD 20 %02X: JR NZ,%d",               OpcodeInfo::ArgTypes::D},        // 20
    {"FD 21 %02X %02X: LD IY,%04X",        OpcodeInfo::ArgTypes::NN},       // 21
    {"FD 22 %02X %02X: LD (%04X),IY",      OpcodeInfo::ArgTypes::NN},       // 22
    {"FD 23: INC IY",                      OpcodeInfo::ArgTypes::None},     // 23
    {"FD 24: INC IYh",                     OpcodeInfo::ArgTypes::None},     // 24
    {"FD 25: DEC IYh",                     OpcodeInfo::ArgTypes::None},     // 25
    {"FD 26 %02X: LD IYh,%02X",            OpcodeInfo::ArgTypes::N},        // 26
    {"FD 27: DAA",                         OpcodeInfo::ArgTypes::None},     // 27
    {"FD 28 %02X: JR Z,%d",                OpcodeInfo::ArgTypes::D},        // 28
    {"FD 29: ADD IY,IY",                   OpcodeInfo::ArgTypes::None},     // 29
    {"FD 2A %02X %02X: LD IY,(%04X)",      OpcodeInfo::ArgTypes::NN},       // 2A
    {"FD 2B: DEC IY",                      OpcodeInfo::ArgTypes::None},     // 2B
    {"FD 2C: INC IYl",                     OpcodeInfo::ArgTypes::None},     // 2C
    {"FD 2D: DEC IYl",                     OpcodeInfo::ArgTypes::None},     // 2D
    {"FD 2E %02X: LD IYl,%02X",            OpcodeInfo::ArgTypes::N},        // 2E
    {"FD 2F: CPL",                         OpcodeInfo::ArgTypes::None},     // 2F
    {"FD 30 %02X: JR NC,%d",               OpcodeInfo::ArgTypes::D},        // 30
    {"FD 31 %02X %02X: LD SP,%04X",        OpcodeInfo::ArgTypes::NN},       // 31
    {"FD 32 %02X %02X: LD (%04X),A",       OpcodeInfo::ArgTypes::NN},       // 32
    {"FD 33: INC SP",                      OpcodeInfo::ArgTypes::None},     // 33
    {"FD 34 %02X: INC (IY+%d)",            OpcodeInfo::ArgTypes::D},        // 34
    {"FD 35 %02X: DEC (IY+%d)",            OpcodeInfo::ArgTypes::D},        // 35
    {"FD 36 %02X %02X: LD (IY+%d),%02X",   OpcodeInfo::ArgTypes::DN},       // 36
    {"FD 37: SCF",                         OpcodeInfo::ArgTypes::None},     // 37
    {"FD 38 %02X: JR C,%d",                OpcodeInfo::ArgTypes::D},        // 38
    {"FD 39: ADD IY,SP",                   OpcodeInfo::ArgTypes::None},     // 39
    {"FD 3A %02X %02X: LD A,(%04X)",       OpcodeInfo::ArgTypes::NN},       // 3A
    {"FD 3B: DEC SP",                      OpcodeInfo::ArgTypes::None},     // 3B
    {"FD 3C: INC A",                       OpcodeInfo::ArgTypes::None},     // 3C
    {"FD 3D: DEC A",                       OpcodeInfo::ArgTypes::None},     // 3D
    {"FD 3E %02X: LD A,%02X",              OpcodeInfo::ArgTypes::N},        // 3E
    {"FD 3F: CCF",                         OpcodeInfo::ArgTypes::None},     // 3F
    {"FD 40: LD B,B",                      OpcodeInfo::ArgTypes::None},     // 40
    {"FD 41: LD B,C",                      OpcodeInfo::ArgTypes::None},     // 41
    {"FD 42: LD B,D",                      OpcodeInfo::ArgTypes::None},     // 42
    {"FD 43: LD B,E",                      OpcodeInfo::ArgTypes::None},     // 43
    {"FD 44: LD B,IYh",                    OpcodeInfo::ArgTypes::None},     // 44
    {"FD 45: LD B,IYl",                    OpcodeInfo::ArgTypes::None},     // 45
    {"FD 46 %02X: LD B,(IY+%d)",           OpcodeInfo::ArgTypes::D},        // 46
    {"FD 47: LD B,A",                      OpcodeInfo::ArgTypes::None},     // 47
    {"FD 48: LD C,B",                      OpcodeInfo::ArgTypes::None},     // 48
    {"FD 49: LD C,C",                      OpcodeInfo::ArgTypes::None},     // 49
    {"FD 4A: LD C,D",                      OpcodeInfo::ArgTypes::None},     // 4A
    {"FD 4B: LD C,E",                      OpcodeInfo::ArgTypes::None},     // 4B
    {"FD 4C: LD C,IYh",                    OpcodeInfo::ArgTypes::None},     // 4C
    {"FD 4D: LD C,IYl",                    OpcodeInfo::ArgTypes::None},     // 4D
    {"FD 4E %02X: LD C,(IY+%d)",           OpcodeInfo::ArgTypes::D},        // 4E
    {"FD 4F: LD C,A",                      OpcodeInfo::ArgTypes::None},     // 4F
    {"FD 50: LD D,B",                      OpcodeInfo::ArgTypes::None},     // 50
    {"FD 51: LD D,C",                      OpcodeInfo::ArgTypes::None},     // 51
    {"FD 52: LD D,D",                      OpcodeInfo::ArgTypes::None},     // 52
    {"FD 53: LD D,E",                      OpcodeInfo::ArgTypes::None},     // 53
    {"FD 54: LD D,IYh",                    OpcodeInfo::ArgTypes::None},     // 54
    {"FD 55: LD D,IYl",                    OpcodeInfo::ArgTypes::None},     // 55
    {"FD 56 %02X: LD D,(IY+%d)",           OpcodeInfo::ArgTypes::D},        // 56
    {"FD 57: LD D,A",                      OpcodeInfo::ArgTypes::None},     // 57
    {"FD 58: LD E,B",                      OpcodeInfo::ArgTypes::None},     // 58
    {"FD 59: LD E,C",                      OpcodeInfo::ArgTypes::None},     // 59
    {"FD 5A: LD E,D",                      OpcodeInfo::ArgTypes::None},     // 5A
    {"FD 5B: LD E,E",                      OpcodeInfo::ArgTypes::None},     // 5B
    {"FD 5C: LD E,IYh",                    OpcodeInfo::ArgTypes::None},     // 5C
    {"FD 5D: LD E,IYl",                    OpcodeInfo::ArgTypes::None},     // 5D
    {"FD 5E %02X: LD E,(IY+%d)",           OpcodeInfo::ArgTypes::D},        // 5E
    {"FD 5F: LD E,A",                      OpcodeInfo::ArgTypes::None},     // 5F
    {"FD 60: LD IYh,B",                    OpcodeInfo::ArgTypes::None},     // 60
    {"FD 61: LD IYh,C",                    OpcodeInfo::ArgTypes::None},     // 61
    {"FD 62: LD IYh,D",                    OpcodeInfo::ArgTypes::None},     // 62
    {"FD 63: LD IYh,E",                    OpcodeInfo::ArgTypes::None},     // 63
    {"FD 64: LD IYh,IYh",                  OpcodeInfo::ArgTypes::None},     // 64
    {"FD 65: LD IYh,IYl",                  OpcodeInfo::ArgTypes::None},     // 65
    {"FD 66 %02X: LD H,(IY+%d)",           OpcodeInfo::ArgTypes::D},        // 66
    {"FD 67: LD IYh,A",                    OpcodeInfo::ArgTypes::None},     // 67
    {"FD 68: LD IYl,B",                    OpcodeInfo::ArgTypes::None},     // 68
    {"FD 69: LD IYl,C",                    OpcodeInfo::ArgTypes::None},     // 69
    {"FD 6A: LD IYl,D",                    OpcodeInfo::ArgTypes::None},     // 6A
    {"FD 6B: LD IYl,E",                    OpcodeInfo::ArgTypes::None},     // 6B
    {"FD 6C: LD IYl,IYh",                  OpcodeInfo::ArgTypes::None},     // 6C
    {"FD 6D: LD IYl,IYl",                  OpcodeInfo::ArgTypes::None},     // 6D
    {"FD 6E %02X: LD L,(IY+%d)",           OpcodeInfo::ArgTypes::D},        // 6E
    {"FD 6F: LD IYl,A",                    OpcodeInfo::ArgTypes::None},     // 6F
    {"FD 70 %02X: LD (IY+%d),B",           OpcodeInfo::ArgTypes::D},        // 70
    {"FD 71 %02X: LD (IY+%d),C",           OpcodeInfo::ArgTypes::D},        // 71
    {"FD 72 %02X: LD (IY+%d),D",           OpcodeInfo::ArgTypes::D},        // 72
    {"FD 73 %02X: LD (IY+%d),E",           OpcodeInfo::ArgTypes::D},        // 73
    {"FD 74 %02X: LD (IY+%d),H",           OpcodeInfo::ArgTypes::D},        // 74
    {"FD 75 %02X: LD (IY+%d),L",           OpcodeInfo::ArgTypes::D},        // 75
    {"FD 76: HALT",                        OpcodeInfo::ArgTypes::None},     // 76
    {"FD 77 %02X: LD (IY+%d),A",           OpcodeInfo::ArgTypes::D},        // 77
    {"FD 78: LD A,B",                      OpcodeInfo::ArgTypes::None},     // 78
    {"FD 79: LD A,C",                      OpcodeInfo::ArgTypes::None},     // 79
    {"FD 7A: LD A,D",                      OpcodeInfo::ArgTypes::None},     // 7A
    {"FD 7B: LD A,E",                      OpcodeInfo::ArgTypes::None},     // 7B
    {"FD 7C: LD A,IYh",                    OpcodeInfo::ArgTypes::None},     // 7C
    {"FD 7D: LD A,IYl",                    OpcodeInfo::ArgTypes::None},     // 7D
    {"FD 7E %02X: LD A,(IY+%d)",           OpcodeInfo::ArgTypes::D},        // 7E
    {"FD 7F: LD A,A",                      OpcodeInfo::ArgTypes::None},     // 7F
    {"FD 80: ADD A,B",                     OpcodeInfo::ArgTypes::None},     // 80
    {"FD 81: ADD A,C",                     OpcodeInfo::ArgTypes::None},     // 81
    {"FD 82: ADD A,D",                     OpcodeInfo::ArgTypes::None},     // 82
    {"FD 83: ADD A,E",                     OpcodeInfo::ArgTypes::None},     // 83
    {"FD 84: ADD A,IYh",                   OpcodeInfo::ArgTypes::None},     // 84
    {"FD 85: ADD A,IYl",                   OpcodeInfo::ArgTypes::None},     // 85
    {"FD 86 %02X: ADD A,(IY+%d)",          OpcodeInfo::ArgTypes::D},        // 86
    {"FD 87: ADD A,A",                     OpcodeInfo::ArgTypes::None},     // 87
    {"FD 88: ADC A,B",                     OpcodeInfo::ArgTypes::None},     // 88
    {"FD 89: ADC A,C",                     OpcodeInfo::ArgTypes::None},     // 89
    {"FD 8A: ADC A,D",                     OpcodeInfo::ArgTypes::None},     // 8A
    {"FD 8B: ADC A,E",                     OpcodeInfo::ArgTypes::None},     // 8B
    {"FD 8C: ADC A,IYh",                   OpcodeInfo::ArgTypes::None},     // 8C
    {"FD 8D: ADC A,IYl",                   OpcodeInfo::ArgTypes::None},     // 8D
    {"FD 8E %02X: ADC A,(IY+%d)",          OpcodeInfo::ArgTypes::D},        // 8E
    {"FD 8F: ADC A,A",                     OpcodeInfo::ArgTypes::None},     // 8F
    {"FD 90: SUB B",                       OpcodeInfo::ArgTypes::None},     // 90
    {"FD 91: SUB C",                       OpcodeInfo::ArgTypes::None},     // 91
    {"FD 92: SUB D",                       OpcodeInfo::ArgTypes::None},     // 92
    {"FD 93: SUB E",                       OpcodeInfo::ArgTypes::None},     // 93
    {"FD 94: SUB IYh",                     OpcodeInfo::ArgTypes::None},     // 94
    {"FD 95: SUB IYl",                     OpcodeInfo::ArgTypes::None},     // 95
    {"FD 96 %02X: SUB (IY+%d)",            OpcodeInfo::ArgTypes::D},        // 96
    {"FD 97: SUB A",                       OpcodeInfo::ArgTypes::None},     // 97
    {"FD 98: SBC A,B",                     OpcodeInfo::ArgTypes::None},     // 98
    {"FD 99: SBC A,C",                     OpcodeInfo::ArgTypes::None},     // 99
    {"FD 9A: SBC A,D",                     OpcodeInfo::ArgTypes::None},     // 9A
    {"FD 9B: SBC A,E",                     OpcodeInfo::ArgTypes::None},     // 9B
    {"FD 9C: SBC A,IYh",                   OpcodeInfo::ArgTypes::None},     // 9C
    {"FD 9D: SBC A,IYl",                   OpcodeInfo::ArgTypes::None},     // 9D
    {"FD 9E %02X: SBC A,(IY+%d)",          OpcodeInfo::ArgTypes::D},        // 9E
    {"FD 9F: SBC A,A",                     OpcodeInfo::ArgTypes::None},     // 9F
    {"FD A0: AND B",                       OpcodeInfo::ArgTypes::None},     // A0
    {"FD A1: AND C",                       OpcodeInfo::ArgTypes::None},     // A1
    {"FD A2: AND D",                       OpcodeInfo::ArgTypes::None},     // A2
    {"FD A3: AND E",                       OpcodeInfo::ArgTypes::None},     // A3
    {"FD A4: AND IYh",                     OpcodeInfo::ArgTypes::None},     // A4
    {"FD A5: AND IYl",                     OpcodeInfo::ArgTypes::None},     // A5
    {"FD A6 %02X: AND (IY+%d)",            OpcodeInfo::ArgTypes::D},        // A6
    {"FD A7: AND A",                       OpcodeInfo::ArgTypes::None},     // A7
    {"FD A8: XOR B",                       OpcodeInfo::ArgTypes::None},     // A8
    {"FD A9: XOR C",                       OpcodeInfo::ArgTypes::None},     // A9
    {"FD AA: XOR D",                       OpcodeInfo::ArgTypes::None},     // AA
    {"FD AB: XOR E",                       OpcodeInfo::ArgTypes::None},     // AB
    {"FD AC: XOR IYh",                     OpcodeInfo::ArgTypes::None},     // AC
    {"FD AD: XOR IYl",                     OpcodeInfo::ArgTypes::None},     // AD
    {"FD AE %02X: XOR (IY+%d)",            OpcodeInfo::ArgTypes::D},        // AE
    {"FD AF: XOR A",                       OpcodeInfo::ArgTypes::None},     // AF
    {"FD B0: OR B",                        OpcodeInfo::ArgTypes::None},     // B0
    {"FD B1: OR C",                        OpcodeInfo::ArgTypes::None},     // B1
    {"FD B2: OR D",                        OpcodeInfo::ArgTypes::None},     // B2
    {"FD B3: OR E",                        OpcodeInfo::ArgTypes::None},     // B3
    {"FD B4: OR IYh",                      OpcodeInfo::ArgTypes::None},     // B4
    {"FD B5: OR IYl",                      OpcodeInfo::ArgTypes::None},     // B5
    {"FD B6 %02X: OR (IY+%d)",             OpcodeInfo::ArgTypes::D},        // B6
    {"FD B7: OR A",                        OpcodeInfo::ArgTypes::None},     // B7
    {"FD B8: CP B",                        OpcodeInfo::ArgTypes::None},     // B8
    {"FD B9: CP C",                        OpcodeInfo::ArgTypes::None},     // B9
    {"FD BA: CP D",                        OpcodeInfo::ArgTypes::None},     // BA
    {"FD BB: CP E",                        OpcodeInfo::ArgTypes::None},     // BB
    {"FD BC: CP IYh",                      OpcodeInfo::ArgTypes::None},     // BC
    {"FD BD: CP IYl",                      OpcodeInfo::ArgTypes::None},     // BD
    {"FD BE %02X: CP (IY+%d)",             OpcodeInfo::ArgTypes::D},        // BE
    {"FD BF: CP A",                        OpcodeInfo::ArgTypes::None},     // BF
    {"FD C0: RET NZ",                      OpcodeInfo::ArgTypes::None},     // C0
    {"FD C1: POP BC",                      OpcodeInfo::ArgTypes::None},     // C1
    {"FD C2 %02X %02X: JP NZ,%04X",        OpcodeInfo::ArgTypes::NN},       // C2
    {"FD C3 %02X %02X: JP %04X",           OpcodeInfo::ArgTypes::NN},       // C3
    {"FD C4 %02X %02X: CALL NZ,%04X",      OpcodeInfo::ArgTypes::NN},       // C4
    {"FD C5: PUSH BC",                     OpcodeInfo::ArgTypes::None},     // C5
    {"FD C6 %02X: ADD A,%02X",             OpcodeInfo::ArgTypes::N},        // C6
    {"FD C7: RST 0",                       OpcodeInfo::ArgTypes::None},     // C7
    {"FD C8: RET Z",                       OpcodeInfo::ArgTypes::None},     // C8
    {"FD C9: RET",                         OpcodeInfo::ArgTypes::None},     // C9
    {"FD CA %02X %02X: JP Z,%04X",         OpcodeInfo::ArgTypes::NN},       // CA
    {"FD CB %02X: [See DDCB i%02Xfo]",     OpcodeInfo::ArgTypes::N},        // CB
    {"FD CC %02X %02X: CALL Z,%04X",       OpcodeInfo::ArgTypes::NN},       // CC
    {"FD CD %02X %02X: CALL %04X",         OpcodeInfo::ArgTypes::NN},       // CD
    {"FD CE %02X: ADC A,%02X",             OpcodeInfo::ArgTypes::N},        // CE
    {"FD CF: RST 8",                       OpcodeInfo::ArgTypes::None},     // CF
    {"FD D0: RET NC",                      OpcodeInfo::ArgTypes::None},     // D0
    {"FD D1: POP DE",                      OpcodeInfo::ArgTypes::None},     // D1
    {"FD D2 %02X %02X: JP NC,%04X",        OpcodeInfo::ArgTypes::NN},       // D2
    {"FD D3 %02X: OUT (%02X),A",           OpcodeInfo::ArgTypes::N},        // D3
    {"FD D4 %02X %02X: CALL NC,%04X",      OpcodeInfo::ArgTypes::NN},       // D4
    {"FD D5: PUSH DE",                     OpcodeInfo::ArgTypes::None},     // D5
    {"FD D6 %02X: SUB %02X",               OpcodeInfo::ArgTypes::N},        // D6
    {"FD D7: RST 10H",                     OpcodeInfo::ArgTypes::None},     // D7
    {"FD D8: RET C",                       OpcodeInfo::ArgTypes::None},     // D8
    {"FD D9: EXX",                         OpcodeInfo::ArgTypes::None},     // D9
    {"FD DA %02X %02X: JP C,%04X",         OpcodeInfo::ArgTypes::NN},       // DA
    {"FD DB %02X: IN A,(%02X)",            OpcodeInfo::ArgTypes::N},        // DB
    {"FD DC %02X %02X: CALL C,%04X",       OpcodeInfo::ArgTypes::NN},       // DC
    {"FD DD: [IY Prefix]",                 OpcodeInfo::ArgTypes::None},     // DD
    {"FD DE %02X: SBC A,%02X",             OpcodeInfo::ArgTypes::N},        // DE
    {"FD DF: RST 18H",                     OpcodeInfo::ArgTypes::None},     // DF
    {"FD E0: RET PO",                      OpcodeInfo::ArgTypes::None},     // E0
    {"FD E1: POP IY",                      OpcodeInfo::ArgTypes::None},     // E1
    {"FD E2 %02X %02X: JP PO,%04X",        OpcodeInfo::ArgTypes::NN},       // E2
    {"FD E3: EX (SP),IY",                  OpcodeInfo::ArgTypes::None},     // E3
    {"FD E4 %02X %02X: CALL PO,%04X",      OpcodeInfo::ArgTypes::NN},       // E4
    {"FD E5: PUSH IY",                     OpcodeInfo::ArgTypes::None},     // E5
    {"FD E6 %02X: AND %02X",               OpcodeInfo::ArgTypes::N},        // E6
    {"FD E7: RST 20H",                     OpcodeInfo::ArgTypes::None},     // E7
    {"FD E8: RET PE",                      OpcodeInfo::ArgTypes::None},     // E8
    {"FD E9: JP (IY)",                     OpcodeInfo::ArgTypes::None},     // E9
    {"FD EA %02X %02X: JP PE,%04X",        OpcodeInfo::ArgTypes::NN},       // EA
    {"FD EB: EX DE,HL",                    OpcodeInfo::ArgTypes::None},     // EB
    {"FD EC %02X %02X: CALL PE,%04X",      OpcodeInfo::ArgTypes::NN},       // EC
    {"FD ED: [Prefix]",                    OpcodeInfo::ArgTypes::None},     // ED
    {"FD EE %02X: XOR %02X",               OpcodeInfo::ArgTypes::N},        // EE
    {"FD EF: RST 28H",                     OpcodeInfo::ArgTypes::None},     // EF
    {"FD F0: RET P",                       OpcodeInfo::ArgTypes::None},     // F0
    {"FD F1: POP AF",                      OpcodeInfo::ArgTypes::None},     // F1
    {"FD F2 %02X %02X: JP P,%04X",         OpcodeInfo::ArgTypes::NN},       // F2
    {"FD F3: DI",                          OpcodeInfo::ArgTypes::None},     // F3
    {"FD F4 %02X %02X: CALL P,%04X",       OpcodeInfo::ArgTypes::NN},       // F4
    {"FD F5: PUSH AF",                     OpcodeInfo::ArgTypes::None},     // F5
    {"FD F6 %02X: OR %02X",                OpcodeInfo::ArgTypes::N},        // F6
    {"FD F7: RST 30H",                     OpcodeInfo::ArgTypes::None},     // F7
    {"FD F8: RET M",                       OpcodeInfo::ArgTypes::None},     // F8
    {"FD F9: LD SP,IY",                    OpcodeInfo::ArgTypes::None},     // F9
    {"FD FA %02X %02X: JP M,%04X",         OpcodeInfo::ArgTypes::NN},       // FA
    {"FD FB: EI",                          OpcodeInfo::ArgTypes::None},     // FB
    {"FD FC %02X %02X: CALL M,%04X",       OpcodeInfo::ArgTypes::NN},       // FC
    {"FD FD: [IY Prefix]",                 OpcodeInfo::ArgTypes::None},     // FD
    {"FD FE %02X: CP %02X",                OpcodeInfo::ArgTypes::N},        // FE
    {"FD FF: RST 38H",                     OpcodeInfo::ArgTypes::None},     // FF
}};

inline constexpr std::array<OpcodeInfo, 256> OpcodeTableDDCB = {{
    {"DD CB %02X 00: LD B,RLC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 00
    {"DD CB %02X 01: LD C,RLC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 01
    {"DD CB %02X 02: LD D,RLC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 02
    {"DD CB %02X 03: LD E,RLC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 03
    {"DD CB %02X 04: LD H,RLC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 04
    {"DD CB %02X 05: LD L,RLC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 05
    {"DD CB %02X 06: RLC (IX+%d)",         OpcodeInfo::ArgTypes::D},        // 06
    {"DD CB %02X 07: LD A,RLC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 07
    {"DD CB %02X 08: LD B,RRC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 08
    {"DD CB %02X 09: LD C,RRC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 09
    {"DD CB %02X 0A: LD D,RRC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 0A
    {"DD CB %02X 0B: LD E,RRC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 0B
    {"DD CB %02X 0C: LD H,RRC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 0C
    {"DD CB %02X 0D: LD L,RRC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 0D
    {"DD CB %02X 0E: RRC (IX+%d)",         OpcodeInfo::ArgTypes::D},        // 0E
    {"DD CB %02X 0F: LD A,RRC (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 0F
    {"DD CB %02X 10: LD B,RL (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 10
    {"DD CB %02X 11: LD C,RL (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 11
    {"DD CB %02X 12: LD D,RL (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 12
    {"DD CB %02X 13: LD E,RL (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 13
    {"DD CB %02X 14: LD H,RL (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 14
    {"DD CB %02X 15: LD L,RL (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 15
    {"DD CB %02X 16: RL (IX+%d)",          OpcodeInfo::ArgTypes::D},        // 16
    {"DD CB %02X 17: LD A,RL (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 17
    {"DD CB %02X 18: LD B,RR (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 18
    {"DD CB %02X 19: LD C,RR (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 19
    {"DD CB %02X 1A: LD D,RR (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 1A
    {"DD CB %02X 1B: LD E,RR (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 1B
    {"DD CB %02X 1C: LD H,RR (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 1C
    {"DD CB %02X 1D: LD L,RR (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 1D
    {"DD CB %02X 1E: RR (IX+%d)",          OpcodeInfo::ArgTypes::D},        // 1E
    {"DD CB %02X 1F: LD A,RR (IX+%d)",     OpcodeInfo::ArgTypes::D},        // 1F
    {"DD CB %02X 20: LD B,SLA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 20
    {"DD CB %02X 21: LD C,SLA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 21
    {"DD CB %02X 22: LD D,SLA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 22
    {"DD CB %02X 23: LD E,SLA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 23
    {"DD CB %02X 24: LD H,SLA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 24
    {"DD CB %02X 25: LD L,SLA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 25
    {"DD CB %02X 26: SLA (IX+%d)",         OpcodeInfo::ArgTypes::D},        // 26
    {"DD CB %02X 27: LD A,SLA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 27
    {"DD CB %02X 28: LD B,SRA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 28
    {"DD CB %02X 29: LD C,SRA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 29
    {"DD CB %02X 2A: LD D,SRA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 2A
    {"DD CB %02X 2B: LD E,SRA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 2B
    {"DD CB %02X 2C: LD H,SRA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 2C
    {"DD CB %02X 2D: LD L,SRA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 2D
    {"DD CB %02X 2E: SRA (IX+%d)",         OpcodeInfo::ArgTypes::D},        // 2E
    {"DD CB %02X 2F: LD A,SRA (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 2F
    {"DD CB %02X 30: LD B,SLL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 30
    {"DD CB %02X 31: LD C,SLL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 31
    {"DD CB %02X 32: LD D,SLL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 32
    {"DD CB %02X 33: LD E,SLL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 33
    {"DD CB %02X 34: LD H,SLL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 34
    {"DD CB %02X 35: LD L,SLL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 35
    {"DD CB %02X 36: SLL (IX+%d)",         OpcodeInfo::ArgTypes::D},        // 36
    {"DD CB %02X 37: LD A,SLL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 37
    {"DD CB %02X 38: LD B,SRL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 38
    {"DD CB %02X 39: LD C,SRL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 39
    {"DD CB %02X 3A: LD D,SRL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 3A
    {"DD CB %02X 3B: LD E,SRL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 3B
    {"DD CB %02X 3C: LD H,SRL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 3C
    {"DD CB %02X 3D: LD L,SRL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 3D
    {"DD CB %02X 3E: SRL (IX+%d)",         OpcodeInfo::ArgTypes::D},        // 3E
    {"DD CB %02X 3F: LD A,SRL (IX+%d)",    OpcodeInfo::ArgTypes::D},        // 3F
    {"DD CB %02X 40: BIT 0,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 40
    {"DD CB %02X 41: BIT 0,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 41
    {"DD CB %02X 42: BIT 0,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 42
    {"DD CB %02X 43: BIT 0,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 43
    {"DD CB %02X 44: BIT 0,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 44
    {"DD CB %02X 45: BIT 0,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 45
    {"DD CB %02X 46: BIT 0,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 46
    {"DD CB %02X 47: BIT 0,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 47
    {"DD CB %02X 48: BIT 1,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 48
    {"DD CB %02X 49: BIT 1,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 49
    {"DD CB %02X 4A: BIT 1,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 4A
    {"DD CB %02X 4B: BIT 1,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 4B
    {"DD CB %02X 4C: BIT 1,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 4C
    {"DD CB %02X 4D: BIT 1,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 4D
    {"DD CB %02X 4E: BIT 1,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 4E
    {"DD CB %02X 4F: BIT 1,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 4F
    {"DD CB %02X 50: BIT 2,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 50
    {"DD CB %02X 51: BIT 2,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 51
    {"DD CB %02X 52: BIT 2,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 52
    {"DD CB %02X 53: BIT 2,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 53
    {"DD CB %02X 54: BIT 2,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 54
    {"DD CB %02X 55: BIT 2,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 55
    {"DD CB %02X 56: BIT 2,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 56
    {"DD CB %02X 57: BIT 2,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 57
    {"DD CB %02X 58: BIT 3,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 58
    {"DD CB %02X 59: BIT 3,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 59
    {"DD CB %02X 5A: BIT 3,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 5A
    {"DD CB %02X 5B: BIT 3,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 5B
    {"DD CB %02X 5C: BIT 3,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 5C
    {"DD CB %02X 5D: BIT 3,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 5D
    {"DD CB %02X 5E: BIT 3,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 5E
    {"DD CB %02X 5F: BIT 3,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 5F
    {"DD CB %02X 60: BIT 4,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 60
    {"DD CB %02X 61: BIT 4,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 61
    {"DD CB %02X 62: BIT 4,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 62
    {"DD CB %02X 63: BIT 4,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 63
    {"DD CB %02X 64: BIT 4,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 64
    {"DD CB %02X 65: BIT 4,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 65
    {"DD CB %02X 66: BIT 4,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 66
    {"DD CB %02X 67: BIT 4,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 67
    {"DD CB %02X 68: BIT 5,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 68
    {"DD CB %02X 69: BIT 5,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 69
    {"DD CB %02X 6A: BIT 5,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 6A
    {"DD CB %02X 6B: BIT 5,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 6B
    {"DD CB %02X 6C: BIT 5,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 6C
    {"DD CB %02X 6D: BIT 5,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 6D
    {"DD CB %02X 6E: BIT 5,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 6E
    {"DD CB %02X 6F: BIT 5,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 6F
    {"DD CB %02X 70: BIT 6,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 70
    {"DD CB %02X 71: BIT 6,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 71
    {"DD CB %02X 72: BIT 6,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 72
    {"DD CB %02X 73: BIT 6,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 73
    {"DD CB %02X 74: BIT 6,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 74
    {"DD CB %02X 75: BIT 6,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 75
    {"DD CB %02X 76: BIT 6,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 76
    {"DD CB %02X 77: BIT 6,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 77
    {"DD CB %02X 78: BIT 7,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 78
    {"DD CB %02X 79: BIT 7,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 79
    {"DD CB %02X 7A: BIT 7,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 7A
    {"DD CB %02X 7B: BIT 7,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 7B
    {"DD CB %02X 7C: BIT 7,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 7C
    {"DD CB %02X 7D: BIT 7,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 7D
    {"DD CB %02X 7E: BIT 7,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 7E
    {"DD CB %02X 7F: BIT 7,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 7F
    {"DD CB %02X 80: LD B,RES 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 80
    {"DD CB %02X 81: LD C,RES 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 81
    {"DD CB %02X 82: LD D,RES 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 82
    {"DD CB %02X 83: LD E,RES 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 83
    {"DD CB %02X 84: LD H,RES 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 84
    {"DD CB %02X 85: LD L,RES 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 85
    {"DD CB %02X 86: RES 0,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 86
    {"DD CB %02X 87: LD A,RES 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 87
    {"DD CB %02X 88: LD B,RES 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 88
    {"DD CB %02X 89: LD C,RES 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 89
    {"DD CB %02X 8A: LD D,RES 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 8A
    {"DD CB %02X 8B: LD E,RES 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 8B
    {"DD CB %02X 8C: LD H,RES 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 8C
    {"DD CB %02X 8D: LD L,RES 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 8D
    {"DD CB %02X 8E: RES 1,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 8E
    {"DD CB %02X 8F: LD A,RES 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 8F
    {"DD CB %02X 90: LD B,RES 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 90
    {"DD CB %02X 91: LD C,RES 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 91
    {"DD CB %02X 92: LD D,RES 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 92
    {"DD CB %02X 93: LD E,RES 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 93
    {"DD CB %02X 94: LD H,RES 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 94
    {"DD CB %02X 95: LD L,RES 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 95
    {"DD CB %02X 96: RES 2,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 96
    {"DD CB %02X 97: LD A,RES 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 97
    {"DD CB %02X 98: LD B,RES 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 98
    {"DD CB %02X 99: LD C,RES 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 99
    {"DD CB %02X 9A: LD D,RES 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 9A
    {"DD CB %02X 9B: LD E,RES 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 9B
    {"DD CB %02X 9C: LD H,RES 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 9C
    {"DD CB %02X 9D: LD L,RES 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 9D
    {"DD CB %02X 9E: RES 3,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // 9E
    {"DD CB %02X 9F: LD A,RES 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // 9F
    {"DD CB %02X A0: LD B,RES 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // A0
    {"DD CB %02X A1: LD C,RES 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // A1
    {"DD CB %02X A2: LD D,RES 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // A2
    {"DD CB %02X A3: LD E,RES 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // A3
    {"DD CB %02X A4: LD H,RES 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // A4
    {"DD CB %02X A5: LD L,RES 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // A5
    {"DD CB %02X A6: RES 4,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // A6
    {"DD CB %02X A7: LD A,RES 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // A7
    {"DD CB %02X A8: LD B,RES 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // A8
    {"DD CB %02X A9: LD C,RES 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // A9
    {"DD CB %02X AA: LD D,RES 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // AA
    {"DD CB %02X AB: LD E,RES 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // AB
    {"DD CB %02X AC: LD H,RES 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // AC
    {"DD CB %02X AD: LD L,RES 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // AD
    {"DD CB %02X AE: RES 5,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // AE
    {"DD CB %02X AF: LD A,RES 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // AF
    {"DD CB %02X B0: LD B,RES 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // B0
    {"DD CB %02X B1: LD C,RES 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // B1
    {"DD CB %02X B2: LD D,RES 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // B2
    {"DD CB %02X B3: LD E,RES 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // B3
    {"DD CB %02X B4: LD H,RES 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // B4
    {"DD CB %02X B5: LD L,RES 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // B5
    {"DD CB %02X B6: RES 6,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // B6
    {"DD CB %02X B7: LD A,RES 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // B7
    {"DD CB %02X B8: LD B,RES 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // B8
    {"DD CB %02X B9: LD C,RES 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // B9
    {"DD CB %02X BA: LD D,RES 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // BA
    {"DD CB %02X BB: LD E,RES 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // BB
    {"DD CB %02X BC: LD H,RES 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // BC
    {"DD CB %02X BD: LD L,RES 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // BD
    {"DD CB %02X BE: RES 7,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // BE
    {"DD CB %02X BF: LD A,RES 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // BF
    {"DD CB %02X C0: LD B,SET 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // C0
    {"DD CB %02X C1: LD C,SET 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // C1
    {"DD CB %02X C2: LD D,SET 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // C2
    {"DD CB %02X C3: LD E,SET 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // C3
    {"DD CB %02X C4: LD H,SET 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // C4
    {"DD CB %02X C5: LD L,SET 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // C5
    {"DD CB %02X C6: SET 0,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // C6
    {"DD CB %02X C7: LD A,SET 0,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // C7
    {"DD CB %02X C8: LD B,SET 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // C8
    {"DD CB %02X C9: LD C,SET 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // C9
    {"DD CB %02X CA: LD D,SET 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // CA
    {"DD CB %02X CB: LD E,SET 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // CB
    {"DD CB %02X CC: LD H,SET 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // CC
    {"DD CB %02X CD: LD L,SET 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // CD
    {"DD CB %02X CE: SET 1,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // CE
    {"DD CB %02X CF: LD A,SET 1,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // CF
    {"DD CB %02X D0: LD B,SET 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // D0
    {"DD CB %02X D1: LD C,SET 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // D1
    {"DD CB %02X D2: LD D,SET 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // D2
    {"DD CB %02X D3: LD E,SET 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // D3
    {"DD CB %02X D4: LD H,SET 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // D4
    {"DD CB %02X D5: LD L,SET 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // D5
    {"DD CB %02X D6: SET 2,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // D6
    {"DD CB %02X D7: LD A,SET 2,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // D7
    {"DD CB %02X D8: LD B,SET 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // D8
    {"DD CB %02X D9: LD C,SET 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // D9
    {"DD CB %02X DA: LD D,SET 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // DA
    {"DD CB %02X DB: LD E,SET 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // DB
    {"DD CB %02X DC: LD H,SET 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // DC
    {"DD CB %02X DD: LD L,SET 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // DD
    {"DD CB %02X DE: SET 3,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // DE
    {"DD CB %02X DF: LD A,SET 3,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // DF
    {"DD CB %02X E0: LD B,SET 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // E0
    {"DD CB %02X E1: LD C,SET 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // E1
    {"DD CB %02X E2: LD D,SET 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // E2
    {"DD CB %02X E3: LD E,SET 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // E3
    {"DD CB %02X E4: LD H,SET 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // E4
    {"DD CB %02X E5: LD L,SET 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // E5
    {"DD CB %02X E6: SET 4,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // E6
    {"DD CB %02X E7: LD A,SET 4,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // E7
    {"DD CB %02X E8: LD B,SET 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // E8
    {"DD CB %02X E9: LD C,SET 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // E9
    {"DD CB %02X EA: LD D,SET 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // EA
    {"DD CB %02X EB: LD E,SET 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // EB
    {"DD CB %02X EC: LD H,SET 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // EC
    {"DD CB %02X ED: LD L,SET 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // ED
    {"DD CB %02X EE: SET 5,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // EE
    {"DD CB %02X EF: LD A,SET 5,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // EF
    {"DD CB %02X F0: LD B,SET 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // F0
    {"DD CB %02X F1: LD C,SET 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // F1
    {"DD CB %02X F2: LD D,SET 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // F2
    {"DD CB %02X F3: LD E,SET 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // F3
    {"DD CB %02X F4: LD H,SET 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // F4
    {"DD CB %02X F5: LD L,SET 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // F5
    {"DD CB %02X F6: SET 6,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // F6
    {"DD CB %02X F7: LD A,SET 6,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // F7
    {"DD CB %02X F8: LD B,SET 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // F8
    {"DD CB %02X F9: LD C,SET 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // F9
    {"DD CB %02X FA: LD D,SET 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // FA
    {"DD CB %02X FB: LD E,SET 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // FB
    {"DD CB %02X FC: LD H,SET 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // FC
    {"DD CB %02X FD: LD L,SET 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // FD
    {"DD CB %02X FE: SET 7,(IX+%d)",       OpcodeInfo::ArgTypes::D},        // FE
    {"DD CB %02X FF: LD A,SET 7,(IX+%d)",  OpcodeInfo::ArgTypes::D},        // FF
}};

inline constexpr std::array<OpcodeInfo, 256> OpcodeTableFDCB = {{
    {"FD CB %02X 00: LD B,RLC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 00
    {"FD CB %02X 01: LD C,RLC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 01
    {"FD CB %02X 02: LD D,RLC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 02
    {"FD CB %02X 03: LD E,RLC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 03
    {"FD CB %02X 04: LD H,RLC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 04
    {"FD CB %02X 05: LD L,RLC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 05
    {"FD CB %02X 06: RLC (IY+%d)",         OpcodeInfo::ArgTypes::D},        // 06
    {"FD CB %02X 07: LD A,RLC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 07
    {"FD CB %02X 08: LD B,RRC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 08
    {"FD CB %02X 09: LD C,RRC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 09
    {"FD CB %02X 0A: LD D,RRC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 0A
    {"FD CB %02X 0B: LD E,RRC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 0B
    {"FD CB %02X 0C: LD H,RRC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 0C
    {"FD CB %02X 0D: LD L,RRC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 0D
    {"FD CB %02X 0E: RRC (IY+%d)",         OpcodeInfo::ArgTypes::D},        // 0E
    {"FD CB %02X 0F: LD A,RRC (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 0F
    {"FD CB %02X 10: LD B,RL (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 10
    {"FD CB %02X 11: LD C,RL (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 11
    {"FD CB %02X 12: LD D,RL (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 12
    {"FD CB %02X 13: LD E,RL (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 13
    {"FD CB %02X 14: LD H,RL (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 14
    {"FD CB %02X 15: LD L,RL (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 15
    {"FD CB %02X 16: RL (IY+%d)",          OpcodeInfo::ArgTypes::D},        // 16
    {"FD CB %02X 17: LD A,RL (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 17
    {"FD CB %02X 18: LD B,RR (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 18
    {"FD CB %02X 19: LD C,RR (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 19
    {"FD CB %02X 1A: LD D,RR (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 1A
    {"FD CB %02X 1B: LD E,RR (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 1B
    {"FD CB %02X 1C: LD H,RR (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 1C
    {"FD CB %02X 1D: LD L,RR (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 1D
    {"FD CB %02X 1E: RR (IY+%d)",          OpcodeInfo::ArgTypes::D},        // 1E
    {"FD CB %02X 1F: LD A,RR (IY+%d)",     OpcodeInfo::ArgTypes::D},        // 1F
    {"FD CB %02X 20: LD B,SLA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 20
    {"FD CB %02X 21: LD C,SLA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 21
    {"FD CB %02X 22: LD D,SLA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 22
    {"FD CB %02X 23: LD E,SLA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 23
    {"FD CB %02X 24: LD H,SLA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 24
    {"FD CB %02X 25: LD L,SLA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 25
    {"FD CB %02X 26: SLA (IY+%d)",         OpcodeInfo::ArgTypes::D},        // 26
    {"FD CB %02X 27: LD A,SLA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 27
    {"FD CB %02X 28: LD B,SRA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 28
    {"FD CB %02X 29: LD C,SRA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 29
    {"FD CB %02X 2A: LD D,SRA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 2A
    {"FD CB %02X 2B: LD E,SRA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 2B
    {"FD CB %02X 2C: LD H,SRA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 2C
    {"FD CB %02X 2D: LD L,SRA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 2D
    {"FD CB %02X 2E: SRA (IY+%d)",         OpcodeInfo::ArgTypes::D},        // 2E
    {"FD CB %02X 2F: LD A,SRA (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 2F
    {"FD CB %02X 30: LD B,SLL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 30
    {"FD CB %02X 31: LD C,SLL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 31
    {"FD CB %02X 32: LD D,SLL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 32
    {"FD CB %02X 33: LD E,SLL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 33
    {"FD CB %02X 34: LD H,SLL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 34
    {"FD CB %02X 35: LD L,SLL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 35
    {"FD CB %02X 36: SLL (IY+%d)",         OpcodeInfo::ArgTypes::D},        // 36
    {"FD CB %02X 37: LD A,SLL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 37
    {"FD CB %02X 38: LD B,SRL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 38
    {"FD CB %02X 39: LD C,SRL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 39
    {"FD CB %02X 3A: LD D,SRL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 3A
    {"FD CB %02X 3B: LD E,SRL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 3B
    {"FD CB %02X 3C: LD H,SRL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 3C
    {"FD CB %02X 3D: LD L,SRL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 3D
    {"FD CB %02X 3E: SRL (IY+%d)",         OpcodeInfo::ArgTypes::D},        // 3E
    {"FD CB %02X 3F: LD A,SRL (IY+%d)",    OpcodeInfo::ArgTypes::D},        // 3F
    {"FD CB %02X 40: BIT 0,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 40
    {"FD CB %02X 41: BIT 0,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 41
    {"FD CB %02X 42: BIT 0,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 42
    {"FD CB %02X 43: BIT 0,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 43
    {"FD CB %02X 44: BIT 0,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 44
    {"FD CB %02X 45: BIT 0,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 45
    {"FD CB %02X 46: BIT 0,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 46
    {"FD CB %02X 47: BIT 0,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 47
    {"FD CB %02X 48: BIT 1,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 48
    {"FD CB %02X 49: BIT 1,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 49
    {"FD CB %02X 4A: BIT 1,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 4A
    {"FD CB %02X 4B: BIT 1,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 4B
    {"FD CB %02X 4C: BIT 1,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 4C
    {"FD CB %02X 4D: BIT 1,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 4D
    {"FD CB %02X 4E: BIT 1,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 4E
    {"FD CB %02X 4F: BIT 1,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 4F
    {"FD CB %02X 50: BIT 2,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 50
    {"FD CB %02X 51: BIT 2,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 51
    {"FD CB %02X 52: BIT 2,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 52
    {"FD CB %02X 53: BIT 2,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 53
    {"FD CB %02X 54: BIT 2,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 54
    {"FD CB %02X 55: BIT 2,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 55
    {"FD CB %02X 56: BIT 2,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 56
    {"FD CB %02X 57: BIT 2,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 57
    {"FD CB %02X 58: BIT 3,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 58
    {"FD CB %02X 59: BIT 3,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 59
    {"FD CB %02X 5A: BIT 3,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 5A
    {"FD CB %02X 5B: BIT 3,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 5B
    {"FD CB %02X 5C: BIT 3,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 5C
    {"FD CB %02X 5D: BIT 3,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 5D
    {"FD CB %02X 5E: BIT 3,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 5E
    {"FD CB %02X 5F: BIT 3,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 5F
    {"FD CB %02X 60: BIT 4,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 60
    {"FD CB %02X 61: BIT 4,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 61
    {"FD CB %02X 62: BIT 4,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 62
    {"FD CB %02X 63: BIT 4,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 63
    {"FD CB %02X 64: BIT 4,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 64
    {"FD CB %02X 65: BIT 4,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 65
    {"FD CB %02X 66: BIT 4,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 66
    {"FD CB %02X 67: BIT 4,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 67
    {"FD CB %02X 68: BIT 5,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 68
    {"FD CB %02X 69: BIT 5,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 69
    {"FD CB %02X 6A: BIT 5,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 6A
    {"FD CB %02X 6B: BIT 5,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 6B
    {"FD CB %02X 6C: BIT 5,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 6C
    {"FD CB %02X 6D: BIT 5,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 6D
    {"FD CB %02X 6E: BIT 5,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 6E
    {"FD CB %02X 6F: BIT 5,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 6F
    {"FD CB %02X 70: BIT 6,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 70
    {"FD CB %02X 71: BIT 6,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 71
    {"FD CB %02X 72: BIT 6,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 72
    {"FD CB %02X 73: BIT 6,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 73
    {"FD CB %02X 74: BIT 6,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 74
    {"FD CB %02X 75: BIT 6,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 75
    {"FD CB %02X 76: BIT 6,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 76
    {"FD CB %02X 77: BIT 6,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 77
    {"FD CB %02X 78: BIT 7,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 78
    {"FD CB %02X 79: BIT 7,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 79
    {"FD CB %02X 7A: BIT 7,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 7A
    {"FD CB %02X 7B: BIT 7,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 7B
    {"FD CB %02X 7C: BIT 7,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 7C
    {"FD CB %02X 7D: BIT 7,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 7D
    {"FD CB %02X 7E: BIT 7,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 7E
    {"FD CB %02X 7F: BIT 7,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 7F
    {"FD CB %02X 80: LD B,RES 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 80
    {"FD CB %02X 81: LD C,RES 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 81
    {"FD CB %02X 82: LD D,RES 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 82
    {"FD CB %02X 83: LD E,RES 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 83
    {"FD CB %02X 84: LD H,RES 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 84
    {"FD CB %02X 85: LD L,RES 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 85
    {"FD CB %02X 86: RES 0,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 86
    {"FD CB %02X 87: LD A,RES 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 87
    {"FD CB %02X 88: LD B,RES 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 88
    {"FD CB %02X 89: LD C,RES 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 89
    {"FD CB %02X 8A: LD D,RES 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 8A
    {"FD CB %02X 8B: LD E,RES 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 8B
    {"FD CB %02X 8C: LD H,RES 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 8C
    {"FD CB %02X 8D: LD L,RES 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 8D
    {"FD CB %02X 8E: RES 1,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 8E
    {"FD CB %02X 8F: LD A,RES 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 8F
    {"FD CB %02X 90: LD B,RES 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 90
    {"FD CB %02X 91: LD C,RES 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 91
    {"FD CB %02X 92: LD D,RES 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 92
    {"FD CB %02X 93: LD E,RES 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 93
    {"FD CB %02X 94: LD H,RES 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 94
    {"FD CB %02X 95: LD L,RES 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 95
    {"FD CB %02X 96: RES 2,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 96
    {"FD CB %02X 97: LD A,RES 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 97
    {"FD CB %02X 98: LD B,RES 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 98
    {"FD CB %02X 99: LD C,RES 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 99
    {"FD CB %02X 9A: LD D,RES 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 9A
    {"FD CB %02X 9B: LD E,RES 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 9B
    {"FD CB %02X 9C: LD H,RES 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 9C
    {"FD CB %02X 9D: LD L,RES 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 9D
    {"FD CB %02X 9E: RES 3,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // 9E
    {"FD CB %02X 9F: LD A,RES 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // 9F
    {"FD CB %02X A0: LD B,RES 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // A0
    {"FD CB %02X A1: LD C,RES 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // A1
    {"FD CB %02X A2: LD D,RES 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // A2
    {"FD CB %02X A3: LD E,RES 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // A3
    {"FD CB %02X A4: LD H,RES 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // A4
    {"FD CB %02X A5: LD L,RES 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // A5
    {"FD CB %02X A6: RES 4,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // A6
    {"FD CB %02X A7: LD A,RES 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // A7
    {"FD CB %02X A8: LD B,RES 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // A8
    {"FD CB %02X A9: LD C,RES 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // A9
    {"FD CB %02X AA: LD D,RES 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // AA
    {"FD CB %02X AB: LD E,RES 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // AB
    {"FD CB %02X AC: LD H,RES 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // AC
    {"FD CB %02X AD: LD L,RES 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // AD
    {"FD CB %02X AE: RES 5,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // AE
    {"FD CB %02X AF: LD A,RES 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // AF
    {"FD CB %02X B0: LD B,RES 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // B0
    {"FD CB %02X B1: LD C,RES 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // B1
    {"FD CB %02X B2: LD D,RES 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // B2
    {"FD CB %02X B3: LD E,RES 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // B3
    {"FD CB %02X B4: LD H,RES 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // B4
    {"FD CB %02X B5: LD L,RES 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // B5
    {"FD CB %02X B6: RES 6,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // B6
    {"FD CB %02X B7: LD A,RES 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // B7
    {"FD CB %02X B8: LD B,RES 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // B8
    {"FD CB %02X B9: LD C,RES 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // B9
    {"FD CB %02X BA: LD D,RES 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // BA
    {"FD CB %02X BB: LD E,RES 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // BB
    {"FD CB %02X BC: LD H,RES 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // BC
    {"FD CB %02X BD: LD L,RES 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // BD
    {"FD CB %02X BE: RES 7,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // BE
    {"FD CB %02X BF: LD A,RES 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // BF
    {"FD CB %02X C0: LD B,SET 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // C0
    {"FD CB %02X C1: LD C,SET 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // C1
    {"FD CB %02X C2: LD D,SET 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // C2
    {"FD CB %02X C3: LD E,SET 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // C3
    {"FD CB %02X C4: LD H,SET 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // C4
    {"FD CB %02X C5: LD L,SET 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // C5
    {"FD CB %02X C6: SET 0,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // C6
    {"FD CB %02X C7: LD A,SET 0,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // C7
    {"FD CB %02X C8: LD B,SET 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // C8
    {"FD CB %02X C9: LD C,SET 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // C9
    {"FD CB %02X CA: LD D,SET 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // CA
    {"FD CB %02X CB: LD E,SET 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // CB
    {"FD CB %02X CC: LD H,SET 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // CC
    {"FD CB %02X CD: LD L,SET 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // CD
    {"FD CB %02X CE: SET 1,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // CE
    {"FD CB %02X CF: LD A,SET 1,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // CF
    {"FD CB %02X D0: LD B,SET 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // D0
    {"FD CB %02X D1: LD C,SET 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // D1
    {"FD CB %02X D2: LD D,SET 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // D2
    {"FD CB %02X D3: LD E,SET 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // D3
    {"FD CB %02X D4: LD H,SET 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // D4
    {"FD CB %02X D5: LD L,SET 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // D5
    {"FD CB %02X D6: SET 2,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // D6
    {"FD CB %02X D7: LD A,SET 2,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // D7
    {"FD CB %02X D8: LD B,SET 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // D8
    {"FD CB %02X D9: LD C,SET 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // D9
    {"FD CB %02X DA: LD D,SET 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // DA
    {"FD CB %02X DB: LD E,SET 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // DB
    {"FD CB %02X DC: LD H,SET 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // DC
    {"FD CB %02X DD: LD L,SET 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // DD
    {"FD CB %02X DE: SET 3,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // DE
    {"FD CB %02X DF: LD A,SET 3,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // DF
    {"FD CB %02X E0: LD B,SET 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // E0
    {"FD CB %02X E1: LD C,SET 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // E1
    {"FD CB %02X E2: LD D,SET 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // E2
    {"FD CB %02X E3: LD E,SET 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // E3
    {"FD CB %02X E4: LD H,SET 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // E4
    {"FD CB %02X E5: LD L,SET 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // E5
    {"FD CB %02X E6: SET 4,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // E6
    {"FD CB %02X E7: LD A,SET 4,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // E7
    {"FD CB %02X E8: LD B,SET 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // E8
    {"FD CB %02X E9: LD C,SET 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // E9
    {"FD CB %02X EA: LD D,SET 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // EA
    {"FD CB %02X EB: LD E,SET 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // EB
    {"FD CB %02X EC: LD H,SET 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // EC
    {"FD CB %02X ED: LD L,SET 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // ED
    {"FD CB %02X EE: SET 5,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // EE
    {"FD CB %02X EF: LD A,SET 5,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // EF
    {"FD CB %02X F0: LD B,SET 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // F0
    {"FD CB %02X F1: LD C,SET 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // F1
    {"FD CB %02X F2: LD D,SET 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // F2
    {"FD CB %02X F3: LD E,SET 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // F3
    {"FD CB %02X F4: LD H,SET 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // F4
    {"FD CB %02X F5: LD L,SET 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // F5
    {"FD CB %02X F6: SET 6,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // F6
    {"FD CB %02X F7: LD A,SET 6,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // F7
    {"FD CB %02X F8: LD B,SET 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // F8
    {"FD CB %02X F9: LD C,SET 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // F9
    {"FD CB %02X FA: LD D,SET 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // FA
    {"FD CB %02X FB: LD E,SET 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // FB
    {"FD CB %02X FC: LD H,SET 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // FC
    {"FD CB %02X FD: LD L,SET 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // FD
    {"FD CB %02X FE: SET 7,(IY+%d)",       OpcodeInfo::ArgTypes::D},        // FE
    {"FD CB %02X FF: LD A,SET 7,(IY+%d)",  OpcodeInfo::ArgTypes::D},        // FF
}};


}


#endif

