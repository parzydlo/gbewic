#pragma once

#include <stdint.h>

uint8_t bitsAsValue(uint8_t* byte, int start, int end);

int parseInstruction(uint8_t* codebuffer, int pc);
