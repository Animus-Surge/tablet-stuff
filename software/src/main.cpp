/**
 * PDA entry point
 */

#include "pda.h"

#include "engine/engine.h"
#include "util/logger.h"

#include <cxxabi.h>

#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Engine* engine;

//Signal handler
void signal_handler(int signal) {
    printf("\n"); // Print a newline after the ^C, makes it more readable
    switch(signal) {
        case SIGINT:
            //SIGINT: Interrupt request, sent to the program; we need to cleanup and exit gracefully
            log(LogLevel::INFO, "RECV SIGINT; Shutting down...");
            //TODO: cleanup
            exit(EXIT_SUCCESS);
        case SIGTERM:
            //SIGTERM: Termination request, sent to the program; we need to cleanup and exit immediately
            log(LogLevel::INFO, "Received SIGTERM");
            //TODO: cleanup
            exit(EXIT_SUCCESS);
        case SIGSEGV: {
            //SIGSEGV: Segmentation fault; we need to print a stack trace and exit
            log(LogLevel::CRITICAL, "RECV SIGSEGV; Segmentation fault detected");

            log(LogLevel::TRACE, "BEGIN TRACE:");

            //BEGIN: stack trace
            void* callstack[128];
            int frames = backtrace(callstack, 128);
            char** strs = backtrace_symbols(callstack, frames);

            if(strs) {
                for (int i = 0; i < frames; i++) {
                    log(LogLevel::TRACE, "  [%d] %s", i, strs[i]);

                    //Demangle the function name
                    char *mangled_name = strchr(strs[i], '(');
                    if (mangled_name) {
                        char *end = strchr(mangled_name, '+');
                        if (end) {
                            *end = '\0';
                            int status;
                            char *real_name = abi::__cxa_demangle(mangled_name + 1, 0, 0, &status);
                            if (status == 0) {
                                log(LogLevel::TRACE, "    %s", real_name);
                            } else {
                                log(LogLevel::TRACE, "    %s", mangled_name + 1);
                            }
                            free(real_name);
                        }
                    }
                }
            }

            free(strs);

            log(LogLevel::TRACE, "END TRACE");
            //END: stack trace
            
            //TODO: cleanup

            exit(EXIT_FAILURE);
        }
        default:
            //TODO: handle all signals
            log(LogLevel::INFO, "Received signal %d", signal);
            break;
    }
}

int main() {
    // Set stdout to line buffered, allows printing in real time without SDL blocking
    setvbuf(stdout, NULL, _IOLBF, 0);

    log(LogLevel::INFO, "Hello, World!");
    log(LogLevel::INFO, "PDA VERSION %s", PDA_VERSION_STRING);

    // Register signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGSEGV, signal_handler);


    //Engine setup
    engine = new Engine(1024, 600, "SOAREDS window");
    engine->run();

    //Cleanup
    engine->shutdown();
    delete engine;
}
