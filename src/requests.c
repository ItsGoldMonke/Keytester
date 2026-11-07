#include <stdio.h>
#include <curl/curl.h>

void make_request(const char *url, const char *headers)
{
    printf("Curl function:\n");
    CURL *curl = curl_easy_init();


    if (curl == NULL) {
        printf("Failed to init CURL\n");
    }

    struct curl_slist *chunk = NULL;

    chunk = curl_slist_append(chunk, headers);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_URL, url);

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        printf("Request was not OK, something went wrong %s \n", curl_easy_strerror(result));
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(chunk);
}