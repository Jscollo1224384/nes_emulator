#ifndef OPCODES_H
#define OPCODES_H

#include "cpu.h"
#include <stdint.h>

// Opcode handler function pointer type
typedef int (*OpcodeHandler)(CPU *cpu, uint8_t *mem);

// Struct to hold handler + metadata
typedef struct {
    OpcodeHandler handler;
    const char *name;         // For debugging
} OpcodeEntry;

// 256-entry lookup table indexed by opcode
extern const OpcodeEntry opcode_table[256];

// Individual opcode handlers
int op_lda_immediate(CPU *cpu, uint8_t *mem);
int op_lda_zero_page(CPU *cpu, uint8_t *mem);
int op_lda_zero_page_x(CPU *cpu, uint8_t *mem);
int op_lda_absolute_x(CPU *cpu, uint8_t *mem);
int op_lda_absolute_y(CPU *cpu, uint8_t *mem);
int op_sta_zero_page(CPU *cpu, uint8_t *mem);
int op_sta_zero_page_x(CPU *cpu, uint8_t *mem);
int op_sta_absolute(CPU *cpu, uint8_t *mem);
int op_sta_absolute_x(CPU *cpu, uint8_t *mem);
int op_sta_absolute_y(CPU *cpu, uint8_t *mem);
int op_sta_indirect_x(CPU *cpu, uint8_t *mem);
int op_sta_indirect_y(CPU *cpu, uint8_t *mem);
int op_ldx_immediate(CPU *cpu, uint8_t *mem);
int op_ldx_zero_page(CPU *cpu, uint8_t *mem);
int op_ldx_zero_page_y(CPU *cpu, uint8_t *mem);
int op_ldx_absolute(CPU *cpu, uint8_t *mem);
int op_ldx_absolute_y(CPU *cpu, uint8_t *mem);
int op_ldy_immediate(CPU *cpu, uint8_t *mem);
int op_ldy_zero_page(CPU *cpu, uint8_t *mem);
int op_ldy_zero_page_x(CPU *cpu, uint8_t *mem);
int op_ldy_absolute(CPU *cpu, uint8_t *mem);
int op_ldy_absolute_x(CPU *cpu, uint8_t *mem);
int op_stx_zero_page(CPU *cpu, uint8_t *mem);
int op_stx_zero_page_y(CPU *cpu, uint8_t *mem);
int op_stx_absolute(CPU *cpu, uint8_t *mem);
int op_sty_zero_page(CPU *cpu, uint8_t *mem);
int op_sty_zero_page_x(CPU *cpu, uint8_t *mem);
int op_sty_absolute(CPU *cpu, uint8_t *mem);
int op_tax_implied(CPU *cpu, uint8_t *mem);
int op_tay_implied(CPU *cpu, uint8_t *mem);
int op_txa_implied(CPU *cpu, uint8_t *mem);
int op_tya_implied(CPU *cpu, uint8_t *mem);



// Default handler for unimplemented opcodes
int op_unimplemented(CPU *cpu, uint8_t *mem);

#endif
