#include <stdio.h>
#include "../src/cpu.h"

int main(void) {
    printf("Hello from test!\n");
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    
    // Place reset vector at $FFFC pointing to $8000
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    
    // LDA #$42
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    
    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    
    printf("Accumulator: 0x%02X\n", cpu.A);
    printf("Zero flag: %d\n", cpu.Z);
    printf("Negative flag: %d\n", cpu.N);
    
    return 0;
}
