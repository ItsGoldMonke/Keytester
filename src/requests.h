#ifndef REQUESTS_H
#define REQUESTS_H

#include <stdbool.h>
#include <stdio.h>
#include <curl/curl.h>


void make_request(const char *url, const char *headers, bool isRaw);
#endif