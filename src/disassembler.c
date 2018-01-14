#include <stdint.h>
#include <stdio.h>

#include "cartridge.h"

uint8_t bitsAsValue(uint8_t* byte, int start, int end) {
    uint8_t mask = 0b00000000;
    uint8_t mask_setter = 0b00000001;
    for (int i = start; i <= end; i++) {
        mask |= (mask_setter << i);
    }
    uint8_t value = *byte & mask;
    value = value >> start;
    return value;
}

int parseInstruction(uint8_t* codebuffer, int pc) {
    uint8_t* code = &codebuffer[pc];
    char * opstring;
    int opbytes = 1;
    int x = bitsAsValue(code, 6, 7);
    int y = bitsAsValue(code, 3, 5);
    int z = bitsAsValue(code, 0, 2);
    int p = bitsAsValue(code, 4, 5);
    int q = bitsAsValue(code, 3, 3);
    
    if (*code != 0xCB) {
        switch (*code) {
            case 0x00:
                opstring = "NOP";
                break;
            case 0x01:
                opstring = "LD BC d16";
                opbytes = 3;
                break;
            case 0x02:
                opstring = "LD (BC) A";
                break;
            case 0x03:
                opstring = "INC BC";
                break;
            case 0x04:
                opstring = "INC B";
                break;
            case 0x05:
                opstring = "DEC B";
                break;
            case 0x06:
                opstring = "LD B d8";
                opbytes = 2;
                break;
            case 0x07:
                opstring = "RLCA";
                break;
            case 0x08:
                opstring = "LD (a16) SP";
                opbytes = 3;
                break;
            case 0x09:
                opstring = "ADD HL BC";
                break;
            case 0x0A:
                opstring = "LD A (BC)";
                break;
            case 0x0B:
                opstring = "DEC BC";
                break;
            case 0x0C:
                opstring = "INC C";
                break;
            case 0x0D:
                opstring = "DEC C";
                break;
            case 0x0E:
                opstring = "LD C d8";
                opbytes = 2;
                break;
            case 0x0F:
                opstring = "RRCA";
                break;
            case 0x10:
                opstring = "STOP 0";
                opbytes = 2;
                break;
            case 0x11:
                opstring = "LD DE d16";
                opbytes = 3;
                break;
            case 0x12:
                opstring = "LD (DE) A";
                break;
            case 0x13:
                opstring = "INC DE";
                break;
            case 0x14:
                opstring = "INC D";
                break;
            case 0x15:
                opstring = "DEC D";
                break;
            case 0x16:
                opstring = "LD D d8";
                opbytes = 2;
                break;
            case 0x17:
                opstring = "RLA";
                break;
            case 0x18:
                opstring = "JR r8";
                opbytes = 2;
                break;
            case 0x19:
                opstring = "ADD HL DE";
                break;
            case 0x1A:
                opstring = "LD A (DE)";
                break;
            case 0x1B:
                opstring = "DEC DE";
                break;
            case 0x1C:
                opstring = "INC E";
                break;
            case 0x1D:
                opstring = "DEC E";
                break;
            case 0x1E:
                opstring = "LD E d8";
                opbytes = 2;
                break;
            case 0x1F:
                opstring = "RRA";
                break;
            case 0x20:
                opstring = "JR NZ r8";
                opbytes = 2;
                break;
            case 0x21:
                opstring = "LD HL d16";
                opbytes = 3;
                break;
            case 0x22:
                opstring = "LD (HL+) A";
                break;
            case 0x23:
                opstring = "INC HL";
                break;
            case 0x24:
                opstring = "INC H";
                break;
            case 0x25:
                opstring = "DEC H";
                break;
            case 0x26:
                opstring = "LD H d8";
                opbytes = 2;
                break;
            case 0x27:
                opstring = "DAA";
                break;
            case 0x28:
                opstring = "JR Z r8";
                opbytes = 2;
                break;
            case 0x29:
                opstring = "ADD HL HL";
                break;
            case 0x2A:
                opstring = "LD A (HL+)";
                break;
            case 0x2B:
                opstring = "DEC HL";
                break;
            case 0x2C:
                opstring = "INC L";
                break;
            case 0x2D:
                opstring = "DEC D";
                break;
            case 0x2E:
                opstring = "LD L d8";
                opbytes = 2;
                break;
            case 0x2F:
                opstring = "CPL";
                break;
            case 0x30:
                opstring = "JR NC r8";
                opbytes = 2;
                break;
            case 0x31:
                opstring = "LD SP d16";
                opbytes = 3;
                break;
            case 0x32:
                opstring = "LD (HL-) A";
                break;
            case 0x33:
                opstring = "INC SP";
                break;
            case 0x34:
                opstring = "INC (HL)";
                break;
            case 0x35:
                opstring = "DEC (HL)";
                break;
            case 0x36:
                opstring = "LD (HL) d8";
                opbytes = 2;
                break;
            case 0x37:
                opstring = "SCF";
                break;
            case 0x38:
                opstring = "JR C r8";
                opbytes = 2;
                break;
            case 0x39:
                opstring = "ADD HL SP";
                break;
            case 0x3A:
                opstring = "LD A (HL-)";
                break;
            case 0x3B:
                opstring = "DEC SP";
                break;
            case 0x3C:
                opstring = "INC A";
                break;
            case 0x3D:
                opstring = "DEC A";
                break;
            case 0x3E:
                opstring = "LD A d8";
                opbytes = 2;
                break;
            case 0x3F:
                opstring = "CCF";
                break;
            case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45:
            case 0x47: case 0x48: case 0x49: case 0x4A: case 0x4B: case 0x4C:
            case 0x4D: case 0x4F: case 0x50: case 0x51: case 0x52: case 0x53:
            case 0x54: case 0x55: case 0x57: case 0x58: case 0x59: case 0x5A:
            case 0x5B: case 0x5C: case 0x5D: case 0x5F: case 0x60: case 0x61:
            case 0x62: case 0x63: case 0x64: case 0x65: case 0x67: case 0x68:
            case 0x69: case 0x6A: case 0x6B: case 0x6C: case 0x6D: case 0x6F:
            case 0x78: case 0x79: case 0x7A: case 0x7B: case 0x7C: case 0x7D:
            case 0x7F:
                opstring = "LD R R";
                break;
            case 0x46: case 0x56: case 0x66: case 0x4E: case 0x5E: case 0x6E:
            case 0x7E:
                opstring = "LD R (HL)";
                break;
            case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75:
            case 0x77:
                opstring = "LD (HL) R";
                break;
            case 0x76:
                opstring = "HALT";
                break;
            case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85:
            case 0x87:
                opstring = "ADD A R";
                break;
            case 0x88: case 0x89: case 0x8A: case 0x8B: case 0x8C:
            case 0x8D: case 0x8F:
                opstring = "ADC A R";
                break;
            case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95:
            case 0x97:
                opstring = "SUB R";
                break;
            case 0x98: case 0x99: case 0x9A: case 0x9B: case 0x9C: case 0x9D:
            case 0x9F:
                opstring = "SBC A R";
                break;
            case 0xA0: case 0xA1: case 0xA2: case 0xA3: case 0xA4: case 0xA5:
            case 0xA7:
                opstring = "AND R";
                break;
            case 0xA8: case 0xA9: case 0xAA: case 0xAB: case 0xAC: case 0xAD:
            case 0xAF:
                opstring = "XOR R";
                break;
            case 0xB0: case 0xB1: case 0xB2: case 0xB3: case 0xB4: case 0xB5:
            case 0xB7:
                opstring = "OR R";
                break;
            case 0xB8: case 0xB9: case 0xBA: case 0xBB: case 0xBC: case 0xBD:
            case 0xBF:
                opstring = "CP R";
                break;
            case 0x86:
                opstring = "ADD A (HL)";
                break;
            case 0x96:
                opstring = "SUB (HL)";
                break;
            case 0xA6:
                opstring = "AND (HL)";
                break;
            case 0xB6:
                opstring = "OR (HL)";
                break;
            case 0x8E:
                opstring = "ADC A (HL)";
                break;
            case 0x9E:
                opstring = "SBC A (HL)";
                break;
            case 0xAE:
                opstring = "XOR (HL)";
                break;
            case 0xBE:
                opstring = "CP (HL)";
                break;
            case 0xC0:
                opstring = "RET NZ";
                break;
            case 0xC1:
                opstring = "POP BC";
                break;
            case 0xC2:
                opstring = "JP NZ a16";
                opbytes = 3;
                break;
            case 0xC3:
                opstring = "JP a16";
                opbytes = 3;
                break;
            case 0xC4:
                opstring = "CALL NZ a16";
                opbytes = 3;
                break;
            case 0xC5:
                opstring = "PUSH BC";
                break;
            case 0xC6:
                opstring = "ADD A d8";
                opbytes = 2;
                break;
            case 0xC7:
                opstring = "RST 00H";
                break;
            case 0xC8:
                opstring = "RET Z";
                break;
            case 0xC9:
                opstring = "RET";
                break;
            case 0xCA:
                opstring = "JP Z a16";
                opbytes = 3;
                break;
            // 0xCB ALREADY HANDLED
            case 0xCC:
                opstring = "CALL Z a16";
                opbytes = 3;
                break;
            case 0xCD:
                opstring = "CALL a16";
                opbytes = 3;
                break;
            case 0xCE:
                opstring = "ADC A d8";
                opbytes = 2;
                break;
            case 0xCF:
                opstring = "RST 08H";
                break;
            case 0xD0:
                opstring = "RET NC";
                break;
            case 0xD1:
                opstring = "POP DE";
                break;
            case 0xD2:
                opstring = "JP NC a16";
                opbytes = 3;
                break;
            case 0xD3:
                // nothing
                break;
            case 0xD4:
                opstring = "CALL NC a16";
                opbytes = 3;
                break;
            case 0xD5:
                opstring = "PUSH DE";
                break;
            case 0xD6:
                opstring = "SUB d8";
                opbytes = 2;
                break;
            case 0xD7:
                opstring = "RST 10H";
                break;
            case 0xD8:
                opstring = "RET C";
                break;
            case 0xD9:
                opstring = "RETI";
                break;
            case 0xDA:
                opstring = "JP C a16";
                opbytes = 3;
                break;
            case 0xDB:
                // nothing
                break;
            case 0xDC:
                opstring = "CALL C a16";
                opbytes = 3;
                break;
            case 0xDD:
                // nothing
                break;
            case 0xDE:
                opstring = "SBC A d8";
                opbytes = 2;
                break;
            case 0xDF:
                opstring = "RST 18H";
                break;
            case 0xE0:
                opstring = "LDH (a8) A";
                opbytes = 2;
                break;
            case 0xE1:
                opstring = "POP HL";
                break;
            case 0xE2:
                opstring = "LD (C) A";
                opbytes = 2;
                break;
            case 0xE3:
                // nothing
                break;
            case 0xE4:
                // nothing
                break;
            case 0xE5:
                opstring = "PUSH HL";
                break;
            case 0xE6:
                opstring = "AND d8";
                opbytes = 2;
                break;
            case 0xE7:
                opstring = "RST 20H";
                break;
            case 0xE8:
                opstring = "ADD SP r8";
                opbytes = 2;
                break;
            case 0xE9:
                opstring = "JP (HL)";
                break;
            case 0xEA:
                opstring = "LD (a16) A";
                opbytes = 3;
                break;
            case 0xEB:
                // nothing
                break;
            case 0xEC:
                // nothing
                break;
            case 0xED:
                // nothing
                break;
            case 0xEE:
                opstring = "XOR d8";
                opbytes = 2;
                break;
            case 0xEF:
                opstring = "RST 28H";
                break;
            case 0xF0:
                opstring = "LDH A (a8)";
                opbytes = 2;
                break;
            case 0xF1:
                opstring = "POP AF";
                break;
            case 0xF2:
                opstring = "LD A (C)";
                opbytes = 2;
                break;
            case 0xF3:
                opstring = "DI";
                break;
            case 0xF4:
                // nothing
                break;
            case 0xF5:
                opstring = "PUSH AF";
                break;
            case 0xF6:
                opstring = "OR d8";
                opbytes = 2;
                break;
            case 0xF7:
                opstring = "RST 30H";
                break;
            case 0xF8:
                opstring = "LD HL SP+r8";
                opbytes = 2;
                break;
            case 0xF9:
                opstring = "LD SP HL";
                break;
            case 0xFA:
                opstring = "LD A a16";
                opbytes = 3;
                break;
            case 0xFB:
                opstring = "EI";
                break;
            case 0xFC:
                // nothing
                break;
            case 0xFD:
                // nothing
                break;
            case 0xFE:
                opstring = "CP d8";
                opbytes = 2;
                break;
            case 0xFF:
                opstring = "RST 38H";
                break;
            default:
                break;
        }
    } else {
        uint8_t* ncode = code + 1;
        opbytes = 2;
        switch (*ncode) {
            case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x05:
            case 0x07:
                opstring = "RLC R";
                break;
            case 0x08: case 0x09: case 0x0A: case 0x0B: case 0x0C: case 0x0D:
            case 0x0F:
                opstring = "RRC R";
                break;
            case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15:
            case 0x17:
                opstring = "RL R";
                break;
            case 0x18: case 0x19: case 0x1A: case 0x1B: case 0x1C: case 0x1D:
            case 0x1F:
                opstring = "RR R";
                break;
            case 0x20: case 0x21: case 0x22: case 0x23: case 0x24: case 0x25:
            case 0x27:
                opstring = "SLA R";
                break;
            case 0x28: case 0x29: case 0x2A: case 0x2B: case 0x2C: case 0x2D:
            case 0x2F:
                opstring = "SRA R";
                break;
            case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35:
            case 0x37:
                opstring = "SWAP R";
                break;
            case 0x38: case 0x39: case 0x3A: case 0x3B: case 0x3C: case 0x3D:
            case 0x3F:
                opstring = "SRL R";
                break;
            case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45:
            case 0x47: case 0x48: case 0x49: case 0x4A: case 0x4B: case 0x4C:
            case 0x4D: case 0x4F: case 0x50: case 0x51: case 0x52: case 0x53:
            case 0x54: case 0x55: case 0x57: case 0x58: case 0x59: case 0x5A:
            case 0x5B: case 0x5C: case 0x5D: case 0x5F: case 0x60: case 0x61:
            case 0x62: case 0x63: case 0x64: case 0x65: case 0x67: case 0x68:
            case 0x69: case 0x6A: case 0x6B: case 0x6C: case 0x6D: case 0x6F:
            case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75:
            case 0x77: case 0x78: case 0x79: case 0x7A: case 0x7B: case 0x7C:
            case 0x7D: case 0x7F:
                opstring = "BIT N R";
                break;
            case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85:
            case 0x87: case 0x88: case 0x89: case 0x8A: case 0x8B: case 0x8C:
            case 0x8D: case 0x8F: case 0x90: case 0x91: case 0x92: case 0x93:
            case 0x94: case 0x95: case 0x97: case 0x98: case 0x99: case 0x9A:
            case 0x9B: case 0x9C: case 0x9D: case 0x9F: case 0xA0: case 0xA1:
            case 0xA2: case 0xA3: case 0xA4: case 0xA5: case 0xA7: case 0xA8:
            case 0xA9: case 0xAA: case 0xAB: case 0xAC: case 0xAD: case 0xAF:
            case 0xB0: case 0xB1: case 0xB2: case 0xB3: case 0xB4: case 0xB5:
            case 0xB7: case 0xB8: case 0xB9: case 0xBA: case 0xBB: case 0xBC:
            case 0xBD: case 0xBF:
                opstring = "RES N R";
                break;
            case 0xC0: case 0xC1: case 0xC2: case 0xC3: case 0xC4: case 0xC5:
            case 0xC7: case 0xC8: case 0xC9: case 0xCA: case 0xCB: case 0xCC:
            case 0xCD: case 0xCF: case 0xD0: case 0xD1: case 0xD2: case 0xD3:
            case 0xD4: case 0xD5: case 0xD7: case 0xD8: case 0xD9: case 0xDA:
            case 0xDB: case 0xDC: case 0xDD: case 0xDF: case 0xE0: case 0xE1:
            case 0xE2: case 0xE3: case 0xE4: case 0xE5: case 0xE7: case 0xE8:
            case 0xE9: case 0xEA: case 0xEB: case 0xEC: case 0xED: case 0xEF:
            case 0xF0: case 0xF1: case 0xF2: case 0xF3: case 0xF4: case 0xF5:
            case 0xF7: case 0xF8: case 0xF9: case 0xFA: case 0xFB: case 0xFC:
            case 0xFD: case 0xFF:
                opstring = "SET N R";
                break;
            case 0x06:
                opstring = "RLC (HL)";
                break;
            case 0x0E:
                opstring = "RRC (HL)";
                break;
            case 0x16:
                opstring = "RL (HL)";
                break;
            case 0x1E:
                opstring = "RR (HL)";
                break;
            case 0x26:
                opstring = "SLA (HL)";
                break;
            case 0x2E:
                opstring = "SRA (HL)";
                break;
            case 0x36:
                opstring = "SWAP (HL)";
                break;
            case 0x3E:
                opstring = "SRL (HL)";
                break;
            case 0x46: case 0x4E: case 0x56: case 0x5E: case 0x66: case 0x6E:
            case 0x76: case 0x7E:
                opstring = "BIT N (HL)";
                break;
            case 0x86: case 0x8E: case 0x96: case 0x9E: case 0xA6: case 0xAE:
            case 0xB6: case 0xBE:
                opstring = "RES N (HL)";
                break;
            case 0xC6: case 0xCE: case 0xD6: case 0xDE: case 0xE6: case 0xEE:
            case 0xF6: case 0xFE:
                opstring = "SET N (HL)";
                break;
            default:
                break;
        }
    }

    printf("%s code: %02x x: %i y: %i z: %i p: %i q: %i", opstring, *code, x, y, z, p, q);
    printf("\n");
    return opbytes;
}

int main() {
    int pc = 0x150;
    size_t romlen;
    uint8_t* rombuf = loadCartridge("test.gb", &romlen);

    printf("ROM length: %zu \n", romlen);
    for(int i = 0; i < 16; i++) {
        pc += parseInstruction(rombuf, pc);
    }
    return 0;
}
