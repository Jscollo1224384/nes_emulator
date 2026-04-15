#include "unity.h"
#include "../src/cpu.h"

void setUp(void) {}    // called before each test
void tearDown(void) {} // called after each test

/** LDA Immediate tests **************************************************************/
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

/** LDA zeropage tests **************************************************************/
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

/** LDA absolute tests ****************************************************************/
void test_LDA_absolute_loads_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAD;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x42;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.A);
}

void test_LDA_absolute_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAD;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x00;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_absolute_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAD;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x80;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDA_absolute_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAD;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x00;
    mem[0x8003] = 0xAD;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2000] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_absolute_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAD;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x80;
    mem[0x8003] = 0xAD;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2000] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_absolute_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAD;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x42;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

/** LDA zeropage X tests *******************************************************************/
void test_LDA_zeropage_x_loads_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB5;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.A);
}

void test_LDA_zeropage_x_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB5;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x00;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_zeropage_x_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB5;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x80;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDA_zeropage_x_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB5;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x00;
    mem[0x8002] = 0xB5;
    mem[0x8003] = 0x15;
    mem[0x001A] = 0x01;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_zeropage_x_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB5;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x80;
    mem[0x8002] = 0xB5;
    mem[0x8003] = 0x15;
    mem[0x001A] = 0x01;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_zeropage_x_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB5;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

void test_LDA_zeropage_x_wraps_around_zero_page(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB5;
    mem[0x8001] = 0xFB;
    mem[0x0000] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, cpu.A);
}

/** Absolute X tests ***********************************************************************/
void test_LDA_absolute_x_loads_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBD;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.A);
}

void test_LDA_absolute_x_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBD;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x00;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_absolute_x_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBD;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x80;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDA_absolute_x_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBD;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x00;
    mem[0x8003] = 0xBD;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2005] = 0x01;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_absolute_x_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBD;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x80;
    mem[0x8003] = 0xBD;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2005] = 0x01;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_absolute_x_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBD;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

void test_LDA_absolute_x_returns_five_cycles_on_page_cross(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBD;
    mem[0x8001] = 0xFE;
    mem[0x8002] = 0x10;
    mem[0x1103] = 0x42; // Results in 0x1103 after adding x register. crosses from page $10 to $11 triggering a page cross.

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(5, cycle);
}

/** Absolute Y tests ***********************************************************************/
void test_LDA_absolute_y_loads_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB9;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.A);
}

void test_LDA_absolute_y_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB9;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x00;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_absolute_y_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB9;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x80;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDA_absolute_y_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB9;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x00;
    mem[0x8003] = 0xB9;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2005] = 0x01;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_absolute_y_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB9;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x80;
    mem[0x8003] = 0xB9;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2005] = 0x01;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDA_absolute_y_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB9;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

void test_LDA_absolute_y_returns_five_cycles_on_page_cross(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB9;
    mem[0x8001] = 0xFE;
    mem[0x8002] = 0x10;
    mem[0x1103] = 0x42; // Results in 0x1103 after adding y register. crosses from page $10 to $11 triggering a page cross.

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(5, cycle);
}


/** STA zero page tests *****************************************************************************/
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
    int cycles = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(3, cycles);
}

/** STA zero page X tests *****************************************************************************/
void test_STA_zeropage_x_stores_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x95;
    mem[0x8003] = 0x10;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x0015]);
}

void test_STA_zeropage_x_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x95;
    mem[0x8003] = 0x10;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

void test_STA_zeropage_x_wraps_around_zero_page(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x95;
    mem[0x8003] = 0xFB;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x0000]);
}

/** STA Absolute tests *****************************************************************************/
void test_STA_absolute_stores_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x8D;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x02;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x0200]);
}

void test_STA_absolute_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x8D;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x02;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

/** STA Absolute X tests *****************************************************************************/
void test_STA_absolute_x_stores_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x9D;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x02;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x0205]);
}

void test_STA_absolute_x_returns_five_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x9D;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x02;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(5, cycle);
}

/** STA Absolute Y tests *****************************************************************************/
void test_STA_absolute_y_stores_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x99;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x02;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x0205]);
}

void test_STA_absolute_y_returns_five_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x99;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x02;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(5, cycle);
}

/** Inderect X tests **************************************************************************************/
void test_STA_indirect_x_stores_accumulator()
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x81;
    mem[0x8003] = 0x20;
    mem[0x0024] = 0x00;
    mem[0x0025] = 0x30;

    cpu_reset(&cpu, mem);
    cpu.X = 0x04;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x3000]);
}

void test_STA_indirect_x_returns_six_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x81;
    mem[0x8003] = 0x20;
    mem[0x0024] = 0x00;
    mem[0x0025] = 0x30;

    cpu_reset(&cpu, mem);
    cpu.X = 0x04;
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(6, cycle);
}

void test_STA_indirect_x_wraps_around_zero_page(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x81;
    mem[0x8003] = 0xFF;
    mem[0x0003] = 0x00;
    mem[0x0004] = 0x30;

    cpu_reset(&cpu, mem);
    cpu.X = 0x04;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x3000]);
}

void test_STA_indirect_y_stores_accumulator()
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x91;
    mem[0x8003] = 0x20;
    mem[0x0020] = 0x00;
    mem[0x0021] = 0x30;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x04;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x3004]);
}

void test_STA_indirect_y_returns_six_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x91;
    mem[0x8003] = 0x20;
    mem[0x0020] = 0x00;
    mem[0x0021] = 0x30;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x04;
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(6, cycle);
}

void test_STA_indirect_y_wraps_zero_page_pointer(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x91;
    mem[0x8003] = 0xFF;
    mem[0x00FF] = 0x00;
    mem[0x0000] = 0x30;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x04;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x3004]);
}

/** LDX Immediate tests ****************************************************************/

void test_LDX_immediate_loads_x_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.X);
}

void test_LDX_immediate_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x00;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_immediate_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x80;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDX_immediate_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0xA2;
    mem[0x8003] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_immediate_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x80;
    mem[0x8002] = 0xA2;
    mem[0x8003] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_immediate_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}

/** LDX zero page tests ********************************************************************/
void test_LDX_zeropage_loads_x_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA6;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x42;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.X);
}

void test_LDX_zeropage_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA6;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x00;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_zeropage_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA6;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x80;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDX_zeropage_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA6;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x00;
    mem[0x8002] = 0xA6;
    mem[0x8003] = 0x20;
    mem[0x0020] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_zeropage_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA6;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x80;
    mem[0x8002] = 0xA6;
    mem[0x8003] = 0x20;
    mem[0x0020] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_zeropage_returns_three_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA6;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x42;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(3, cycle);
}

