cmake_minimum_required(VERSION 3.26)
project(nes_emulator C)

set(CMAKE_C_STANDARD 11)

# ── Main emulator ──────────────────────────────────────────
add_executable(nes_emulator
        src/main.c
        src/cpu.c
        src/opcodes.c
)

# ── Test: CPU ──────────────────────────────────────────────
add_executable(test_cpu
        tests/test_cpu.c
        tests/unity/unity.c
        src/cpu.c
        src/opcodes.c
)

target_include_directories(test_cpu PRIVATE
        tests/unity       # so unity.h is found
        src               # so cpu.h is found
)