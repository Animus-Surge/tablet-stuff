#include "font.h"

#include <fstream>

#include <stdint.h>
#include <stdio.h>

FontDirectory directory;

uint8_t readByte(std::ifstream& file) {
    char byte;
    file.read(&byte, 1);
    return static_cast<uint8_t>(byte);
}

uint32_t readBytes(std::ifstream& file, int count) {
    uint32_t value = 0;

    for (int i = 0; i < count; i++) {
        value <<= 8;
        value |= readByte(file);
    }

    return value;
}

bool loadFont(const char* path) {
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        printf("Failed to open file: %s\n", path);
        return false;
    }

    // Read font directory table
    FontDirectory directory;

    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    directory.scalerType = readBytes(file, 4);
    directory.numTables = static_cast<unsigned short>(readBytes(file, 2));
    directory.searchRange = static_cast<unsigned short>(readBytes(file, 2));
    directory.entrySelector = static_cast<unsigned short>(readBytes(file, 2));
    directory.rangeShift = static_cast<unsigned short>(readBytes(file, 2));

    printf("Scaler type: %lu\n", directory.scalerType);
    printf("Number of tables: %hu\n", directory.numTables);
    printf("Search range: %hu\n", directory.searchRange);
    printf("Entry selector: %hu\n", directory.entrySelector);
    printf("Range shift: %hu\n", directory.rangeShift);

    //Begin reading tables
    FontDirectoryEntry entries[directory.numTables];

    for(int i = 0; i < directory.numTables; i++) {
        entries[i].tag[0] = readByte(file);
        entries[i].tag[1] = readByte(file);
        entries[i].tag[2] = readByte(file);
        entries[i].tag[3] = readByte(file);
        entries[i].tag[4] = '\0';
        entries[i].checkSum = readBytes(file, 4);
        entries[i].offset = readBytes(file, 4);
        entries[i].length = readBytes(file, 4);

        printf("Table %d\n", i);
        printf("Tag: %s\n", entries[i].tag);
        printf("Check sum: %u\n", entries[i].checkSum);
        printf("Offset: %u\n", entries[i].offset);
        printf("Length: %u\n", entries[i].length);
    }

    return true;
}
