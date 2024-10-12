#include "font.h"
#include "util.h"

#include <cstring>
#include <fstream>


void seekToTable(std::ifstream& file, FontDirectory* dir, const char* tag) {
    for(int i = 0; i < dir->numTables; i++) {
        FontDirEntry* entry = &dir->entries[i];
        if(strcmp(entry->tag, tag) == 0) {
            file.seekg(entry->offset, std::ios::beg);
            return;
        }
    }
}
