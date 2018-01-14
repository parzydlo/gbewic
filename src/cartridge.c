#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cartridge.h"

uint8_t* loadCartridge(char* filename, size_t* length) {
    FILE* fileptr;
    uint8_t* buffer;

    fileptr = fopen(filename, "rb");
    fseek(fileptr, 0, SEEK_END);
    *length = ftell(fileptr);
    rewind(fileptr);
    buffer = (uint8_t*)malloc((*length) * 8);
    fread(buffer, *length, 1, fileptr);
    fclose(fileptr);
    return buffer;
}
