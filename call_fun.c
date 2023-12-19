#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include "cJSON.h" //Header file implementation pending

// Callback function to write response to a cJSON structure
size_t write_callback(void* contents, size_t size, size_t nmemb, cJSON* json) {
    // Concatenate the received data into the cJSON structure
    cJSON* root = cJSON_ParseWithLength(contents, size * nmemb);
    if (root == NULL) {
        fprintf(stderr, "Error parsing JSON response.\n");
        return 0;
    }

    // Add parsed data to the existing cJSON structure
    cJSON_ReplaceItemInObject(json, "", root);

    return size * nmemb;
}

int main() {
    CURL* hnd = curl_easy_init();
    if (!hnd) {
        fprintf(stderr, "Error initializing libcurl.\n");
        return 1;
    }

    FILE* json_file = fopen("response.json", "w");
    if (!json_file) {
        fprintf(stderr, "Error opening the file for writing.\n");
        curl_easy_cleanup(hnd);
        return 1;
    }

    // cJSON structure to hold parsed JSON data
    cJSON* json_data = cJSON_CreateObject();

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, "https://weatherapi-com.p.rapidapi.com/current.json?q=Karachi&");
    curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0);

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "X-RapidAPI-Key: 6a53f96e8emshbd482eccd871b64p1f89eejsn5fef25e81b4a");
    headers = curl_slist_append(headers, "X-RapidAPI-Host: weatherapi-com.p.rapidapi.com");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    // Set the write callback function
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);
    // Pass the cJSON structure to the callback function
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, json_data);

    CURLcode ret = curl_easy_perform(hnd);
    if (ret != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
        curl_easy_cleanup(hnd);
        fclose(json_file);
        cJSON_Delete(json_data);
        return 1;
    }

    // Convert cJSON structure to a formatted string
    char* formatted_json = cJSON_Print(json_data);
    fprintf(json_file, "%s\n", formatted_json);

    // Clean up cJSON and close the file
    cJSON_Delete(json_data);
    free(formatted_json);
    fclose(json_file);
    curl_easy_cleanup(hnd);
    curl_slist_free_all(headers);

    return 0;
}
