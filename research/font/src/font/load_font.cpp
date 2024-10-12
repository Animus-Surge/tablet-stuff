#include "font.h"

#include <cstdlib>
#include <fstream>

#include <stdint.h>
#include <stdio.h>

#include "util.h"

FontDirectory directory;

bool loadFont(const char* path, const char* friendly_name) {
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        printf("Failed to open file: %s\n", path);
        return false;
    }

    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    LoadedFont *font = (LoadedFont*) malloc(sizeof(LoadedFont));

    FontDirectory *directory = (FontDirectory*) malloc(sizeof(FontDirectory));

    // Load font directory
    directory->scalerType = read_bytes(file, 4);
    directory->numTables = (unsigned int)read_bytes(file, 2);
    directory->searchRange = (unsigned int)read_bytes(file, 2);
    directory->entrySelector = (unsigned int)read_bytes(file, 2);
    directory->rangeShift = (unsigned int)read_bytes(file, 2);

    printf("scaler type: %lu\n", directory->scalerType);
    printf("num tables: %d\n", directory->numTables);
    printf("search range: %d\n", directory->searchRange);
    printf("entry selector: %d\n", directory->entrySelector);
    printf("range shift: %d\n", directory->rangeShift);

    //We have numTables, now we can load the tables
    directory->entries = (FontDirEntry*) malloc(sizeof(FontDirEntry) * directory->numTables);

    for (int i = 0; i < directory->numTables; i++) {
        printf("\n");

        directory->entries[i].tag[0] = read_byte(file);
        directory->entries[i].tag[1] = read_byte(file);
        directory->entries[i].tag[2] = read_byte(file);
        directory->entries[i].tag[3] = read_byte(file);
        directory->entries[i].tag[4] = '\0';
        directory->entries[i].checksum = read_bytes(file, 4);
        directory->entries[i].offset = read_bytes(file, 4);
        directory->entries[i].length = read_bytes(file, 4);

        printf("tag: %c%c%c%c\n", directory->entries[i].tag[0], directory->entries[i].tag[1], directory->entries[i].tag[2], directory->entries[i].tag[3]);
        printf("offset: %lu\n", directory->entries[i].offset);
        printf("length: %lu\n", directory->entries[i].length);
    }

    // Add directory to font
    font->dir = directory;

    // Load 'head' table
    HeadTable *head = (HeadTable*) malloc(sizeof(HeadTable));

    seekToTable(file, directory, "head");

    head->version = read_bytes(file, 4);
    head->fontRevision = read_bytes(file, 4);
    head->checksumAdjustment = read_bytes(file, 4);
    head->magicNumber = read_bytes(file, 4);
    head->flags = (unsigned short)read_bytes(file, 2);
    head->unitsPerEm = (unsigned short)read_bytes(file, 2);
    head->created = (long long)read_bytes(file, 8);
    head->modified = (long long)read_bytes(file, 8);
    head->xMin = (short)read_bytes(file, 2);
    head->yMin = (short)read_bytes(file, 2);
    head->xMax = (short)read_bytes(file, 2);
    head->yMax = (short)read_bytes(file, 2);
    head->macStyle = (unsigned short)read_bytes(file, 2);
    head->lowestRecPPEM = (unsigned short)read_bytes(file, 2);
    head->fontDirectionHint = (short)read_bytes(file, 2);
    head->indexToLocFormat = (short)read_bytes(file, 2);
    head->glyphDataFormat = (short)read_bytes(file, 2);

    printf("\n");
    printf("head table\n");
    printf("version: %lu\n", head->version);
    printf("font revision: %lu\n", head->fontRevision);
    printf("checksum adjustment: %lu\n", head->checksumAdjustment);
    printf("magic number: %lu\n", head->magicNumber);
    printf("flags: %d\n", head->flags);
    printf("units per em: %d\n", head->unitsPerEm);
    printf("created: %lld\n", head->created);
    printf("modified: %lld\n", head->modified);
    printf("x min: %d\n", head->xMin);
    printf("y min: %d\n", head->yMin);
    printf("x max: %d\n", head->xMax);
    printf("y max: %d\n", head->yMax);
    printf("mac style: %d\n", head->macStyle);
    printf("lowest rec ppem: %d\n", head->lowestRecPPEM);
    printf("font direction hint: %d\n", head->fontDirectionHint);
    printf("index to loc format: %d\n", head->indexToLocFormat);
    printf("glyph data format: %d\n", head->glyphDataFormat);

    // Add head table to font
    font->head = head;

    // CMAP
    CmapTable *cmap = (CmapTable*) malloc(sizeof(CmapTable));

    file.close();

    //Since no rendering is taking place, free memory
    free(directory->entries);
    free(directory);

    return true;
}
