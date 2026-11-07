#ifndef REQUESTS_H
#define REQUESTS_H


#include <stdio.h>
#include <curl/curl.h>

void make_request(const char *url, const char *headers);
#endif