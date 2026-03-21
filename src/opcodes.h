#ifndef OPCODES_H
#define OPCODES_H

#include "cpu.h"
#include <stdint.h>

// Opcode handler function pointer type
typedef int (*OpcodeHandler)(CPU *cpu, uint8_t *mem, uint8_t operand);

// Struct to hold handler + metadata
typedef struct {
    OpcodeHandler handler;
    uint8_t cycles;           // Base cycle count
    uint8_t bytes;            // Instruction length (bytes)
    const char *name;         // For debugging
} OpcodeEntry;

// 256-entry lookup table indexed by opcode
extern const OpcodeEntry opcode_table[256];

// Individual opcode handlers
int op_lda_immediate(CPU *cpu, uint8_t *mem, uint8_t operand);
int op_lda_zero_page(CPU *cpu, uint8_t *mem, uint8_t operand);
int op_sta_zero_page(CPU *cpu, uint8_t *mem, uint8_t operand);

// Default handler for unimplemented opcodes
int op_unimplemented(CPU *cpu, uint8_t *mem, uint8_t operand);

#endif