/** LDX zero page Y tests ****************************************************************************************/
void test_LDX_zeropage_y_loads_x_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB6;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.X);
}

void test_LDX_zeropage_y_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB6;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x00;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_zeropage_y_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB6;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x80;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDX_zeropage_y_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB6;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x00;
    mem[0x8002] = 0xB6;
    mem[0x8003] = 0x15;
    mem[0x001A] = 0x01;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_zeropage_y_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB6;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x80;
    mem[0x8002] = 0xB6;
    mem[0x8003] = 0x15;
    mem[0x001A] = 0x01;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_zeropage_y_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB6;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

void test_LDX_zeropage_y_wraps_around_zero_page(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB6;
    mem[0x8001] = 0xFB;
    mem[0x0000] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, cpu.X);
}

/** LDX absolute tests *********************************************************************************/
void test_LDX_absolute_loads_x_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAE;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x42;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.X);
}

void test_LDX_absolute_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAE;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x00;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_absolute_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAE;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x80;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDX_absolute_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAE;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x00;
    mem[0x8003] = 0xAE;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2000] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_absolute_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAE;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x80;
    mem[0x8003] = 0xAE;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2000] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_absolute_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAE;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x42;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

/** LDX absolute y tests ******************************************************************************************/
void test_LDX_absolute_y_loads_x_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBE;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.X);
}

void test_LDX_absolute_y_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBE;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x00;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_absolute_y_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBE;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x80;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDX_absolute_y_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBE;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x00;
    mem[0x8003] = 0xBE;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2005] = 0x01;


    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_absolute_y_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBE;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x80;
    mem[0x8003] = 0xBE;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2005] = 0x01;


    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDX_absolute_y_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBE;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

void test_LDX_absolute_y_returns_five_cycles_on_page_cross(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBE;
    mem[0x8001] = 0xFF;
    mem[0x8002] = 0x10;
    mem[0x1104] = 0x42; // Results in 0x1104 after adding Y register. crosses from page $10 to $11 triggering a page cross.

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(5, cycle);
}

/**LDY immediate tests ***************************************************************************************************************/
void test_LDY_immediate_loads_y_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x42;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.Y);
}

void test_LDY_immediate_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x00;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_immediate_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x80;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDY_immediate_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0xA0;
    mem[0x8003] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_immediate_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x80;
    mem[0x8002] = 0xA0;
    mem[0x8003] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_immediate_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x42;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}

/** LDY zero page tests ****************************************************************************/
void test_LDY_zeropage_loads_y_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA4;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x42;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.Y);
}

void test_LDY_zeropage_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA4;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x00;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_zeropage_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA4;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x80;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDY_zeropage_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA4;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x00;
    mem[0x8002] = 0xA4;
    mem[0x8003] = 0x20;
    mem[0x0020] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_zeropage_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA4;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x80;
    mem[0x8002] = 0xA4;
    mem[0x8003] = 0x20;
    mem[0x0020] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}


void test_LDY_zeropage_returns_three_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA4;
    mem[0x8001] = 0x10;
    mem[0x0010] = 0x42;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(3, cycle);
}

/** LDY zero page x tests *********************************************************************************************/
void test_LDY_zeropage_x_loads_y_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB4;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.Y);
}

void test_LDY_zeropage_x_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB4;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x00;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_zeropage_x_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB4;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x80;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDY_zeropage_x_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB4;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x00;
    mem[0x8002] = 0xB4;
    mem[0x8003] = 0x15;
    mem[0x001A] = 0x01;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_zeropage_x_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB4;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x80;
    mem[0x8002] = 0xB4;
    mem[0x8003] = 0x15;
    mem[0x001A] = 0x01;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_zeropage_x_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB4;
    mem[0x8001] = 0x10;
    mem[0x0015] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

void test_LDY_zeropage_x_wraps_around_zero_page(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xB4;
    mem[0x8001] = 0xFB;
    mem[0x0000] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, cpu.Y);
}

/** LDY absolute tests *******************************************************************************************/
void test_LDY_absolute_loads_y_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAC;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x42;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.Y);
}

void test_LDY_absolute_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAC;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x00;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_absolute_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAC;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x80;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDY_absolute_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAC;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x00;
    mem[0x8003] = 0xAC;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2000] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_absolute_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAC;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x80;
    mem[0x8003] = 0xAC;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2000] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_absolute_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xAC;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1000] = 0x42;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

/**LDY Absolute X tests **********************************************************************************************/
void test_LDY_absolute_x_loads_y_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBC;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, cpu.Y);
}

void test_LDY_absolute_x_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBC;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x00;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_absolute_x_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBC;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x80;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_LDY_absolute_x_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBC;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x00;
    mem[0x8003] = 0xBC;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2005] = 0x01;


    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_absolute_x_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBC;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x80;
    mem[0x8003] = 0xBC;
    mem[0x8004] = 0x00;
    mem[0x8005] = 0x20;
    mem[0x2005] = 0x01;


    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_LDY_absolute_x_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBC;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x10;
    mem[0x1005] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

void test_LDY_absolute_x_returns_five_cycles_on_page_cross(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBC;
    mem[0x8001] = 0xFF;
    mem[0x8002] = 0x10;
    mem[0x1104] = 0x42; // Results in 0x1104 after adding X register. crosses from page $10 to $11 triggering a page cross.

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(5, cycle);
}

/** STX zero page tests ********************************************************************************************************************/
void test_STX_zeropage_stores_x_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x86;
    mem[0x8003] = 0x10;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x0010]);
}

void test_STX_zeropage_returns_three_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x86;
    mem[0x8003] = 0x10;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(3, cycle);
}

/** STX zero page Y tests ***************************************************************************/
void test_STX_zeropage_y_stores_x_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x96;
    mem[0x8003] = 0x10;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x0015]);
}

void test_STX_zeropage_y_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x96;
    mem[0x8003] = 0x10;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

void test_STX_zeropage_y_wraps_around_zero_page(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x96;
    mem[0x8003] = 0xFF;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x0004]);
}

/** STX Absolute tests ************************************************************************/
void test_STX_absolute_stores_x_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x8E;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x10;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, mem[0x1000]);
}

void test_STX_absolute_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x8E;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x10;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

