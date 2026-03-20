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

void test_LDA_immediate_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}


void test_LDA_zeropage_loads_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA5;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x42;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.A);
}

void test_LDA_zeropage_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA5;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x00;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_zeropage_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA5;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x80;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDA_zeropage_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA5;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x00;
    mem[0x8002] = 0xA5;
    mem[0x8003] = 0x20;
    mem[0x0020] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_zeropage_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA5;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x80;
    mem[0x8002] = 0xA5;
    mem[0x8003] = 0x20;
    mem[0x0020] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_zeropage_returns_three_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA5;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x42;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(3, cycle);
}

void test_STA_zeropage_stores_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x85;
    mem[0x8003] = 0x10;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x0010]);
}

void test_STA_zeropage_returns_three_cycles(void)
{ CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x85;
    mem[0x8003] = 0x10;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycles = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(3, cycles);
}

int main(void) {

    UNITY_BEGIN();
    //LDA Tests
    //Addressing Mode - Immediate
    RUN_TEST(test_LDA_immediate_loads_accumulator);
    RUN_TEST(test_LDA_immediate_sets_zero_flag);
    RUN_TEST(test_LDA_immediate_sets_negative_flag);
    RUN_TEST(test_LDA_immediate_clears_zero_flag);
    RUN_TEST(test_LDA_immediate_clears_negative_flag);
    RUN_TEST(test_LDA_immediate_returns_two_cycles);
    //Zero Page
    RUN_TEST(test_LDA_zeropage_loads_accumulator);
    RUN_TEST(test_LDA_zeropage_sets_zero_flag);
    RUN_TEST(test_LDA_zeropage_sets_negative_flag);
    RUN_TEST(test_LDA_zeropage_clears_zero_flag);
    RUN_TEST(test_LDA_zeropage_clears_negative_flag);
    RUN_TEST(test_LDA_zeropage_returns_three_cycles);
    //STA Tests
    RUN_TEST(test_STA_zeropage_stores_accumulator);
    RUN_TEST(test_STA_zeropage_returns_three_cycles);
    return UNITY_END();
}
