#include "opcodes.h"

//All opcode functions return cycles;

// LDA immediate (0xA9) - Load accumulator with immediate value
int op_lda_immediate(CPU *cpu, uint8_t *mem)
{
    uint8_t operand = mem[cpu->PC++];
    cpu->A = operand;
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) ? 1 : 0;
    return 2;
}

// LDA zero page (0xA5) - Load accumulator from zero page memory
int op_lda_zero_page(CPU *cpu, uint8_t *mem)
{
    uint8_t address = mem[cpu->PC++];
    cpu->A = mem[address];
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) ? 1 : 0;
    return 3;
}

// LDA absolute (0xAD) - Load accumulator from a full 16-bit memory address
int op_lda_absolute(CPU *cpu, uint8_t *mem)
{
    uint8_t lo = mem[cpu->PC++];
    uint8_t hi = mem[cpu->PC++];
    uint16_t address = (uint16_t)(hi << 8) | lo;
    cpu->A = mem[address];
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) ? 1 : 0;
    return 4;
}

// LDA zero page x (0xB5) - Adds x register to base address
int op_lda_zero_page_x(CPU *cpu, uint8_t *mem)
{
    uint8_t address = mem[cpu->PC++];
    cpu->A = mem[(uint8_t)(address + cpu->X)]; //cast as uint8_t to maintain 8 bits and keep zero page.
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) ? 1 : 0;
    return 4;
}

// LDA absolute x (0xBD) - Adds x register to a full 16-bit memory address
int op_lda_absolute_x(CPU *cpu, uint8_t *mem)
{
    uint8_t lo = mem[cpu->PC++];
    uint8_t hi = mem[cpu->PC++];
    uint16_t address = (uint16_t)(hi << 8) | lo;
    uint16_t effective_address = (uint16_t)(address + cpu->X);
    cpu->A = mem[effective_address];
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) ? 1 : 0;
    int page_crossed = (address & 0xFF00) != (effective_address & 0xFF00);
    return page_crossed ? 5 : 4;
}

// LDA absolute Y (0xB9) - Adds Y register to a full 16-bit memory address
int op_lda_absolute_y(CPU *cpu, uint8_t *mem)
{
    uint8_t lo = mem[cpu->PC++];
    uint8_t hi = mem[cpu->PC++];
    uint16_t address = (uint16_t)(hi << 8) | lo;
    uint16_t effective_address = (uint16_t)(address + cpu->Y);
    cpu->A = mem[effective_address];
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) ? 1 : 0;
    int page_crossed = (address & 0xFF00) != (effective_address & 0xFF00);
    return page_crossed ? 5 : 4;
}

// STA zero page (0x85) - Store accumulator to zero page memory
int op_sta_zero_page(CPU *cpu, uint8_t *mem)
{
    uint8_t address = mem[cpu->PC++];
    mem[address] = cpu->A;
    return 3;
}

// STA zero page X (0x95)
int op_sta_zero_page_x(CPU *cpu, uint8_t *mem)
{
    uint8_t address = mem[cpu->PC++];
    mem[(uint8_t)(address + cpu->X)] = cpu->A; //cast as uint8_t to maintain 8 bits and keep zero page.
    return 4;
}

// STA absolute (0x8D) - Store accumulator to a full 16-bit memory address
int op_sta_absolute(CPU *cpu, uint8_t *mem)
{
    uint8_t lo = mem[cpu->PC++];
    uint8_t hi = mem[cpu->PC++];
    uint16_t address = (uint16_t)(hi << 8) | lo;
    mem[address] = cpu->A;
    return 4;
}

// STA absolute X (0x9D) - Store accumulator to a full 16-bit address offset by X
int op_sta_absolute_x(CPU *cpu, uint8_t *mem)
{
    uint8_t lo = mem[cpu->PC++];
    uint8_t hi = mem[cpu->PC++];
    uint16_t address = (uint16_t)(hi << 8) | lo;
    uint16_t effective_address = (uint16_t)(address + cpu->X);
    mem[effective_address] = cpu->A;
    return 5;
}

// STA absolute Y (0x99) - Store accumulator to a full 16-bit address offset by Y
int op_sta_absolute_y(CPU *cpu, uint8_t *mem)
{
    uint8_t lo = mem[cpu->PC++];
    uint8_t hi = mem[cpu->PC++];
    uint16_t address = (uint16_t)(hi << 8) | lo;
    uint16_t effective_address = (uint16_t)(address + cpu->Y);
    mem[effective_address] = cpu->A;
    return 5;
}

