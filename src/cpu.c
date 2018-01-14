#include <stdint.h>
#include <string.h>

#include "disassembler.h"
#include "mem.h"

#include "cpu.h"

// registers
#define B 0x000
#define C 0x001
#define D 0x010
#define E 0x011
#define H 0x100
#define L 0x101
#define A 0x110
#define F 0x111

// flag bits
#define ZERO 7
#define SUBTRACT 6
#define HALFCARRY 5
#define CARRY 4

uint8_t regRead(int y) {
    uint8_t d8;
    memcpy(&d8, cpu.registers[y], sizeof(d8));
    return d8;
}

uint16_t regpairRead(int p) {
    uint16_t d16;
    memcpy(&d16, cpu.registers[p*2], sizeof(d16));
    return d16;
}

void regWrite(int y, uint8_t d8) {
    memcpy(cpu.registers[y], &d8, sizeof(d8));
}

void regpairWrite(int p, uint16_t d16) {
    memcpy(cpu.registers[p*2], &d16, sizeof(d16));
}

int getFlag(int f) {
    uint8_t mask = 0b00000001;
    uint8_t val = regRead(F);
    int bit = (val >> f) & mask;
    return bit;
}

void setFlag(int f) {
    uint8_t mask = 0b00000001;
    mask = mask << f;
    uint8_t val = regRead(F);
    val |= mask;
    regWrite(F, val);
}

void resetFlag(int f) {
    uint8_t mask = 0b00000001;
    mask = mask << f;
    uint8_t val = regRead(F);
    val &= ~(mask);
    regWrite(F, val);
}

// do nothing
void NOP() {}

// load 16 bits into register pair
void LDRPd16(int p, uint16_t d16) {
    regpairWrite(p, d16);
}

// load accumulator value into memory address stored in register pair
void LDdRPA(int p) {
    uint16_t addr = regpairRead(p);
    memWrite(addr, regRead(A));
}

// load register into register
void LDRR(int y, int z) {
    uint8_t val = regRead(z);
    regWrite(y, val);
}

// increment register
void INCR(int y) {
    uint8_t val = regRead(y) + 1;
    regWrite(y, val);
}

// increment register pair
void INCRP(int p) {
    uint16_t val = regpairRead(p) + 1;
    regpairWrite(p, val);
}

// decrement register
void DECR(int y) {
    uint8_t val = regRead(y) - 1;
    regWrite(y, val);
}

// decrement register pair
void DECRP(int p) {
    uint16_t val = regpairRead(p) - 1;
    regpairWrite(p, val);
}

// rotate accumulator left with carry
void RLCA() {
    uint8_t val = regRead(A);
    uint8_t tail = bitsAsValue(&val, 7, 7);
    val = val << 1;
    // bit 0 is unset after the shift
    // so adding tail always works
    val += tail;
    regWrite(A, val);
    if (tail) {
        setFlag(CARRY);
    } else {
        resetFlag(CARRY);
    }
}

// rotate accumulator left
void RLA() {
    uint8_t val = regRead(A);
    int c = getFlag(CARRY);
    uint8_t tail = bitsAsValue(&val, 7, 7);
    val = val << 1;
    // same as RLCA but bit 0 gets
    // old carry flag value instead
    val += c;
    if (tail) {
        setFlag(CARRY);
    } else {
        resetFlag(CARRY);
    }
}

// rotate accumulator right with carry
void RRCA() {
    uint8_t val = regRead(A);
    uint8_t tail = bitsAsValue(&val, 0, 0);
    tail << 7;
    val = val >> 1;
    val += tail;
    regWrite(A, val);
    if (tail) {
        setFlag(CARRY);
    } else {
        resetFlag(CARRY);
    }
}