/** STY zero page tests ******************************************************************************/
void test_STY_zeropage_stores_y_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x84;
    mem[0x8003] = 0x10;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x0010]);
}

void test_STY_zeropage_returns_three_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x84;
    mem[0x8003] = 0x10;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(3, cycle);
}

/** STY zero page X tests ********************************************************************************/
void test_STY_zeropage_x_stores_y_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x94;
    mem[0x8003] = 0x10;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x0015]);
}

void test_STY_zeropage_x_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x94;
    mem[0x8003] = 0x10;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

void test_STY_zeropage_x_wraps_around_zero_page(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x94;
    mem[0x8003] = 0xFF;

    cpu_reset(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x0004]);
}

/** STY absolut tests **********************************************************************************/
void test_STY_absolute_stores_y_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x8C;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x10;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL_HEX8(0x42, mem[0x1000]);
}

void test_STY_absolute_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x8C;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x10;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

/** TAX Tests *****************************************************************************************************************/
void test_TAX_transfers_accumulator_to_x(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0xAA;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, cpu.X);
}

void test_TAX_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0xAA;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.Z = 0;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TAX_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x80;
    mem[0x8002] = 0xAA;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 0;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}
void test_TAX_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x01;
    mem[0x8002] = 0xAA;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.Z = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TAX_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x01;
    mem[0x8002] = 0xAA;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TAX_overwrites_existing_x(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0xA9;
    mem[0x8003] = 0x01;
    mem[0x8004] = 0xAA;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x01, cpu.X);
}

void test_TAX_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0xAA;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}

/** TAY Tests **********************************************************************************/
void test_TAY_transfers_accumulator_to_y(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0xA8;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, cpu.Y);
}

void test_TAY_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0xA8;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.Z = 0;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TAY_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x80;
    mem[0x8002] = 0xA8;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 0;

    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_TAY_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x01;
    mem[0x8002] = 0xA8;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.Z = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TAY_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x01;
    mem[0x8002] = 0xA8;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TAY_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0xA8;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}

void test_TAY_overwrites_existing_y(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0xA9;
    mem[0x8003] = 0x01;
    mem[0x8004] = 0xA8;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x01, cpu.Y);
}

/** TXA Tests **************************************************************************************************************/
void test_TXA_transfers_x_to_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x8A;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, cpu.A);
}

void test_TXA_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x8A;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.Z = 0;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TXA_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x80;
    mem[0x8002] = 0x8A;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 0;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_TXA_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x01;
    mem[0x8002] = 0x8A;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.Z = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TXA_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x01;
    mem[0x8002] = 0x8A;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TXA_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x8A;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}

void test_TXA_overwrites_existing_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0xA2;
    mem[0x8003] = 0x01;
    mem[0x8004] = 0x8A;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x01, cpu.A);
}

/** TYA Tests************************************************************************************************/
void test_TYA_transfers_y_to_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x98;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, cpu.A);
}

void test_TYA_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x98;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.Z = 0;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TYA_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x80;
    mem[0x8002] = 0x98;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 0;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_TYA_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x01;
    mem[0x8002] = 0x98;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.Z = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TYA_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x01;
    mem[0x8002] = 0x98;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TYA_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA0;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x98;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}

void test_TYA_overwrites_existing_accumulator(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0xA0;
    mem[0x8003] = 0x01;
    mem[0x8004] = 0x98;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x01, cpu.A);
}

/** TSX Tests ***************************************************************************************************/
void test_TSX_transfers_stack_pointer_to_x(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBA;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0xFD, cpu.X);
}

void test_TSX_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBA;

    cpu_reset(&cpu, mem);
    cpu.SP = 0x00;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TSX_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBA;

    cpu_reset(&cpu, mem); //Reset sets SP to 0xFD, this will set the negative flag.
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_TSX_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBA;

    cpu_reset(&cpu, mem);
    cpu.SP = 0x01;
    cpu.Z = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TSX_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBA;

    cpu_reset(&cpu, mem);
    cpu.SP = 0x01;
    cpu.N = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_TSX_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xBA;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}

/** TXS Tests *******************************************************************************************************/
void test_TXS_transfers_x_to_stack_pointer(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x9A;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, cpu.SP);
}

void test_TXS_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA2;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x9A;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}

/** PHA Tests *****************************************************************************************/
void test_PHA_pushes_accumulator_to_stack(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x48;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, mem[0x01FD]);
}

void test_PHA_decrements_stack_pointer(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x48;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0xFC, cpu.SP);
}

void test_PHA_returns_three_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0x42;
    mem[0x8002] = 0x48;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(3, cycle);
}

/** PLA Tests *****************************************************************************************************/
void test_PLA_pulls_accumulator_from_stack(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x68;
    mem[0x01FD] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.SP = 0xFC;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x42, cpu.A);
}

void test_PLA_increments_stack_pointer(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x68;
    mem[0x01FD] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.SP = 0xFC;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0xFD, cpu.SP);
}

void test_PLA_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x68;
    mem[0x01FD] = 0x00;

    cpu_reset(&cpu, mem);
    cpu.SP = 0xFC;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_PLA_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x68;
    mem[0x01FD] = 0x80;

    cpu_reset(&cpu, mem);
    cpu.SP = 0xFC;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_PLA_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x68;
    mem[0x01FD] = 0x01;

    cpu_reset(&cpu, mem);
    cpu.SP = 0xFC;
    cpu.Z = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_PLA_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x68;
    mem[0x01FD] = 0x01;

    cpu_reset(&cpu, mem);
    cpu.SP = 0xFC;
    cpu.N = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_PLA_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x68;
    mem[0x01FD] = 0x42;

    cpu_reset(&cpu, mem);
    cpu.SP = 0xFC;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

/** PHP Tests ************************************************************************************************/
void test_PHP_pushes_processor_status_to_stack(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x08;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0b00110100, mem[0x01FD]); // This tests the status bits that are set at reset.
}

void test_PHP_decrements_stack_pointer(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x08;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0xFC, cpu.SP);
}

void test_PHP_returns_three_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x08;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(3, cycle);
}

/** PLP Tests ****************************************************************************************************/
void test_PLP_pulls_processor_status_from_stack(void) {
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x08;
    mem[0x8001] = 0x28;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 1;
    cpu_step(&cpu, mem);

    // cpu.I and cpu.B are set from pulling processor status after reset.
    TEST_ASSERT_EQUAL(1, cpu.I);
    TEST_ASSERT_EQUAL(1, cpu.B);
    TEST_ASSERT_EQUAL(0,cpu.N);
}

