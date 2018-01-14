#include <stdint.h>

#include "mem.h"

void memWrite(uint16_t address, uint8_t d8) {
    mem[address] = d8;
}

void memWrite(uint16_t address, uint16_t d16) {
    uint8_t low = d16 & 0xFF;
    uint8_t high = (d16 >> 8);
    memWrite(address, high);
    memWrite(address + 1, low);
}
