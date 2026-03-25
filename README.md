# NES Emulator — Project Blueprint

> A test-driven NES emulator written in C. This document is the single source of truth for architecture, development phases, TDD workflow, and project conventions.

---

## Table of Contents

1. [Project Goals](#1-project-goals)
2. [Tech Stack](#2-tech-stack)
3. [Repository Structure](#3-repository-structure)
4. [Architecture Overview](#4-architecture-overview)
5. [TDD Workflow](#5-tdd-workflow)
6. [Development Phases](#6-development-phases)
    - [Phase 1 — 6502 CPU](#phase-1--6502-cpu)
    - [Phase 2 — Memory Bus & Cartridge](#phase-2--memory-bus--cartridge)
    - [Phase 3 — PPU (Graphics)](#phase-3--ppu-graphics)
    - [Phase 4 — Display Output](#phase-4--display-output)
    - [Phase 5 — Controller Input](#phase-5--controller-input)
    - [Phase 6 — APU (Audio)](#phase-6--apu-audio)
    - [Phase 7 — Additional Mappers](#phase-7--additional-mappers)
    - [Phase 8 — Debugging Tools](#phase-8--debugging-tools)
7. [Test Strategy](#7-test-strategy)
8. [Key Reference Resources](#8-key-reference-resources)
9. [Coding Conventions](#9-coding-conventions)
10. [Milestone Checklist](#10-milestone-checklist)

---

## 1. Project Goals

- Build a cycle-accurate NES emulator from scratch in C
- Use Test-Driven Development (TDD) throughout — no feature is implemented without a failing test first
- Learn NES hardware by building, not by reading alone
- Target compatibility with the most common NES game library (Mappers 0, 1, 2, 3)
- Keep the codebase modular so each hardware component is independently testable

---

## 2. Tech Stack

| Concern | Choice | Notes |
|---|---|---|
| Language | C (C11) | No C++ — keep it close to the metal |
| Build system | Make | Simple `make`, `make test`, `make run` |
| Test framework | Unity (ThrowTheSwitch) | Lightweight, no dependencies, C-native |
| Display | SDL2 | Cross-platform window + texture blitting |
| Audio | SDL2 Audio | Callback-based PCM output |
| Input | SDL2 Events | Keyboard and gamepad support |

### Minimum dependencies

```bash
# macOS
brew install sdl2

# Ubuntu/Debian
sudo apt install libsdl2-dev

# Unity test framework — vendored directly into /tests/unity/
# Download: https://github.com/ThrowTheSwitch/Unity
```

---

## 3. Repository Structure

```
nes-emulator/
├── README.md                  ← this file
├── Makefile
├── src/
│   ├── main.c                 ← entry point, SDL2 init, main loop
│   ├── cpu.c / cpu.h          ← 6502 CPU emulation (reset, step, dispatch)
│   ├── opcodes.c / opcodes.h  ← opcode handlers + 256-entry lookup table
│   ├── bus.c / bus.h          ← memory bus and address decoding
│   ├── ppu.c / ppu.h          ← picture processing unit
│   ├── apu.c / apu.h          ← audio processing unit
│   ├── cartridge.c / cartridge.h  ← iNES ROM loader
│   ├── mapper.h               ← mapper interface (function pointers)
│   ├── mappers/
│   │   ├── mapper000.c        ← NROM (no bank switching)
│   │   ├── mapper001.c        ← MMC1
│   │   ├── mapper002.c        ← UxROM
│   │   └── mapper003.c        ← CNROM
│   ├── controller.c / controller.h
│   └── display.c / display.h  ← SDL2 framebuffer rendering
├── tests/
│   ├── unity/                 ← Unity framework (vendored)
│   ├── test_cpu.c             ← one test per opcode
│   ├── test_bus.c
│   ├── test_ppu.c
│   ├── test_cartridge.c
│   ├── test_mappers.c
│   ├── test_apu.c
│   ├── test_controller.c
│   └── roms/                  ← test ROMs (nestest.nes, blargg suites)
├── roms/                      ← your personal ROM directory (gitignored)
└── docs/
    └── notes.md               ← your personal dev notes
```

### Makefile targets

```makefile
make         # build the emulator binary
make test    # build and run all unit tests
make run ROM=roms/game.nes   # run with a specific ROM
make clean   # remove build artifacts
```

---

## 4. Architecture Overview

The NES hardware maps cleanly to independent C modules. Each module owns its state as a struct and exposes a minimal function interface. The bus module is the connective tissue — it owns the memory map and dispatches reads/writes to the correct hardware component.

```
+------------------+       +------------------+
|    CPU (6502)    |<----->|   Memory Bus     |
+------------------+  R/W  |                  |
                           |  $0000 RAM       |
+------------------+       |  $2000 PPU regs  |
|      PPU         |<----->|  $4000 APU/IO    |
| (renders frame)  |       |  $8000 Cartridge |
+------------------+       +------------------+
                                    ^
+------------------+                |
|   Cartridge      |----------------+
| (ROM + Mapper)   |
+------------------+

+------------------+       +------------------+
|      APU         |       |   Controller     |
| (generates audio)|       |  ($4016/$4017)   |
+------------------+       +------------------+
```

### CPU memory map

| Address range | Mapped to |
|---|---|
| `$0000–$07FF` | 2KB internal RAM (mirrored to `$1FFF`) |
| `$2000–$2007` | PPU registers (mirrored to `$3FFF`) |
| `$4000–$4017` | APU and I/O registers |
| `$4020–$FFFF` | Cartridge space (PRG ROM, mapper registers) |

### PPU memory map

| Address range | Mapped to |
|---|---|
| `$0000–$1FFF` | Pattern tables (CHR ROM/RAM) |
| `$2000–$2FFF` | Nametables (VRAM, mirrored by mapper) |
| `$3F00–$3F1F` | Palette RAM |

---

## 5. TDD Workflow

Every feature in this project follows the Red → Green → Refactor cycle. The rule is strict: **no implementation code is written without a failing test first.**

### The cycle

```
1. RED    — Write a test that describes the behavior you want.
             Run it. Watch it fail. The failure message is your spec.

2. GREEN  — Write the minimum code needed to make the test pass.
             No extra logic. No "while I'm here" additions.

3. REFACTOR — Clean up the implementation.
              Extract helpers, rename variables, remove duplication.
              Tests must stay green throughout.

4. REPEAT — Move to the next behavior.
```

### Minimal test harness

Rather than pulling in a heavy framework, Unity is a single `.c` + `.h` pair. A test file looks like this:

```c
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

void test_LDA_immediate_sets_zero_flag(void) {
    CPU cpu;
    uint8_t mem[0x10000] = {0};
    mem[0xFFFC] = 0x00; mem[0xFFFD] = 0x80;
    mem[0x8000] = 0xA9; mem[0x8001] = 0x00; // LDA #$00

    cpu_reset(&cpu, mem);
    cpu_step(&cpu, mem);

    TEST_ASSERT_EQUAL(1, cpu.Z);
    TEST_ASSERT_EQUAL(0, cpu.N);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_LDA_immediate_loads_accumulator);
    RUN_TEST(test_LDA_immediate_sets_zero_flag);
    return UNITY_END();
}
```

### TDD rules for this project

- One test file per hardware module
- One test function per opcode/behavior — never bundle multiple assertions about different behaviors in one test
- Tests must not depend on SDL2 or any display output — hardware logic is pure C with no side effects on the UI
- Controller tests mock button state directly on the struct — no SDL2 in tests
- If a test needs a fake ROM, build a minimal byte array inline — never load a file from disk in a unit test
- For indexed addressing modes (zero page X, zero page Y), always include a wrap-around test — prove the address wraps within the page rather than spilling into the next page
- When testing clear flag behavior, always assert both the flag being cleared AND the other flag staying in the expected state

---

## 6. Development Phases

### Phase 1 — 6502 CPU

**Goal:** A fully correct 6502 CPU that passes nestest.

The CPU is the safest place to start because it is completely self-contained and has a world-class test ROM (nestest.nes) that generates a golden log of 26,554 CPU cycles you can diff against.

**What to build:**

- `CPU` struct: registers `A`, `X`, `Y`, `SP`, `PC`; status flags `N`, `V`, `B`, `D`, `I`, `Z`, `C`
- `cpu_reset()` — load PC from reset vector at `$FFFC/$FFFD`
- `cpu_step()` — fetch opcode, decode, execute, return cycles consumed
- All official opcodes (~151) with correct cycle counts
- All addressing modes: implied, accumulator, immediate, zero page, zero page X/Y, absolute, absolute X/Y, indirect, indexed indirect `(X)`, indirect indexed `(Y)`, relative
- Interrupts: NMI, IRQ, RESET, BRK

**TDD approach:**

Write one test per opcode. Start with the simplest: `LDA`, `STA`, `LDX`, `STX`, `LDY`, `STY`. Then branches (`BEQ`, `BNE`, etc.), then arithmetic, then the tricky ones (`ROR`, `ROL`, `LSR`, `ASL` with carry flag side effects).

**Validation:**

```bash
# Run your emulator against nestest.nes in a headless mode
# Compare your CPU log output line-by-line against nestest.log
diff my_cpu.log tests/roms/nestest.log
```

**Done when:** `diff` is clean for all 26,554 lines of nestest.log.

---

### Phase 2 — Memory Bus & Cartridge

**Goal:** Load a real iNES ROM file, parse it correctly, and have the CPU execute code from cartridge space.

**What to build:**

- `Bus` struct: holds pointers to RAM, PPU, APU, cartridge; dispatches `bus_read()` / `bus_write()` to the correct region
- `Cartridge` struct: iNES header parser, PRG ROM and CHR ROM buffers, mapper ID
- `Mapper` interface: a struct of function pointers `(read, write)` — each mapper implements this interface
- `mapper000.c` — NROM: direct PRG ROM mapping, no bank switching

**iNES header format:**

```
Bytes 0–3:  "NES\x1A" magic
Byte 4:     PRG ROM size (units of 16KB)
Byte 5:     CHR ROM size (units of 8KB)
Byte 6:     Flags (mirroring, battery, trainer, mapper low nibble)
Byte 7:     Flags (mapper high nibble, NES 2.0 indicator)
```

**TDD approach:**

Test `bus_read()` and `bus_write()` for each memory region independently. Test the iNES parser with a hand-crafted byte array — not a real ROM file. Test Mapper 0's read/write logic in isolation.

**Done when:** CPU executes from PRG ROM correctly with Mapper 0.

---

### Phase 3 — PPU (Graphics)

**Goal:** Render a correct 256×240 pixel frame to a framebuffer array.

This is the hardest phase. Budget significant time here. Read the NesDev PPU wiki page carefully before writing a line of code.

**What to build:**

- `PPU` struct: internal registers (`v`, `t`, `x`, `w`), OAM (256 bytes), secondary OAM, palette RAM, nametable VRAM, cycle and scanline counters, framebuffer (`uint32_t pixels[256*240]`)
- PPU register read/write handlers for `$2000`–`$2007` (mapped through the bus)
- Scanline renderer: background tile fetching, sprite evaluation, pixel compositing
- VBLANK flag + NMI generation (fires at scanline 241, cleared at scanline 261)
- Sprite 0 hit detection

**Scanline timing (simplified):**

```
Scanlines 0–239:   Visible — render background + sprites
Scanline 240:      Post-render idle
Scanlines 241–260: VBLANK — set flag, fire NMI on cycle 1 of scanline 241
Scanline 261:      Pre-render — clear flags, reload scroll
Each scanline = 341 PPU clock cycles
PPU runs 3 cycles per CPU cycle
```

**TDD approach:**

Test PPU register side effects (writing to `$2006` twice updates the VRAM address, reading `$2007` returns buffered data, etc.). Use blargg's `ppu_vbl_nmi` test ROM for NMI timing. For pixel output, use framebuffer snapshot tests — render one frame and compare the pixel array byte-for-byte against a known-good output.

**Done when:** Donkey Kong or Super Mario Bros. renders a correct title screen.

---

### Phase 4 — Display Output

**Goal:** Open an SDL2 window and blit the PPU framebuffer at 60fps.

This phase is deliberately thin. Keep all rendering logic in `display.c` and away from the PPU — the PPU writes pixels to an array, the display module reads that array.

**What to build:**

- `SDL_Window` + `SDL_Renderer` + `SDL_Texture` (256×240, `SDL_PIXELFORMAT_ARGB8888`)
- `display_update(uint32_t *pixels)` — upload framebuffer to texture and present
- Frame timing loop: target 16.639ms per frame (60.0988 Hz, the NES actual refresh rate)
- Window scaling: render 256×240 upscaled to at least 512×480

**TDD approach:**

Display code is not unit-tested directly (SDL2 requires a window). Keep it so thin that it obviously cannot break. Integration-test visually.

**Done when:** A game renders at correct speed with no tearing.

---

### Phase 5 — Controller Input

**Goal:** Read SDL2 keyboard events and expose them as NES controller button state at `$4016`/`$4017`.

**NES controller protocol:**

Writing `1` then `0` to `$4016` latches the current button state. Each subsequent read of `$4016` shifts out one button in order: A, B, Select, Start, Up, Down, Left, Right.

**What to build:**

- `Controller` struct: `uint8_t buttons` (one bit per button), `uint8_t shift_register`, `uint8_t strobe`
- `controller_write()` — latch on strobe transition `1→0`
- `controller_read()` — shift out next bit, return bit 0
- SDL2 event polling to set/clear bits in `buttons`

**TDD approach:**

Test the strobe latch and 8-bit shift-out sequence entirely without SDL2 — set `buttons` directly on the struct and assert the correct bit sequence comes out of `controller_read()`.

**Done when:** You can play Super Mario Bros. with keyboard controls.

---

### Phase 6 — APU (Audio)

**Goal:** Generate correct audio output for the five NES sound channels.

The APU can be deferred until after Phase 5 — the emulator is fully playable without sound. Add it once gameplay is working.

**What to build:**

- Two pulse wave channels (with envelope, sweep, length counter)
- Triangle wave channel
- Noise channel (linear feedback shift register)
- DMC (delta modulation) channel — optional for initial pass
- SDL2 audio callback that mixes channels and outputs PCM samples at 44100 Hz
- Frame counter (`$4017`) — sequences envelope and length counter clocks

**TDD approach:**

Test each channel's timer tick and output value independently. Test envelope decay step counts. Test length counter halt/reload. Use blargg's `apu_test` ROMs for integration validation. For sample output, compare generated PCM buffers against golden WAV files.

**Done when:** blargg `apu_test` ROMs pass; game music and sound effects are recognizable.

---

### Phase 7 — Additional Mappers

**Goal:** Support the mappers that cover the majority of commercial NES titles.

| Mapper | Name | Notable games | % of library |
|---|---|---|---|
| 0 | NROM | Donkey Kong, Super Mario Bros. | ~10% |
| 1 | MMC1 | Zelda, Metroid, Mega Man 2 | ~28% |
| 2 | UxROM | Contra, Mega Man, Castlevania | ~10% |
| 3 | CNROM | Gradius, Arkanoid | ~6% |

Mappers 0–3 together cover roughly 54% of the commercial NES library.

**What to build for each mapper:**

- Register write handler (the CPU writes to specific address ranges to control bank switching)
- PRG ROM and CHR ROM read/write with correct bank offsets
- Mirroring mode changes (MMC1 can switch between horizontal, vertical, and single-screen mirroring)

**TDD approach:**

Each mapper gets its own test file. Test that writing the correct value to a mapper register results in the expected bank being mapped at the expected address. Test all mirroring modes for MMC1.

**Done when:** The top 20 NES games by popularity run correctly.

---

### Phase 8 — Debugging Tools

**Goal:** Build visibility into the emulator so bugs are diagnosable.

These tools save enormous time during development. Build them incrementally — add each one when you first need it, not all upfront.

**CPU logger:**

```
C  A  X  Y  SP  NV-BDIZC   Cycles
8000  A9 42     LDA #$42    A:00 X:00 Y:00 P:24 SP:FD  CYC:7
8002  85 00     STA $00     A:42 X:00 Y:00 P:24 SP:FD  CYC:9
```

This format matches nestest.log exactly, enabling line-by-line diffing.

**PPU register viewer:** Print nametable, attribute table, and OAM contents on demand.

**Memory inspector:** `dump_mem(addr, len)` — hex + ASCII, useful for diagnosing mapper bugs.

**Palette viewer:** Render the current 32-color palette as colored blocks.

**Step mode:** Run one CPU instruction at a time on keypress — invaluable for tracing PPU timing bugs.

**Test ROMs to keep in `tests/roms/`:**

| ROM | Tests |
|---|---|
| `nestest.nes` | CPU — all official opcodes |
| `blargg/cpu_timing_test.nes` | CPU instruction timing |
| `blargg/ppu_vbl_nmi.nes` | PPU VBLANK and NMI timing |
| `blargg/sprite_hit_tests.nes` | Sprite 0 hit |
| `blargg/apu_test.nes` | APU channel behavior |

---

## 7. Test Strategy

### Rules

- Every hardware behavior gets a test before implementation
- Tests are pure C — no SDL2 dependency in any test
- Each test is one behavior, one assertion group — if you name a test `test_X_and_Y`, split it
- The nestest golden log is the ground truth for CPU correctness — treat any diff as a bug
- Snapshot tests (framebuffer, APU PCM) are stored as binary files in `tests/snapshots/`

### Running tests

```bash
make test              # run all test suites
make test_cpu          # run only CPU tests
make test_ppu          # run only PPU tests
```

### Test file naming

| Module | Test file |
|---|---|
| CPU | `tests/test_cpu.c` |
| Bus / memory | `tests/test_bus.c` |
| Cartridge | `tests/test_cartridge.c` |
| PPU | `tests/test_ppu.c` |
| APU | `tests/test_apu.c` |
| Controllers | `tests/test_controller.c` |
| Mappers | `tests/test_mappers.c` |

---

## 8. Key Reference Resources

| Resource | URL | Use for |
|---|---|---|
| NesDev Wiki | https://www.nesdev.org/wiki/ | Everything — the authoritative NES reference |
| 6502 opcode table | https://www.nesdev.org/obelisk-6502-guide/ | Opcode matrix, cycle counts, flags |
| nestest ROM + log | https://www.nesdev.org/nestest.txt | CPU validation golden log |
| blargg test ROMs | https://www.nesdev.org/wiki/Emulator_tests | PPU, APU, CPU timing test ROMs |
| NES rendering explained | https://www.nesdev.org/wiki/PPU_rendering | Cycle-by-cycle PPU render pipeline |
| iNES format spec | https://www.nesdev.org/wiki/INES | ROM file format |
| Mapper database | https://www.nesdev.org/wiki/Mapper | Every mapper, register behavior |

---

## 9. Coding Conventions

- File names: `snake_case.c` / `snake_case.h`
- Struct names: `PascalCase` (e.g., `CPU`, `PPU`, `Cartridge`)
- Function names: `module_verb_noun` (e.g., `cpu_step`, `bus_read`, `ppu_reset`)
- Constants and macros: `UPPER_SNAKE_CASE`
- All hardware registers and addresses as hex literals: `0x2000`, never `8192`
- No global mutable state — all state lives in structs passed by pointer
- Header files expose only what other modules need — keep internals in `.c`
- Every function that can fail returns an `int` status code (0 = success)

### Opcode dispatch — lookup table pattern

Opcodes are implemented as a 256-entry function pointer table in `opcodes.c`. Each entry maps an opcode byte to a handler function. `cpu_step` fetches the opcode, looks up the handler, and calls it — no switch statement.

```c
// opcodes.h
typedef int (*OpcodeHandler)(CPU *cpu, uint8_t *mem);

typedef struct {
    OpcodeHandler handler;
    const char *name;   // for debugging and CPU logger
} OpcodeEntry;

extern const OpcodeEntry opcode_table[256];
```

```c
// opcodes.c — each handler fetches its own operand bytes
int op_lda_immediate(CPU *cpu, uint8_t *mem) {
    cpu->A = mem[cpu->PC++];
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) ? 1 : 0;
    return 2;
}

const OpcodeEntry opcode_table[256] = {
    [0xA9] = { op_lda_immediate, "LDA immediate" },
    [0xA5] = { op_lda_zero_page, "LDA zero page" },
    // ...
};
```

Key rules for handlers:
- Each handler fetches its own operand bytes via `cpu->PC++` — `cpu_step` does not pre-fetch
- Cycle count is returned by the handler, not stored in the table — it lives in one place
- Page crossing penalty is calculated inside the handler for modes that support it
- Zero page indexed modes cast the address sum to `uint8_t` to enforce wrap-around behaviour

### Example module interface

```c
// cpu.h — public interface only
#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct {
    uint8_t  A, X, Y, SP;
    uint16_t PC;
    // Status flags
    uint8_t N, V, B, D, I, Z, C;
    uint64_t cycles;
} CPU;

void cpu_reset(CPU *cpu, uint8_t *mem);
int  cpu_step(CPU *cpu, uint8_t *mem);   // returns cycles consumed

#endif
```

---

## 10. Milestone Checklist

Use this to track progress. Each milestone should have passing tests before you move on.

- [x] **M1** — Unity test framework wired up; `make test` runs and passes a hello-world test
- [x] **M2** — LDA all 8 addressing modes fully tested; STA zero page, zero page X, absolute fully tested; opcode dispatch refactored to 256-entry lookup table
- [ ] **M3** — Remaining Load/Store opcodes: `LDX`, `LDY`, `STX`, `STY` all addressing modes passing tests
- [ ] **M4** — All branch instructions correct (all 8 branch opcodes + cycle penalty for page cross)
- [ ] **M5** — All 151 official opcodes passing; nestest.log diff is clean
- [ ] **M6** — iNES ROM parser correct; Mapper 0 PRG ROM reads working
- [ ] **M7** — PPU registers read/write with correct side effects; NMI fires at correct scanline
- [ ] **M8** — Background rendering correct; Donkey Kong title screen renders
- [ ] **M9** — Sprite rendering correct; sprites visible and positioned correctly
- [ ] **M10** — SDL2 window opens; framebuffer blits at 60fps
- [ ] **M11** — Controller input working; Super Mario Bros. playable
- [ ] **M12** — MMC1 (Mapper 1) implemented; The Legend of Zelda boots
- [ ] **M13** — UxROM (Mapper 2) implemented; Contra playable
- [ ] **M14** — APU pulse and triangle channels; basic music audible
- [ ] **M15** — APU noise + DMC; audio complete
- [ ] **M16** — CPU step debugger and memory inspector working

---

*This blueprint is a living document. Update it as the project evolves — add notes on tricky bugs, architecture decisions you changed, and things you'd do differently.*