//STA indirect X (0x81) -  Store accumulator to address pointed to by zero page pointer offset by X
int op_sta_indirect_x(CPU *cpu, uint8_t *mem)
{
    uint8_t operand = mem[cpu->PC++]; //step 1
    uint8_t zp_index = (uint8_t)(operand + cpu->X); //step2
    uint8_t lo = mem[zp_index];
    uint8_t hi = mem[(uint8_t)(zp_index + 1)];
    uint16_t address = (uint16_t)(hi << 8) | lo;
    mem[address] = cpu->A;
    return 6;
}

//STA indirect Y (0x(91) -  Store accumulator to address pointed to by zero page pointer offset by Y
int op_sta_indirect_y(CPU *cpu, uint8_t *mem)
{
    uint8_t operand = mem[cpu->PC++]; //step 1
    uint8_t lo = mem[operand];
    uint8_t hi = mem[(uint8_t)(operand + 1)];
    uint16_t address = ((uint16_t)(hi << 8) | lo) + cpu->Y;
    mem[address] = cpu->A;
    return 6;
}

// LDX immediate (0xA2) - Load X register with immediate value
int op_ldx_immediate(CPU *cpu, uint8_t *mem)
{
    uint8_t operand = mem[cpu->PC++];
    cpu->X = operand;
    cpu->Z = (cpu->X == 0);
    cpu->N = (cpu->X & 0x80) ? 1 : 0;
    return 2;
}

//LDX zero page (0xA6) - Load X register from zero page memory
int op_ldx_zero_page(CPU *cpu, uint8_t *mem)
{
    uint8_t address = mem[cpu->PC++];
    cpu->X = mem[address];
    cpu->Z = (cpu->X == 0);
    cpu->N = (cpu->X & 0x80) ? 1 : 0;
    return 3;
}

// LDX zero page Y (0xB6) - Adds Y register to base address
int op_ldx_zero_page_y(CPU *cpu, uint8_t *mem)
{
    uint8_t address = mem[cpu->PC++];
    cpu->X = mem[(uint8_t)(address + cpu->Y)]; //cast as uint8_t to maintain 8 bits and keep zero page.
    cpu->Z = (cpu->X == 0);
    cpu->N = (cpu->X & 0x80) ? 1 : 0;
    return 4;
}

// LDX absolute - (0xAE) - Load X register from a full 16-bit memory address
int op_ldx_absolute(CPU *cpu, uint8_t *mem)
{
    uint8_t lo = mem[cpu->PC++];
    uint8_t hi = mem[cpu->PC++];
    uint16_t address = (uint16_t)(hi << 8) | lo;
    cpu->X = mem[address];
    cpu->Z = (cpu->X == 0);
    cpu->N = (cpu->X & 0x80) ? 1 : 0;
    return 4;
}

// LDX absolute Y (0xBE) - Adds Y register to a full 16-bit memory address in X
int op_ldx_absolute_y(CPU *cpu, uint8_t *mem)
{
    uint8_t lo = mem[cpu->PC++];
    uint8_t hi = mem[cpu->PC++];
    uint16_t address = (uint16_t)(hi << 8) | lo;
    uint16_t effective_address = (uint16_t)(address + cpu->Y);
    cpu->X = mem[effective_address];
    cpu->Z = (cpu->X == 0);
    cpu->N = (cpu->X & 0x80) ? 1 : 0;
    int page_crossed = (address & 0xFF00) != (effective_address & 0xFF00);
    return page_crossed ? 5 : 4;
}

// LDY immediate (0xA0) - Load Y register with immediate value
int op_ldy_immediate(CPU *cpu, uint8_t *mem)
{
    uint8_t operand = mem[cpu->PC++];
    cpu->Y = operand;
    cpu->Z = (cpu->Y == 0);
    cpu->N = (cpu->Y & 0x80) ? 1 : 0;
    return 2;
}

// LDY zero page (0xA4) - Load Y register from zero page memory
int op_ldy_zero_page(CPU *cpu, uint8_t *mem)
{
    uint8_t address = mem[cpu->PC++];
    cpu->Y = mem[address];
    cpu->Z = (cpu->Y == 0);
    cpu->N = (cpu->Y & 0x80) ? 1 : 0;
    return 3;
}