void test_PLP_increments_stack_pointer(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x08;
    mem[0x8001] = 0x28;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.SP = 0xFC;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0XFD, cpu.SP);
}

void test_PLP_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x08;
    mem[0x8001] = 0x28;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

/** INX Tests *****************************************************************************************************/
void test_INX_increments_x_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xE8;

    cpu_reset(&cpu, mem);
    cpu.X = 0xFC;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0XFD, cpu.X);
}

void test_INX_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xE8;

    cpu_reset(&cpu, mem);
    cpu.X = 0xFF;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_INX_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xE8;

    cpu_reset(&cpu, mem);
    cpu.X = 0xFE;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_INX_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xE8;

    cpu_reset(&cpu, mem);
    cpu.Z = 1;
    cpu.X = 0x00;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_INX_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xE8;

    cpu_reset(&cpu, mem);
    cpu.N = 1;
    cpu.X = 0x00;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_INX_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xE8;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}

void test_INX_wraps_around(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xE8;

    cpu_reset(&cpu, mem);
    cpu.X = 0xFF;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x00, cpu.X);
}

/** INY Tests *****************************************************************************************************/
void test_INY_increments_y_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xC8;

    cpu_reset(&cpu, mem);
    cpu.Y = 0xFC;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0XFD, cpu.Y);
}

void test_INY_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xC8;

    cpu_reset(&cpu, mem);
    cpu.Y = 0xFF;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_INY_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xC8;

    cpu_reset(&cpu, mem);
    cpu.Y = 0xFE;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_INY_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xC8;

    cpu_reset(&cpu, mem);
    cpu.Z = 1;
    cpu.Y = 0x00;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_INY_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xC8;

    cpu_reset(&cpu, mem);
    cpu.N = 1;
    cpu.Y = 0x00;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_INY_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xC8;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}

void test_INY_wraps_around(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xC8;

    cpu_reset(&cpu, mem);
    cpu.Y = 0xFF;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x00, cpu.Y);
}

/** DEX Tests *****************************************************************************************************/
void test_DEX_decrements_x_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xCA;

    cpu_reset(&cpu, mem);
    cpu.X = 0xFC;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0XFB, cpu.X);
}

void test_DEX_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xCA;

    cpu_reset(&cpu, mem);
    cpu.X = 0x01;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_DEX_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xCA;

    cpu_reset(&cpu, mem);
    cpu.X = 0x00;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_DEX_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xCA;

    cpu_reset(&cpu, mem);
    cpu.Z = 1;
    cpu.X = 0x02;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_DEX_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xCA;

    cpu_reset(&cpu, mem);
    cpu.N = 1;
    cpu.X = 0x80;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_DEX_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xCA;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}

void test_DEX_wraps_around(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xCA;

    cpu_reset(&cpu, mem);
    cpu.X = 0x00;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0xFF, cpu.X);
}

/** DEX Tests *****************************************************************************************************/
void test_DEY_decrements_y_register(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x88;

    cpu_reset(&cpu, mem);
    cpu.Y = 0xFC;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0XFB, cpu.Y);
}

void test_DEY_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x88;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x01;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_DEY_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x88;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x00;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_DEY_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x88;

    cpu_reset(&cpu, mem);
    cpu.Z = 1;
    cpu.Y = 0x02;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_DEY_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x88;

    cpu_reset(&cpu, mem);
    cpu.N = 1;
    cpu.Y = 0x80;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_DEY_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x88;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}

void test_DEY_wraps_around(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x88;

    cpu_reset(&cpu, mem);
    cpu.Y = 0x00;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0xFF, cpu.Y);
}

/** JMP Absolute Tests ****************************************************************************/
void test_JMP_absolute_jumps_to_address(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x4C;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x01;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x0100, cpu.PC);
}

void test_JMP_absolute_returns_three_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x4C;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x01;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(3, cycle);
}

/** JMP Indirect Tests ****************************************************************************/
void test_JMP_indirect_jumps_to_address(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x6C;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x01;
    mem[0x0100] = 0x00;
    mem[0x0101] = 0x20;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x2000, cpu.PC);
}

void test_JMP_indirect_returns_five_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x6C;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x01;
    mem[0x0100] = 0x00;
    mem[0x0101] = 0x20;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(5, cycle);
}

void test_JMP_indirect_page_boundary_bug(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x6C;
    mem[0x8001] = 0xFF;
    mem[0x8002] = 0x10;
    mem[0x10FF] = 0x00;
    mem[0x1000] = 0x20;
    mem[0x1100] = 0x30;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x2000, cpu.PC);
}

/** JSR Tests ****************************************************************************/
void test_JSR_jumps_to_subroutine(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x20;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x02;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x0200, cpu.PC);
}

void test_JSR_pushes_return_address_high_byte(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x20;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x02;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x80, mem[0x01FD]);
}

void test_JSR_pushes_return_address_low_byte(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x20;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x02;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x02, mem[0x01FC]);
}

void test_JSR_decrements_stack_pointer_twice(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x20;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x02;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0xFB, cpu.SP);
}

void test_JSR_returns_six_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x20;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x02;

    cpu_reset(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(6, cycle);
}

/** RTS Tests ****************************************************************************/
void test_RTS_returns_from_subroutine(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x20;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x02;
    mem[0x0200] = 0x60;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0x8003, cpu.PC);
}

void test_RTS_increments_stack_pointer_twice(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x20;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x02;
    mem[0x0200] = 0x60;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0xFD, cpu.SP);
}

void test_RTS_returns_six_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0x20;
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x02;
    mem[0x0200] = 0x60;

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(6, cycle);
}

/** AND immediate Tests*******************************************************************************************/
void test_AND_immediate_performs_and_operation(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x29;
    mem[0x8003] = 0b01000000; //0x40

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0b01000000 /*0x40*/, cpu.A);
}

