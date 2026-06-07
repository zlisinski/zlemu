#!/usr/bin/env python3

import json
import re
import sys
from pathlib import Path


def get_cycles(prefix: str, opcode: int) -> int:
    """
    Return the minimum cycle count found in the test JSON file.
    If the file does not exist, return 4.
    """

    if prefix == "":
        filename = f"{opcode:02x}.json"
    elif prefix == "CB ":
        filename = f"cb {opcode:02x}.json"
    elif prefix == "DD ":
        filename = f"dd {opcode:02x}.json"
    elif prefix == "ED ":
        filename = f"ed {opcode:02x}.json"
    elif prefix == "FD ":
        filename = f"fd {opcode:02x}.json"
    elif prefix == "DD CB ":
        filename = f"dd cb __ {opcode:02x}.json"
    elif prefix == "FD CB ":
        filename = f"fd cb __ {opcode:02x}.json"
    else:
        return 4

    path = Path(__file__).parent / "../../test_data/z80/v1" / filename

    if not path.exists():
        return 4

    with open(path) as f:
        data = json.load(f)

    min_cycles = None

    for test in data:
        cycle_count = len(test["cycles"])

        if min_cycles is None or cycle_count < min_cycles:
            min_cycles = cycle_count

    return min_cycles if min_cycles is not None else 4


def clean_instr(s: str) -> str:
    s = re.sub(r'^[+*]', '', s)      # remove markers
    s = re.sub(r'\s+', ' ', s)      # normalize whitespace
    return s.strip()


def emit_table(prefix, data):
    print(f"inline constexpr std::array<OpcodeInfo, 256> OpcodeTable{prefix.replace(' ', '')} = {{{{")
    for i, s in enumerate(data):
        if s is None:
            s = ""

        argType = "OpcodeInfo::ArgTypes::None,"
        if "nn" in s:
            argType = "OpcodeInfo::ArgTypes::NN,"
            s = s.replace("nn", "%04X")
            s = f"{prefix}{i:02X} %02X %02X: " + s
        elif "n" in s and "d" in s:
            argType = "OpcodeInfo::ArgTypes::DN,"
            s = s.replace("d", "%d").replace("n", "%02X")
            s = f"{prefix}{i:02X} %02X %02X: " + s
        elif "n" in s:
            argType = "OpcodeInfo::ArgTypes::N,"
            s = s.replace("n", "%02X")
            s = f"{prefix}{i:02X} %02X: " + s
        elif "d" in s:
            argType = "OpcodeInfo::ArgTypes::D,"
            s = s.replace("d", "%d")
            if prefix == "DD CB " or prefix == "FD CB ":
                s = f"{prefix}%02X {i:02X}: " + s
            else:
                s = f"{prefix}{i:02X} %02X: " + s
        else:
            s = f"{prefix}{i:02X}: " + s

        s = f'"{s}",'

        cycles = get_cycles(prefix, i)

        print(f'    {{{s:<37}{argType:<28}{cycles:<2}}}, // {i:02X}')
    print("}};\n")


tables = {
    "normal": [None] * 256,
    "dd":     [None] * 256,
    "cb":     [None] * 256,
    "ed":     [None] * 256,
    "fd":     [None] * 256,
    "ddcb":   [None] * 256,
    "fdcb":   [None] * 256,
}

with open(Path(__file__).parent / "z80inst2.txt") as f:
    for line in f:
        if not line.startswith("|["):
            continue

        parts = [p.strip() for p in line.strip().split("|")]

        # Extract hex value
        m = re.search(r'\[\s*([0-9A-Fa-f]{2})', parts[1])
        if not m:
            continue
        h = int(m.group(1), 16)

        cols = [clean_instr(c) for c in parts[3:8]]

        tables["normal"][h] = cols[0]
        tables["dd"][h]     = cols[1]
        tables["cb"][h]     = cols[2]
        tables["ed"][h]     = cols[3]
        tables["fd"][h]     = cols[1].replace("IX", "IY")
        tables["ddcb"][h]   = cols[4]
        tables["fdcb"][h]   = cols[4].replace("IX", "IY")


print("""#ifndef ZLEMU_CORE_SMS_Z80OPCODES_H
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
    uint8_t cycles;
};

""")

emit_table("",        tables["normal"])
emit_table("CB ",     tables["cb"])
emit_table("DD ",     tables["dd"])
emit_table("ED ",     tables["ed"])
emit_table("FD ",     tables["fd"])
emit_table("DD CB ",   tables["ddcb"])
emit_table("FD CB ",   tables["fdcb"])

print("""
}


#endif
""")