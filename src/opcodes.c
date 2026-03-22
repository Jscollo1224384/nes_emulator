#include "opcodes.h"

// LDA immediate (0xA9) - Load accumulator with immediate value
int op_lda_immediate(CPU *cpu, uint8_t *mem) {
    uint8_t operand = mem[cpu->PC++];
    cpu->A = operand;
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) ? 1 : 0;
    return 2;  // 2 cycles
}

// LDA zero page (0xA5) - Load accumulator from zero page memory
int op_lda_zero_page(CPU *cpu, uint8_t *mem) {
    uint8_t address = mem[cpu->PC++];
    cpu->A = mem[address];
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) ? 1 : 0;
    return 3;  // 3 cycles
}

// STA zero page (0x85) - Store accumulator to zero page memory
int op_sta_zero_page(CPU *cpu, uint8_t *mem) {
    uint8_t address = mem[cpu->PC++];
    mem[address] = cpu->A;
    return 3;  // 3 cycles
}

// Default handler for unimplemented opcodes
int op_unimplemented(CPU *cpu, uint8_t *mem) {
    (void)cpu;
    (void)mem;  // Suppress unused parameter warnings
    return 1;  // Return 1 cycle as placeholder
}

// 256-entry lookup table indexed by opcode
// Using designated initializers - all unmentioned entries default to 0 (null handler)
const OpcodeEntry opcode_table[256] = {
    [0xA9] = { op_lda_immediate, "LDA immediate" },
    [0xA5] = { op_lda_zero_page, "LDA zero page" },
    [0x85] = { op_sta_zero_page, "STA zero page" },
};
