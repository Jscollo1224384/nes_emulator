#include <stdio.h>
#include "cpu.h"
#include "opcodes.h"

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
    const OpcodeEntry *entry = &opcode_table[opcode];
    
    // Handle unimplemented opcodes
    if (entry->handler == NULL) {
        return op_unimplemented(cpu, mem, 0);
    }
    
    // Fetch operand (for 2-byte instructions)
    uint8_t operand = 0;
    if (entry->bytes > 1) {
        operand = mem[cpu->PC++];
    }
    
    // Execute via function pointer
    return entry->handler(cpu, mem, operand);
}
