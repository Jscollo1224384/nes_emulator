#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct {
    uint8_t  A, X, Y, SP;
    uint16_t PC;
    // Status flags
    uint8_t N, V, B, D, I, Z, C;
    uint64_t cycles;
} CPU;

void cpu_reset(CPU *cpu, uint8_t *mem);
int  cpu_step(CPU *cpu, const uint8_t *mem);   // returns cycles consumed

#endif
