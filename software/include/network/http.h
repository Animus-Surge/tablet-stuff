#pragma once

/**
 * @file network/http.h
 *
 * @brief HTTP networking
 */

#include <curl/curl.h>

#include <vector>

extern CURL* curlptr;

void init();
void shutdown();
