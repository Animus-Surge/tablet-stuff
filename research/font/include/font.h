#pragma once

/*
PDAFontResearch - font.h

Declarations and macros for font rendering
*/

#include <fstream>

#include <SDL2/SDL.h>

#include <stdint.h>

//Font directory table
struct FontDirEntry {
    char tag[5];
    unsigned long int checksum;
    unsigned long int offset;
    unsigned long int length;
};
struct FontDirectory {
    unsigned long int scalerType;
    unsigned short numTables;
    unsigned short searchRange;
    unsigned short entrySelector;
    unsigned short rangeShift;
    FontDirEntry* entries;
};

//Font header [head]
struct HeadTable {
    unsigned long int version;
    unsigned long int fontRevision;
    unsigned long int checksumAdjustment;
    unsigned long int magicNumber;
    unsigned short flags;
    unsigned short unitsPerEm;
    long long created;
    long long modified;
    short xMin;
    short yMin;
    short xMax;
    short yMax;
    unsigned short macStyle;
    unsigned short lowestRecPPEM;
    short fontDirectionHint;
    short indexToLocFormat;
    short glyphDataFormat;
};

//Character to glyph mapping [cmap]
struct CmapEntry {

};
struct CmapTable {
    unsigned short version;
    unsigned short numTables;
    CmapEntry* entries;
};

//Font glyphs [glyf]
struct Glyph {
    short numberOfContours;
    short xMin;
    short yMin;
    short xMax;
    short yMax;
};

struct LoadedFont {
    FontDirectory *dir;
    HeadTable *head;
};

// Basic functions

//Load a new font; return true if OK, false otherwise
bool loadFont(const char* path, const char* friendly_name);
//Render text
void renderText(const char* friendly_name, const char* text, int x, int y, int size);
//Take font with friendly_name and free all resources associated with it
void unloadFont(const char* friendly_name);

// Utility functions
void seekToTable(std::ifstream& file, FontDirectory* dir, const char* tag);
