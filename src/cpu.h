#pragma once
#include <stdint.h>

struct cpu_t {
    uint8_t registers[8];
    uint16_t pc;
    uint16_t sp;
}

extern cpu_t cpu;
