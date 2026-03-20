#include "cpu.h"

// Reset CPU to initial state
void cpu_reset(CPU *cpu, uint8_t *mem) {
    //Registers
    cpu->A      = 0;                                    // Accumulator (Arithmetic and logic)
    cpu->X      = 0;                                    // Index Register (counting, offsets, loops))
    cpu->Y      = 0;                                    // Index Register (counting, offsets, loops))
    cpu->SP     = 0xFD;                                 // Stack pointer starts at 0xFD
    cpu->PC     = mem[0xFFFC] | (mem[0xFFFD] << 8);     // program counter
    //Status flags
    cpu->N      = 0;                                    // Negative flag is set when bit 7 (sign bit) is set.
    cpu->V      = 0;                                    // Set when there is signed overflow.
    cpu->B      = 0;                                    // Break flag — set when BRK instruction is executed, rarely used in game mode, mainly used for debug.
    cpu->D      = 0;                                    // Decimal (The NES's version of the 6502 did not have a decimal flag. This will not be used.)
    cpu->I      = 1;                                    // Interrupt disable flag set on reset
    cpu->Z      = 0;                                    // Set when the result of an operation is 0
    cpu->C      = 0;
    cpu->cycles = 0;
}

// Execute one CPU instruction, return cycles consumed
int cpu_step(CPU *cpu, uint8_t *mem)
{
    uint8_t opcode = mem[cpu->PC++];
    uint8_t operand = mem[cpu->PC++];

    switch (opcode){
        case 0xA9:  // LDA immediate
            cpu->A = operand;
            cpu->Z = (cpu->A == 0);
            cpu->N = (cpu->A & 0x80) ? 1 : 0;
            return 2;  // 2 cycles

        case 0x85: // STA zero page
            mem[operand] = cpu->A;
            return 3;

        default:
            // For now, just return 1 cycle for unimplemented opcodes
            return 1;
    }
}
