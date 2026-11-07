#include <stdio.h>
#include <curl/curl.h>

int main(void)
{
    printf("Curl function:\n");
    CURL *curl = curl_easy_init();

    if (curl == NULL) {
        printf("Failed to init CURL\n");
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/get");

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        printf("Request was not OK, something went wrong %s \n", curl_easy_strerror(result));
    }

    curl_easy_cleanup(curl);
    return 0;

}