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
char* _get_calling_function() {
    const int backtrace_frames = 10;

    void* callstack[backtrace_frames];
    int frames = backtrace(callstack, backtrace_frames);
    char** strs = backtrace_symbols(callstack, frames);

    char* calling_function = (char*)malloc(128);

    if(strs) {
        for (int i = 0; i < frames; i++) {
            //Demangle the function name
            char *mangled_name = strchr(strs[i], '(');
            if (mangled_name) {
                mangled_name++;
                char *end = strchr(mangled_name, '+');
                if (end) {
                    *end = '\0';
                    int status;
                    char *real_name = abi::__cxa_demangle(mangled_name + 1, 0, 0, &status);
                    if (status == 0 && real_name) {
                        snprintf(calling_function, 128, "%s", real_name);
                        free(real_name);
                    } else {
                        snprintf(calling_function, 128, "%s", mangled_name + 1);
                    }
                }
            }
        }
    }

    free(strs);

    free(calling_function);

    return "INVALID";
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

    char* sender = _get_calling_function();
    char* time = _get_current_time();

    printf("[%s ", time);
    printf("%s]", sender);

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