// LDY zero page X (0xB4) - Adds X register to base address
int op_ldy_zero_page_x(CPU *cpu, uint8_t *mem)
{
    uint8_t address = mem[cpu->PC++];
    cpu->Y = mem[(uint8_t)(address + cpu->X)]; //cast as uint8_t to maintain 8 bits and keep zero page.
    cpu->Z = (cpu->Y == 0);
    cpu->N = (cpu->Y & 0x80) ? 1 : 0;
    return 4;
}

// LDY absolute (0xAC) - Load Y register from a full 16-bit memory address
int op_ldy_absolute(CPU *cpu, uint8_t *mem)
{
    uint8_t lo = mem[cpu->PC++];
    uint8_t hi = mem[cpu->PC++];
    uint16_t address = (uint16_t)(hi << 8) | lo;
    cpu->Y = mem[address];
    cpu->Z = (cpu->Y == 0);
    cpu->N = (cpu->Y & 0x80) ? 1 : 0;
    return 4;
}

// LDY absolute X (0xBC) - Adds X register to a full 16-bit memory address in Y
int op_ldy_absolute_x(CPU *cpu, uint8_t *mem)
{
    uint8_t lo = mem[cpu->PC++];
    uint8_t hi = mem[cpu->PC++];
    uint16_t address = (uint16_t)(hi << 8) | lo;
    uint16_t effective_address = (uint16_t)(address + cpu->X);
    cpu->Y = mem[effective_address];
    cpu->Z = (cpu->Y == 0);
    cpu->N = (cpu->Y & 0x80) ? 1 : 0;
    int page_crossed = (address & 0xFF00) != (effective_address & 0xFF00);
    return page_crossed ? 5 : 4;
}

// STX zero page (0x86) - Store X register to zero page memory
int op_stx_zero_page(CPU *cpu, uint8_t *mem)
{
    uint8_t address = mem[cpu->PC++];
    mem[address] = cpu->X;
    return 3;
}

// STX zero page Y (0x96) - Y register stores X
int op_stx_zero_page_y(CPU *cpu, uint8_t *mem)
{
    uint8_t address = mem[cpu->PC++];
    mem[(uint8_t)(address + cpu->Y)] = cpu->X; //cast as uint8_t to maintain 8 bits and keep zero page.
    return 4;
}

// STX absolute (0x8E) - Store X register to a full 16-bit memory address
int op_stx_absolute(CPU *cpu, uint8_t *mem)
{
    uint8_t lo = mem[cpu->PC++];
    uint8_t hi = mem[cpu->PC++];
    uint16_t address = (uint16_t)(hi << 8) | lo;
    mem[address] = cpu->X;
    return 4;
}

// STY zero page (0x84) - Store Y register to zero page memory
int op_sty_zero_page(CPU *cpu, uint8_t *mem)
{
    uint8_t address = mem[cpu->PC++];
    mem[address] = cpu->Y;
    return 3;
}

// STY zero page X (0x94) - X register stores Y
int op_sty_zero_page_x(CPU *cpu, uint8_t *mem)
{
    uint8_t address = mem[cpu->PC++];
    mem[(uint8_t)(address + cpu->X)] = cpu->Y; //cast as uint8_t to maintain 8 bits and keep zero page.
    return 4;
}

// STY absolute (0x8C) - Store Y register to a full 16-bit memory address
int op_sty_absolute(CPU *cpu, uint8_t *mem)
{
    uint8_t lo = mem[cpu->PC++];
    uint8_t hi = mem[cpu->PC++];
    uint16_t address = (uint16_t)(hi << 8) | lo;
    mem[address] = cpu->Y;
    return 4;
}

// TAX implied (0xAA) - Transfer accumulator to X
int op_tax_implied(CPU *cpu, uint8_t *mem)
{
    (void)mem;
    cpu->X = cpu->A;
    cpu->Z = (cpu->X == 0);
    cpu->N = (cpu->X & 0x80) ? 1 : 0;
    return 2;
}

// TAY implied (0xA8) - Transfer accumulator to Y
int op_tay_implied(CPU *cpu, uint8_t *mem)
{
    (void)mem;
    cpu->Y = cpu->A;
    cpu->Z = (cpu->Y == 0);
    cpu->N = (cpu->Y & 0x80) ? 1 : 0;
    return 2;
}

// TXA implied (0x8A) - Transfer X to accumulator
int op_txa_implied(CPU *cpu, uint8_t *mem)
{
    (void)mem;
    cpu->A = cpu->X;
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) ? 1 : 0;
    return 2;
}

