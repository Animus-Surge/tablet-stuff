#pragma once

/*
PDAFontResearch - util.h

Utility macros and functions
*/

//Find the length of an array
#include <fstream>
#define len(arr) sizeof(arr) / sizeof(arr[i])

//Helpful reader functions for files

//Read a single byte
static inline unsigned char read_byte(std::ifstream& file) {
    char byte;
    file.read(&byte, 1);
    return static_cast<unsigned char>(byte);
}

//Read multiple bytes
static inline unsigned long int read_bytes(std::ifstream& file, int count) {
    unsigned long int value = 0;

    for (int i = 0; i < count; i++) {
        value <<= 8;
        value |= read_byte(file);
    }

    return value;
}
