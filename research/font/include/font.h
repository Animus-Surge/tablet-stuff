#pragma once

/*
PDAFontResearch - font.h

Declarations and macros for font rendering
*/

#include <fstream>

#include <SDL2/SDL.h>

#include <stdint.h>

//Font directory table
#pragma pack(push, 1)
struct FontDirectory {
    unsigned long int scalerType;
    unsigned short numTables;
    unsigned short searchRange;
    unsigned short entrySelector;
    unsigned short rangeShift;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct FontDirectoryEntry {
    char tag[5];
    unsigned int checkSum;
    unsigned int offset;
    unsigned int length;
};
#pragma pack(pop)

//Font header [head]

//Character to glyph mapping [cmap]

//Font glyphs [glyf]
struct GlyphBase {
    short numberOfContours;
    short xMin;
    short yMin;
    short xMax;
    short yMax;
};

struct GlyphSimple {
    GlyphBase base;
    short* endPtsOfContours;
    short instructionLength;
    char* instructions;
    char* flags;
    short* xCoordinates;
    short* yCoordinates;
};

struct GlyphComposite {
    GlyphBase base;
    short flags;
    short glyphIndex;
    short argument1;
    short argument2;
    unsigned short transformation;
};

bool loadFont(const char* path);
void renderText(const char* text, int x, int y, int size);
