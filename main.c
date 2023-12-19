#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main() {
    
    CURL *hnd = curl_easy_init();

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, "https://weatherapi-com.p.rapidapi.com/current.json?q=53.1%2C-0.13");

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "X-RapidAPI-Key: 353dd9c21bmsh27913df22698674p1c9bcdjsnc96f27643b02");
    headers = curl_slist_append(headers, "X-RapidAPI-Host: weatherapi-com.p.rapidapi.com");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    CURLcode ret = curl_easy_perform(hnd);
// Clean up and close the file
    fclose(json_file);
    curl_easy_cleanup(hnd);
    curl_slist_free_all(headers);

return 0;
}
