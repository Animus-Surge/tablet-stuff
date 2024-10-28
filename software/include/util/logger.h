#pragma once

/*
pda logger.h
Logging system
*/

#include <stdio.h>

#define INVALID_FN_NAME "invalid"

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
    TRACE
};

extern LogLevel log_level;

void set_log_level(LogLevel level);
LogLevel get_log_level();

void log(LogLevel level, const char* message, ...);
