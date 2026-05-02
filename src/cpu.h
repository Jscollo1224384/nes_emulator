#ifndef CPU_H
#define CPU_H

#include <stdint.h>

// Status flag bit positions (6502 standard)
#define FLAG_N (1 << 7)  // Negative
#define FLAG_V (1 << 6)  // Overflow
#define FLAG_B (1 << 4)  // Break
#define FLAG_D (1 << 3)  // Decimal (unused in NES)
#define FLAG_I (1 << 2)  // Interrupt disable
#define FLAG_Z (1 << 1)  // Zero
#define FLAG_C (1 << 0)  // Carry


typedef struct {
    uint8_t  A, X, Y, SP;
    uint16_t PC;
    // Status flags
    uint8_t N, V, B, D, I, Z, C;
    uint8_t P;
    uint64_t cycles;
} CPU;

void cpu_reset(CPU *cpu, uint8_t *mem);
int  cpu_step(CPU *cpu, uint8_t *mem);   // returns cycles consumed

#endif
