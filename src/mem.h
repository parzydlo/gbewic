#pragma once

#include <stdint.h>

extern uint8_t mem[65536];

void memWrite(uint16_t address, uint8_t d8);
void memWrite(uint16_t address, uint8_t d16);
