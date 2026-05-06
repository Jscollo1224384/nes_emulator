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
    cpu->P      = 0;
    cpu->cycles = 0;
}

// Execute one CPU instruction, return cycles consumed
int cpu_step(CPU *cpu, uint8_t *mem)
{
    uint8_t opcode = mem[cpu->PC++];
    const OpcodeEntry *entry = &opcode_table[opcode];
    
    // Handle unimplemented opcodes
    if (entry->handler == NULL) {
        return op_unimplemented(cpu, mem);
    }
    
    // Execute via function pointer (handler fetches its own operands)
    return entry->handler(cpu, mem);
}

void set_flag(CPU *cpu, uint8_t flag)
{
    cpu->P |= flag;
}

void clear_flag(CPU *cpu, uint8_t flag)
{
    cpu->P &= ~flag;
}

void update_zero_negative_flags(CPU *cpu, uint8_t register_value)
{
    if(register_value == 0) {
        set_flag(cpu, FLAG_Z);
        clear_flag(cpu, FLAG_N);
    } else {
        clear_flag(cpu, FLAG_Z);
        if(register_value & 0x80)
            set_flag(cpu, FLAG_N);
        else
            clear_flag(cpu, FLAG_N);
    }
}