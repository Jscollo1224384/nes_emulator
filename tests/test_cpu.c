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
    
    return UNITY_END();
}
