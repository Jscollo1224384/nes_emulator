#include "unity.h"
#include "../src/cpu.h"

void setUp(void) {}    // called before each test
void tearDown(void) {} // called after each test

void test_LDA_immediate_loads_accumulator(void) {
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

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.A);
}

void test_LDA_immediate_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x00; // LDA #$00

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_immediate_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x80; // LDA #$80

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);

}

void test_LDA_immediate_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0xA9;
    mem[0x8003] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_immediate_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x80;
    mem[0x8002] = 0xA9;
    mem[0x8003] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_LDA_immediate_loads_accumulator);
    RUN_TEST(test_LDA_immediate_sets_zero_flag);
    RUN_TEST(test_LDA_immediate_sets_negative_flag);
    RUN_TEST(test_LDA_immediate_clears_zero_flag);
    RUN_TEST(test_LDA_immediate_clears_negative_flag);
    return UNITY_END();
}
