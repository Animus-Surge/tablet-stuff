/**
 * Logger class implementation
 */

#include "util/logger.h"

#include <stdarg.h>
#include <stdio.h>

#include <fstream>

LogLevel log_level = LogLevel::INFO;

void set_log_level(LogLevel level) {
    log_level = level;
}
LogLevel get_log_level() {
    return log_level;
}

void log(LogLevel level, const char* message, ...) {
    if (level < log_level) {
        return;
    }

    va_list args;
    va_start(args, message);

    switch (level) {
        case LogLevel::DEBUG:
            printf("[DEB ]: ");
            break;
        case LogLevel::INFO:
            printf("[INFO]: ");
            break;
        case LogLevel::WARNING:
            printf("[WARN]: ");
            break;
        case LogLevel::ERROR:
            printf("[ERR ]: ");
            break;
        case LogLevel::CRITICAL:
            printf("[CRIT]: ");
            break;
        }

    vprintf(message, args);
    printf("\n");

    va_end(args);
}
