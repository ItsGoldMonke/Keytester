#include <stdio.h>
#include <curl/curl.h>

void make_request(const char *url, const char *headers)
{
    CURL *curl = curl_easy_init();

    if (curl == NULL) {
        printf("Failed to init CURL\n");
        return;
    }

    struct curl_slist *chunk = NULL;

    if (headers != NULL && headers[0] != '\0') {
        chunk = curl_slist_append(chunk, headers);

        if (chunk == NULL) {
            printf("Failed to allocate header list\n");
            curl_easy_cleanup(curl);
            return;
        }
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    }
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Keytester/1.0.0");

    CURLcode result = curl_easy_perform(curl);
    
    if (result != CURLE_OK) {
        printf("Request was not OK, something went wrong %s \n", curl_easy_strerror(result));
    }

    long response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    
    printf("\nStatus code: %ld\n", response_code);
    
    curl_slist_free_all(chunk);
    curl_easy_cleanup(curl);
}