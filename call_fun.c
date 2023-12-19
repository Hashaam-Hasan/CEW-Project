#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

// A simple call function for handling API response
size_t write_callback(void *contents, size_t size, size_t nmemb, char *buffer) {
    size_t total_size = size * nmemb;
    strcat(buffer, (char *)contents);
    return total_size;
}

int main() {
    CURL *curl;
    CURLcode res;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        char ipinfo_url[] = "https://ipinfo.io/json";
        char response[2048] = {0};  // Response buffer

        // Set the API URL
        curl_easy_setopt(curl, CURLOPT_URL, ipinfo_url);

        // Set the callback function to handle the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Print the response (JSON format)
            printf("API Response:\n%s\n", response);
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    // Cleanup libcurl
    curl_global_cleanup();

    return 0;
}
