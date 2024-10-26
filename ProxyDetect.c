#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct Memory {
    char *response;
    size_t size;
};

size_t write_callback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    struct Memory *mem = (struct Memory *)userp;

    char *ptr = realloc(mem->response, mem->size + total_size + 1);
    if(ptr == NULL) return 0;

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, total_size);
    mem->size += total_size;
    mem->response[mem->size] = 0;

    return total_size;
}

void check_proxy(const char *ip) {
    CURL *curl;
    CURLcode res;

    struct Memory chunk = {NULL, 0}; 
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "https://blackbox.ipinfo.app/lookup/%s", ip);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            if (strcmp(chunk.response, "Y") == 0) {
                printf("IP %s adalah proxy.\n", ip);
            } else {
                printf("IP %s bukan proxy.\n", ip);
            }
        }

        curl_easy_cleanup(curl);
    }

    if (chunk.response) {
        free(chunk.response);
    }

    curl_global_cleanup();
}

int main() {
    char ip[100];
    printf("Masukkan IP yang ingin diperiksa: ");
    scanf("%99s", ip);
    check_proxy(ip);
    return 0;
}
