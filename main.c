#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

size_t write_callback(void* contents, size_t size, size_t nmemb, FILE* file) {
    size_t written = fwrite(contents, size, nmemb, file);
    return written;
}

int main() {
    
    CURL *hnd = curl_easy_init();

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, "https://weatherapi-com.p.rapidapi.com/current.json?q=53.1%2C-0.13");








    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "X-RapidAPI-Key: 353dd9c21bmsh27913df22698674p1c9bcdjsnc96f27643b02");
    headers = curl_slist_append(headers, "X-RapidAPI-Host: weatherapi-com.p.rapidapi.com");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
    // Set the write callback function
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);
    // File pointer passed to the callback function
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, json_file);






    

    CURLcode ret = curl_easy_perform(hnd);
    if (ret != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
            curl_easy_cleanup(hnd);
            fclose(json_file);
            return 1;  // Exit with an error code
    }
// Clean up and close the file
    fclose(json_file);
    curl_easy_cleanup(hnd);
    curl_slist_free_all(headers);

return 0;
}
