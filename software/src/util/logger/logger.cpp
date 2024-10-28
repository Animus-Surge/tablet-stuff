/**
 * Logger class implementation
 */

#include "util/logger.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <cxxabi.h>
#include <execinfo.h>

#include <ctime>
#include <cstring>
#include <memory>
#include <string>

LogLevel log_level = LogLevel::INFO;

/**
 * Get the current time in the format "dd/mm/yy HH:MM:SS"
 * 
 * @return The current time
 */
char* _get_current_time() {
    char* timestr = (char*)malloc(32);
    std::time_t current_time = std::time(nullptr);

    std::strftime(timestr, 32, "%m/%d/%y %H:%M:%S", std::localtime(&current_time));

    return timestr;
}

/**
 * Get the name of the function that called the calling function
 * 
 * @return The name of the calling function
 */
std::string _get_calling_function() {
    return INVALID_FN_NAME;
}

// Logger functions
void set_log_level(LogLevel level) {
    log_level = level;
}
LogLevel get_log_level() {
    return log_level;
}

/**
 * Log a message to the console
 * 
 * @param level The log level of the message
 * @param message The message to log
 * @param ... The arguments to the message
 */
void log(LogLevel level, const char* message, ...) {
    //TODO: Add file logging
    if (level < log_level) {
        return;
    }

    va_list args;
    va_start(args, message);

    char* time = _get_current_time();

    printf("[%s ", time);
    printf("invalid]");

    switch(level) {
        case LogLevel::DEBUG:
            printf("(DBG ): ");
            break;
        case LogLevel::INFO:
            printf("(INFO): ");
            break;
        case LogLevel::WARNING:
            printf("(WARN): ");
            break;
        case LogLevel::ERROR:
            printf("(ERR ): ");
            break;
        case LogLevel::CRITICAL:
            printf("(CRIT): ");
            break;
        case LogLevel::TRACE:
            printf("(TRCE): ");
            break;
    }

    vprintf(message, args);
    printf("\n");

    va_end(args);

    free(time);
    //free(sender);
}