void test_AND_immediate_sets_zero_flag(void)
{
     CPU cpu;
     uint8_t mem[0x10000] = {0};

     mem[0xFFFC] = 0x00;
     mem[0xFFFD] = 0x80;
     mem[0x8000] = 0xA9;
     mem[0x8001] = 0b01000010; //0x42
     mem[0x8002] = 0x29;
     mem[0x8003] = 0b00000000; //0x00

     cpu_reset(&cpu, mem);
     cpu_step(&cpu, mem);
     cpu_step(&cpu, mem);

     TEST_ASSERT_EQUAL(1, cpu.Z);
     TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_immediate_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b10000001; //0x81
    mem[0x8002] = 0x29;
    mem[0x8003] = 0b10000000; //0x80

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 0;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_AND_immediate_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b00000001; //0x01
    mem[0x8002] = 0x29;
    mem[0x8003] = 0b00000001; //0x01

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.Z = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_immediate_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b10000001; //0x81
    mem[0x8002] = 0x29;
    mem[0x8003] = 0b00000001; //0x01

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_immediate_returns_two_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x29;
    mem[0x8003] = 0b01000000; //0x40

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(2, cycle);
}

/** AND zero page tests ***************************************************************************/
void test_AND_zeropage_performs_and_operation(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x25;
    mem[0x8003] = 0x02;
    mem[0x0002] = 0b01000000; //0x40

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0b01000000, cpu.A);
}

void test_AND_zeropage_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x25;
    mem[0x8003] = 0x02;
    mem[0x0002] = 0b00000000; //0x00

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_zeropage_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b10000001; //0x81
    mem[0x8002] = 0x25;
    mem[0x8003] = 0x02;
    mem[0x0002] = 0b10000000; //0x80

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 0;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_AND_zeropage_clears_zero_flag(void) {

    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b00000001; //0x01
    mem[0x8002] = 0x25;
    mem[0x8003] = 0x02;
    mem[0x0002] = 0b00000001; //0x01

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.Z = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_zeropage_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b10000001; //0x81
    mem[0x8002] = 0x25;
    mem[0x8003] = 0x02;
    mem[0x0002] = 0b00000001; //0x01

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_zeropage_returns_three_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x25;
    mem[0x8003] = 0x02;
    mem[0x0002] = 0b01000000; //0x40

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(3, cycle);
}

void test_AND_absolute_performs_and_operation(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x2D;
    mem[0x8003] = 0x00; //low  byte
    mem[0x8004] = 0x50; //high byte
    mem[0x5000] = 0b01000000; //0x40

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0b01000000, cpu.A);
}

void test_AND_absolute_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x2D;
    mem[0x8003] = 0x00; //low  byte
    mem[0x8004] = 0x50; //high byte
    mem[0x5000] = 0b00000000; //0x00

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_absolute_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b10000001; //0x81
    mem[0x8002] = 0x2D;
    mem[0x8003] = 0x00; //low  byte
    mem[0x8004] = 0x50; //high byte
    mem[0x5000] = 0b10000000; //0x80

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 0;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_AND_absolute_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x2D;
    mem[0x8003] = 0x00; //low  byte
    mem[0x8004] = 0x50; //high byte
    mem[0x5000] = 0b01000011; //0x43

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.Z = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_absolute_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b10000001; //0x81
    mem[0x8002] = 0x2D;
    mem[0x8003] = 0x00; //low  byte
    mem[0x8004] = 0x50; //high byte
    mem[0x5000] = 0b00000001; //0x01

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.N = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_absolute_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b10000001; //0x81
    mem[0x8002] = 0x2D;
    mem[0x8003] = 0x00; //low  byte
    mem[0x8004] = 0x50; //high byte
    mem[0x5000] = 0b00000001; //0x01

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

/**AND Zero page x Tests *********************************************************************************************/
void test_AND_zeropage_x_ands_accumulator_with_x_offset_value(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x35;
    mem[0x8003] = 0x00;
    mem[0x0005] = 0b01000000; //0x40

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0b01000000, cpu.A);
}

void test_AND_zeropage_x_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x35;
    mem[0x8003] = 0x00;
    mem[0x0005] = 0b00000000; //0x00

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_zeropage_x_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b10000001; //0x81
    mem[0x8002] = 0x35;
    mem[0x8003] = 0x00;
    mem[0x0005] = 0b10000000; //0x80

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    cpu.N = 0;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_AND_zeropage_x_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b00000001; //0x01
    mem[0x8002] = 0x35;
    mem[0x8003] = 0x00;
    mem[0x0005] = 0b00000001; //0x01

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    cpu.Z = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_zeropage_x_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b10000001; //0x81
    mem[0x8002] = 0x35;
    mem[0x8003] = 0x00;
    mem[0x0005] = 0b00000001; //0x01

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    cpu.N = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_zeropage_x_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x35;
    mem[0x8003] = 0x00;
    mem[0x0005] = 0b01000000; //0x40

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

void test_AND_zeropage_x_wraps_around_zero_page(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x35;
    mem[0x8003] = 0xFF;
    mem[0x0004] = 0b01000000; //0x40

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0b01000000, cpu.A);
}

void test_AND_absolute_x_ands_accumulator_with_x_offset_value (void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x3D;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x20;
    mem[0x2005] = 0b01000000; //0x40

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0b01000000, cpu.A);
}

void test_AND_absolute_x_sets_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x3D;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x20;
    mem[0x2005] = 0b00000000; //0x00

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_absolute_x_sets_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b10000001; //0x81
    mem[0x8002] = 0x3D;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x20;
    mem[0x2005] = 0b10000000; //0x80

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    cpu.N = 0;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(1, cpu.N);
}

void test_AND_absolute_x_clears_zero_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b00000001; //0x01
    mem[0x8002] = 0x3D;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x20;
    mem[0x2005] = 0b00000001; //0x01

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    cpu.Z = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_absolute_x_clears_negative_flag(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b10000001; //0x81
    mem[0x8002] = 0x3D;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x20;
    mem[0x2005] = 0b00000001; //0x01

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    cpu.N = 1;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

void test_AND_absolute_x_returns_four_cycles(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x3D;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x20;
    mem[0x2005] = 0b01000000; //0x40

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(4, cycle);
}

void test_AND_absolute_x_returns_five_cycles_on_page_cross(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x3D;
    mem[0x8003] = 0xFF;
    mem[0x8004] = 0x20;
    mem[0x2104] = 0b01000000; //0x40

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.X = 0x05;
    int cycle = cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(5, cycle);
}

void test_AND_absolute_y_ands_accumulator_with_y_offset_value(void)
{
    CPU cpu;
    uint8_t mem[0x10000] = {0};

    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9;
    mem[0x8001] = 0b01000010; //0x42
    mem[0x8002] = 0x39;
    mem[0x8003] = 0x00;
    mem[0x8004] = 0x20;
    mem[0x2005] = 0b01000000; //0x40

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);
    cpu.Y = 0x05;
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(0b01000000, cpu.A);
}

