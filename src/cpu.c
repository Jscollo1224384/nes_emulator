#include "cpu.h"

// Reset CPU to initial state
void cpu_reset(CPU *cpu, uint8_t *mem) {
    cpu->A = 0;
    cpu->X = 0;
    cpu->Y = 0;
    cpu->SP = 0xFD;  // Stack pointer starts at 0xFD
    cpu->PC = mem[0xFFFC] | (mem[0xFFFD] << 8);  // Load PC from reset vector
    cpu->N = 0;
    cpu->V = 0;
    cpu->B = 0;
    cpu->D = 0;
    cpu->I = 1;  // Interrupt disable flag set on reset
    cpu->Z = 0;
    cpu->C = 0;
    cpu->cycles = 0;
}

// Execute one CPU instruction, return cycles consumed
int cpu_step(CPU *cpu, const uint8_t *mem)
{
    uint8_t opcode = mem[cpu->PC++];
    uint8_t operand = mem[cpu->PC++];

    switch (opcode) {
        case 0xA9:  // LDA immediate
            cpu->A = operand;
            cpu->Z = (cpu->A == 0);
            cpu->N = (cpu->A & 0x80) ? 1 : 0;
            return 2;  // 2 cycles

        default:
            // For now, just return 1 cycle for unimplemented opcodes
            return 1;
    }
}
