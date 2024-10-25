/**
 * PDA entry point
 */

#include "pda.h"

#include "util/logger.h"

#include <stdio.h>

int main() {
    // Set stdout to line buffered, allows printing in real time without SDL blocking
    setvbuf(stdout, NULL, _IOLBF, 0);

    log(LogLevel::INFO, "Hello, World!");
    log(LogLevel::INFO, "PDA VERSION %s", PDA_VERSION_STRING);

}