int main(void) {

    UNITY_BEGIN();
    //LDA Tests
    //Addressing Mode
    //Immediate
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
    //Absolute
    RUN_TEST(test_LDA_absolute_loads_accumulator);
    RUN_TEST(test_LDA_absolute_sets_zero_flag);
    RUN_TEST(test_LDA_absolute_sets_negative_flag);
    RUN_TEST(test_LDA_absolute_clears_zero_flag);
    RUN_TEST(test_LDA_absolute_clears_negative_flag);
    RUN_TEST(test_LDA_absolute_returns_four_cycles);
    //Zero Page X
    RUN_TEST(test_LDA_zeropage_x_loads_accumulator);
    RUN_TEST(test_LDA_zeropage_x_sets_zero_flag);
    RUN_TEST(test_LDA_zeropage_x_sets_negative_flag);
    RUN_TEST(test_LDA_zeropage_x_clears_zero_flag);
    RUN_TEST(test_LDA_zeropage_x_clears_negative_flag);
    RUN_TEST(test_LDA_zeropage_x_returns_four_cycles);
    RUN_TEST(test_LDA_zeropage_x_wraps_around_zero_page);
    //Absolute X
    RUN_TEST(test_LDA_absolute_x_loads_accumulator);
    RUN_TEST(test_LDA_absolute_x_sets_zero_flag);
    RUN_TEST(test_LDA_absolute_x_sets_negative_flag);
    RUN_TEST(test_LDA_absolute_x_clears_zero_flag);
    RUN_TEST(test_LDA_absolute_x_clears_negative_flag);
    RUN_TEST(test_LDA_absolute_x_returns_four_cycles);
    RUN_TEST(test_LDA_absolute_x_returns_five_cycles_on_page_cross);
    //Absolute Y
    RUN_TEST(test_LDA_absolute_y_loads_accumulator);
    RUN_TEST(test_LDA_absolute_y_sets_zero_flag);
    RUN_TEST(test_LDA_absolute_y_sets_negative_flag);
    RUN_TEST(test_LDA_absolute_y_clears_zero_flag);
    RUN_TEST(test_LDA_absolute_y_clears_negative_flag);
    RUN_TEST(test_LDA_absolute_y_returns_four_cycles);
    RUN_TEST(test_LDA_absolute_y_returns_five_cycles_on_page_cross);

    //STA Tests
    //Zero page
    RUN_TEST(test_STA_zeropage_stores_accumulator);
    RUN_TEST(test_STA_zeropage_returns_three_cycles);
    //Zero page X
    RUN_TEST(test_STA_zeropage_x_stores_accumulator);
    RUN_TEST(test_STA_zeropage_x_returns_four_cycles);
    RUN_TEST(test_STA_zeropage_x_wraps_around_zero_page);
    //Absolute
    RUN_TEST(test_STA_absolute_stores_accumulator);
    RUN_TEST(test_STA_absolute_returns_four_cycles);
    //Absolute X
    RUN_TEST(test_STA_absolute_x_stores_accumulator);
    RUN_TEST(test_STA_absolute_x_returns_five_cycles);
    //Absolute Y
    RUN_TEST(test_STA_absolute_y_stores_accumulator);
    RUN_TEST(test_STA_absolute_y_returns_five_cycles);
    //Indirect X
    RUN_TEST(test_STA_indirect_x_stores_accumulator);
    RUN_TEST(test_STA_indirect_x_returns_six_cycles);
    RUN_TEST(test_STA_indirect_x_wraps_around_zero_page);
    //Indirect Y
    RUN_TEST(test_STA_indirect_y_stores_accumulator);
    RUN_TEST(test_STA_indirect_y_returns_six_cycles);
    RUN_TEST(test_STA_indirect_y_wraps_zero_page_pointer);

    //LDX Tests
    //Immediate
    RUN_TEST(test_LDX_immediate_loads_x_register);
    RUN_TEST(test_LDX_immediate_sets_zero_flag);
    RUN_TEST(test_LDX_immediate_sets_negative_flag);
    RUN_TEST(test_LDX_immediate_clears_zero_flag);
    RUN_TEST(test_LDX_immediate_clears_negative_flag);
    RUN_TEST(test_LDX_immediate_returns_two_cycles);
    //Zero page
    RUN_TEST(test_LDX_zeropage_loads_x_register);
    RUN_TEST(test_LDX_zeropage_sets_zero_flag);
    RUN_TEST(test_LDX_zeropage_sets_negative_flag);
    RUN_TEST(test_LDX_zeropage_clears_zero_flag);
    RUN_TEST(test_LDX_zeropage_clears_negative_flag);
    RUN_TEST(test_LDX_zeropage_returns_three_cycles);
    //Zero page Y
    RUN_TEST(test_LDX_zeropage_y_loads_x_register);
    RUN_TEST(test_LDX_zeropage_y_sets_zero_flag);
    RUN_TEST(test_LDX_zeropage_y_sets_negative_flag);
    RUN_TEST(test_LDX_zeropage_y_clears_zero_flag);
    RUN_TEST(test_LDX_zeropage_y_clears_negative_flag);
    RUN_TEST(test_LDX_zeropage_y_returns_four_cycles);
    RUN_TEST(test_LDX_zeropage_y_wraps_around_zero_page);
    //Absolute
    RUN_TEST(test_LDX_absolute_loads_x_register);
    RUN_TEST(test_LDX_absolute_sets_zero_flag);
    RUN_TEST(test_LDX_absolute_sets_negative_flag);
    RUN_TEST(test_LDX_absolute_clears_zero_flag);
    RUN_TEST(test_LDX_absolute_clears_negative_flag);
    RUN_TEST(test_LDX_absolute_returns_four_cycles);
    //Absolute Y
    RUN_TEST(test_LDX_absolute_y_loads_x_register);
    RUN_TEST(test_LDX_absolute_y_sets_zero_flag);
    RUN_TEST(test_LDX_absolute_y_sets_negative_flag);
    RUN_TEST(test_LDX_absolute_y_clears_zero_flag);
    RUN_TEST(test_LDX_absolute_y_clears_negative_flag);
    RUN_TEST(test_LDX_absolute_y_returns_four_cycles);
    RUN_TEST(test_LDX_absolute_y_returns_five_cycles_on_page_cross);

    //LDY Tests
    //Immediate
    RUN_TEST(test_LDY_immediate_loads_y_register);
    RUN_TEST(test_LDY_immediate_sets_zero_flag);
    RUN_TEST(test_LDY_immediate_sets_negative_flag);
    RUN_TEST(test_LDY_immediate_clears_zero_flag);
    RUN_TEST(test_LDY_immediate_clears_negative_flag);
    RUN_TEST(test_LDY_immediate_returns_two_cycles);
    //Zero page
    RUN_TEST(test_LDY_zeropage_loads_y_register);
    RUN_TEST(test_LDY_zeropage_sets_zero_flag);
    RUN_TEST(test_LDY_zeropage_sets_negative_flag);
    RUN_TEST(test_LDY_zeropage_clears_zero_flag);
    RUN_TEST(test_LDY_zeropage_clears_negative_flag);
    RUN_TEST(test_LDY_zeropage_returns_three_cycles);
    //Zero page X
    RUN_TEST(test_LDY_zeropage_x_loads_y_register);
    RUN_TEST(test_LDY_zeropage_x_sets_zero_flag);
    RUN_TEST(test_LDY_zeropage_x_sets_negative_flag);
    RUN_TEST(test_LDY_zeropage_x_clears_zero_flag);
    RUN_TEST(test_LDY_zeropage_x_clears_negative_flag);
    RUN_TEST(test_LDY_zeropage_x_returns_four_cycles);
    RUN_TEST(test_LDY_zeropage_x_wraps_around_zero_page);
    //Absolute
    RUN_TEST(test_LDY_absolute_loads_y_register);
    RUN_TEST(test_LDY_absolute_sets_zero_flag);
    RUN_TEST(test_LDY_absolute_sets_negative_flag);
    RUN_TEST(test_LDY_absolute_clears_zero_flag);
    RUN_TEST(test_LDY_absolute_clears_negative_flag);
    RUN_TEST(test_LDY_absolute_returns_four_cycles);
    //Absolute X
    RUN_TEST(test_LDY_absolute_x_loads_y_register);
    RUN_TEST(test_LDY_absolute_x_sets_zero_flag);
    RUN_TEST(test_LDY_absolute_x_sets_negative_flag);
    RUN_TEST(test_LDY_absolute_x_clears_zero_flag);
    RUN_TEST(test_LDY_absolute_x_clears_negative_flag);
    RUN_TEST(test_LDY_absolute_x_returns_four_cycles);
    RUN_TEST(test_LDY_absolute_x_returns_five_cycles_on_page_cross);

    //STX Tests
    //Zero page
    RUN_TEST(test_STX_zeropage_stores_x_register);
    RUN_TEST(test_STX_zeropage_returns_three_cycles);
    //Zero page Y
    RUN_TEST(test_STX_zeropage_y_stores_x_register);
    RUN_TEST(test_STX_zeropage_y_returns_four_cycles);
    RUN_TEST(test_STX_zeropage_y_wraps_around_zero_page);
    //Absolute
    RUN_TEST(test_STX_absolute_stores_x_register);
    RUN_TEST(test_STX_absolute_returns_four_cycles);

    //STY Tests
    //Zero page
    RUN_TEST(test_STY_zeropage_stores_y_register);
    RUN_TEST(test_STY_zeropage_returns_three_cycles);
    //Zero page X
    RUN_TEST(test_STY_zeropage_x_stores_y_register);
    RUN_TEST(test_STY_zeropage_x_returns_four_cycles);
    RUN_TEST(test_STY_zeropage_x_wraps_around_zero_page);
    //Absolute
    RUN_TEST(test_STY_absolute_stores_y_register);
    RUN_TEST(test_STY_absolute_returns_four_cycles);

    //TAX Tests
    //Implied
    RUN_TEST(test_TAX_transfers_accumulator_to_x);
    RUN_TEST(test_TAX_sets_zero_flag);
    RUN_TEST(test_TAX_sets_negative_flag);
    RUN_TEST(test_TAX_clears_zero_flag);
    RUN_TEST(test_TAX_clears_negative_flag);
    RUN_TEST(test_TAX_overwrites_existing_x);
    RUN_TEST(test_TAX_returns_two_cycles);

    //TAY Tests
    //Implied
    RUN_TEST(test_TAY_transfers_accumulator_to_y);
    RUN_TEST(test_TAY_sets_zero_flag);
    RUN_TEST(test_TAY_sets_negative_flag);
    RUN_TEST(test_TAY_clears_zero_flag);
    RUN_TEST(test_TAY_clears_negative_flag);
    RUN_TEST(test_TAY_returns_two_cycles);
    RUN_TEST(test_TAY_overwrites_existing_y);

    //TXA Tests
    //Implied
    RUN_TEST(test_TXA_transfers_x_to_accumulator);
    RUN_TEST(test_TXA_sets_zero_flag);
    RUN_TEST(test_TXA_sets_negative_flag);
    RUN_TEST(test_TXA_clears_zero_flag);
    RUN_TEST(test_TXA_clears_negative_flag);
    RUN_TEST(test_TXA_returns_two_cycles);
    RUN_TEST(test_TXA_overwrites_existing_accumulator);

    //TYA Tests
    //Implied
    RUN_TEST(test_TYA_transfers_y_to_accumulator);
    RUN_TEST(test_TYA_sets_zero_flag);
    RUN_TEST(test_TYA_sets_negative_flag);
    RUN_TEST(test_TYA_clears_zero_flag);
    RUN_TEST(test_TYA_clears_negative_flag);
    RUN_TEST(test_TYA_returns_two_cycles);
    RUN_TEST(test_TYA_overwrites_existing_accumulator);

    //TSX Tests
    //Implied
    RUN_TEST(test_TSX_transfers_stack_pointer_to_x);
    RUN_TEST(test_TSX_sets_zero_flag);
    RUN_TEST(test_TSX_sets_negative_flag);
    RUN_TEST(test_TSX_clears_zero_flag);
    RUN_TEST(test_TSX_clears_negative_flag);
    RUN_TEST(test_TSX_returns_two_cycles);

    //TXS Tests
    //Implied
    RUN_TEST(test_TXS_transfers_x_to_stack_pointer);
    RUN_TEST(test_TXS_returns_two_cycles);

    //PHA Tests
    //Implied
    RUN_TEST(test_PHA_pushes_accumulator_to_stack);
    RUN_TEST(test_PHA_decrements_stack_pointer);
    RUN_TEST(test_PHA_returns_three_cycles);

    //PLA Tests
    //Implied
    RUN_TEST(test_PLA_pulls_accumulator_from_stack);
    RUN_TEST(test_PLA_increments_stack_pointer);
    RUN_TEST(test_PLA_sets_zero_flag);
    RUN_TEST(test_PLA_sets_negative_flag);
    RUN_TEST(test_PLA_clears_zero_flag);
    RUN_TEST(test_PLA_clears_negative_flag);
    RUN_TEST(test_PLA_returns_four_cycles);

    //PHP Tests
    //Implied
    RUN_TEST(test_PHP_pushes_processor_status_to_stack);
    RUN_TEST(test_PHP_decrements_stack_pointer);
    RUN_TEST(test_PHP_returns_three_cycles);

    //PLP Tests
    //Implied
    RUN_TEST(test_PLP_pulls_processor_status_from_stack);
    RUN_TEST(test_PLP_increments_stack_pointer);
    RUN_TEST(test_PLP_returns_four_cycles);

    //INX Tests
    //Implied
    RUN_TEST(test_INX_increments_x_register);
    RUN_TEST(test_INX_sets_zero_flag);
    RUN_TEST(test_INX_sets_negative_flag);
    RUN_TEST(test_INX_clears_zero_flag);
    RUN_TEST(test_INX_clears_negative_flag);
    RUN_TEST(test_INX_returns_two_cycles);
    RUN_TEST(test_INX_wraps_around);

    //INX Tests
    //Implied
    RUN_TEST(test_INY_increments_y_register);
    RUN_TEST(test_INY_sets_zero_flag);
    RUN_TEST(test_INY_sets_negative_flag);
    RUN_TEST(test_INY_clears_zero_flag);
    RUN_TEST(test_INY_clears_negative_flag);
    RUN_TEST(test_INY_returns_two_cycles);
    RUN_TEST(test_INY_wraps_around);

    //DEX Tests
    //Implied
    RUN_TEST(test_DEX_decrements_x_register);
    RUN_TEST(test_DEX_sets_zero_flag);
    RUN_TEST(test_DEX_sets_negative_flag);
    RUN_TEST(test_DEX_clears_zero_flag);
    RUN_TEST(test_DEX_clears_negative_flag);
    RUN_TEST(test_DEX_returns_two_cycles);
    RUN_TEST(test_DEX_wraps_around);

    //DEY Tests
    //Implied
    RUN_TEST(test_DEY_decrements_y_register);
    RUN_TEST(test_DEY_sets_zero_flag);
    RUN_TEST(test_DEY_sets_negative_flag);
    RUN_TEST(test_DEY_clears_zero_flag);
    RUN_TEST(test_DEY_clears_negative_flag);
    RUN_TEST(test_DEY_returns_two_cycles);
    RUN_TEST(test_DEY_wraps_around);

    //JMP Tests
    //Addressing Mode
    //Absolute
    RUN_TEST(test_JMP_absolute_jumps_to_address);
    RUN_TEST(test_JMP_absolute_returns_three_cycles);
    //Indirect
    RUN_TEST(test_JMP_indirect_jumps_to_address);
    RUN_TEST(test_JMP_indirect_returns_five_cycles);
    RUN_TEST(test_JMP_indirect_page_boundary_bug);

    //JSR Tests
    //Absolute
    RUN_TEST(test_JSR_jumps_to_subroutine);
    RUN_TEST(test_JSR_pushes_return_address_high_byte);
    RUN_TEST(test_JSR_pushes_return_address_low_byte);
    RUN_TEST(test_JSR_decrements_stack_pointer_twice);
    RUN_TEST(test_JSR_returns_six_cycles);

    //RTS Tests
    //Implied
    RUN_TEST(test_RTS_returns_from_subroutine);
    RUN_TEST(test_RTS_increments_stack_pointer_twice);
    RUN_TEST(test_RTS_returns_six_cycles);

    //AND Tests
    //Addressing Mode
    //Immediate
    RUN_TEST(test_AND_immediate_performs_and_operation);
    RUN_TEST(test_AND_immediate_sets_zero_flag);
    RUN_TEST(test_AND_immediate_sets_negative_flag);
    RUN_TEST(test_AND_immediate_clears_zero_flag);
    RUN_TEST(test_AND_immediate_clears_negative_flag);
    RUN_TEST(test_AND_immediate_returns_two_cycles);

    //Zero page
    RUN_TEST(test_AND_zeropage_performs_and_operation);
    RUN_TEST(test_AND_zeropage_sets_zero_flag);
    RUN_TEST(test_AND_zeropage_sets_negative_flag);
    RUN_TEST(test_AND_zeropage_clears_zero_flag);
    RUN_TEST(test_AND_zeropage_clears_negative_flag);
    RUN_TEST(test_AND_zeropage_returns_three_cycles);

    //Absolute
    RUN_TEST(test_AND_absolute_performs_and_operation);
    RUN_TEST(test_AND_absolute_sets_zero_flag);
    RUN_TEST(test_AND_absolute_sets_negative_flag);
    RUN_TEST(test_AND_absolute_clears_zero_flag);
    RUN_TEST(test_AND_absolute_clears_negative_flag);
    RUN_TEST(test_AND_absolute_returns_four_cycles);

    //Zero page x
    RUN_TEST(test_AND_zeropage_x_ands_accumulator_with_x_offset_value);
    RUN_TEST(test_AND_zeropage_x_sets_zero_flag);
    RUN_TEST(test_AND_zeropage_x_sets_negative_flag);
    RUN_TEST(test_AND_zeropage_x_clears_zero_flag);
    RUN_TEST(test_AND_zeropage_x_clears_negative_flag);
    RUN_TEST(test_AND_zeropage_x_returns_four_cycles);
    RUN_TEST(test_AND_zeropage_x_wraps_around_zero_page);

    //Absolute page x
    RUN_TEST(test_AND_absolute_x_ands_accumulator_with_x_offset_value);
    RUN_TEST(test_AND_absolute_x_sets_zero_flag);
    RUN_TEST(test_AND_absolute_x_sets_negative_flag);
    RUN_TEST(test_AND_absolute_x_clears_zero_flag);
    RUN_TEST(test_AND_absolute_x_clears_negative_flag);
    RUN_TEST(test_AND_absolute_x_returns_four_cycles);
    RUN_TEST(test_AND_absolute_x_returns_five_cycles_on_page_cross);

    //Absolute page y
    RUN_TEST(test_AND_absolute_y_ands_accumulator_with_y_offset_value);

    return UNITY_END();
}