// TYA implied (0x98) - Transfer Y to accumulator
int op_tya_implied(CPU *cpu, uint8_t *mem)
{
    (void)mem;
    cpu->A = cpu->Y;
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) ? 1 : 0;
    return 2;
}

// TSX implied (0xBA) - Transfer Stack Pointer to X
int op_tsx_implied(CPU *cpu, uint8_t *mem)
{
    (void)mem;
    cpu->X = cpu->SP;
    cpu->Z = (cpu->X == 0);
    cpu->N = (cpu->X & 0x80) ? 1 : 0;
    return 2;
}

// TXS implied (0x9A) - Transfer X to Stack Pointer
int op_txs_implied(CPU *cpu, uint8_t *mem)
{
    (void)mem;
    cpu->SP = cpu->X;
    return 2;
}

// PHA implied (0x48) - Push value in accumulator onto the stack
int op_pha_implied(CPU *cpu, uint8_t *mem)
{
    mem[0x0100 + cpu->SP] = cpu->A;
    cpu->SP --;
    return 3;
}

// PLA implied (0x68) - Pull value from the stack and store it into the accumulator
int op_pla_implied(CPU *cpu, uint8_t *mem)
{
    cpu->SP ++;
    cpu->A = mem[0x0100 + cpu->SP];
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) ? 1 : 0;
    return 4;
}
// Default handler for unimplemented opcodes
int op_unimplemented(CPU *cpu, uint8_t *mem)
{
    (void)cpu;
    (void)mem;  // Suppress unused parameter warnings
    return 1;
}

// 256-entry lookup table indexed by opcode
// Using designated initializers - all unmentioned entries default to 0 (null handler)
const OpcodeEntry opcode_table[256] = {
    [0xA9] = { op_lda_immediate,   "LDA immediate"   },
    [0xA5] = { op_lda_zero_page,   "LDA zero page"   },
    [0xAD] = { op_lda_absolute,    "LDA absolute"    },
    [0xB5] = { op_lda_zero_page_x, "LDA zero page X" },
    [0xBD] = { op_lda_absolute_x,  "LDA absolute X"  },
    [0xB9] = { op_lda_absolute_y,  "LDA absolute Y"  },
    [0x85] = { op_sta_zero_page,   "STA zero page"   },
    [0x95] = { op_sta_zero_page_x, "STA zero page X" },
    [0x8D] = { op_sta_absolute,    "STA absolute"    },
    [0x9D] = { op_sta_absolute_x,  "STA absolute X " },
    [0x99] = { op_sta_absolute_y,  "STA absolute Y " },
    [0x81] = { op_sta_indirect_x,  "STA indirect X"  },
    [0x91] = { op_sta_indirect_y,  "STA indirect Y"  },
    [0xA2] = { op_ldx_immediate,   "LDX immediate"   },
    [0xA6] = { op_ldx_zero_page,   "LDX zero page"   },
    [0xB6] = { op_ldx_zero_page_y, "LDX zero page Y" },
    [0xAE] = { op_ldx_absolute,    "LDX absolute"    },
    [0xBE] = { op_ldx_absolute_y,  "LDX absolute Y"  },
    [0xA0] = { op_ldy_immediate,   "LDY immediate"   },
    [0xA4] = { op_ldy_zero_page,   "LDY zero page"   },
    [0xB4] = { op_ldy_zero_page_x, "LDY zero page X" },
    [0xAC] = { op_ldy_absolute,    "LDY absolute"    },
    [0xBC] = { op_ldy_absolute_x,  "LDY absolute X"  },
    [0x86] = { op_stx_zero_page,   "STX zero page"   },
    [0x96] = { op_stx_zero_page_y, "STX zero page Y" },
    [0x8E] = { op_stx_absolute,    "STX absolute"    },
    [0x84] = { op_sty_zero_page,   "STY zero page"   },
    [0x94] = { op_sty_zero_page_x, "STY zero page X" },
    [0x8C] = { op_sty_absolute,    "STY absolute"    },
    [0xAA] = { op_tax_implied,     "TAX implied"     },
    [0xA8] = { op_tay_implied,     "TAY implied"     },
    [0x8A] = { op_txa_implied,     "TXA implied"     },
    [0x98] = { op_tya_implied,     "TYA implied"     },
    [0xBA] = { op_tsx_implied,     "TSX implied"     },
    [0x9A] = { op_txs_implied,     "TXS implied"     },
    [0x48] = { op_pha_implied,     "PHA implied"     },
    [0x68] = { op_pla_implied,     "PLA implied"     }
};
