#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <time.h>
#include <math.h>
#include <weather_utils.h>
#include "generate_report.h"
#include "send_email.h"

int main(void) {
    char temperature[10];
    char humidity[10];
    char precipitation[10];
    char pressure[10];
    char windSpeed[10];
    char windDirection[10];
    //char severeWeather[10];
    FILE *outputFile = fopen("output_log.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        return 1;
    }

    FILE *processedDataFile = fopen("processed_data.txt", "a");
    if (processedDataFile == NULL) {
        fprintf(stderr, "Error opening processed_data file.\n");
        fclose(outputFile);
        return 1;
      }

    CURL *hnd = curl_easy_init();
    if (hnd) {
        curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(hnd, CURLOPT_URL, "https://weatherapi-com.p.rapidapi.com/current.json?q=24.8607%2C67.0011");

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "X-RapidAPI-Key: 353dd9c21bmsh27913df22698674p1c9bcdjsnc96f27643b02");
        headers = curl_slist_append(headers, "X-RapidAPI-Host: weatherapi-com.p.rapidapi.com");
        curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, fwrite);
        curl_easy_setopt(hnd, CURLOPT_WRITEDATA, outputFile);

        CURLcode ret = curl_easy_perform(hnd);

        if (ret != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(hnd);

        fclose(outputFile);
    }

    FILE *inputFile = fopen("output_log.txt", "r");
    if (!inputFile) {
        fprintf(stderr, "Failed to open input file.\n");
        return 1;
    }
     FILE *apiResponseFile = fopen("api_response.txt", "a");
    if (apiResponseFile == NULL) {
        fprintf(stderr, "Error opening api_response.txt file.\n");
        fclose(inputFile);
        fclose(processedDataFile);
        return 1;
    }

    // Copy and append content from output_log.txt to api_response.txt
    int ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        fputc(ch, apiResponseFile);
    }



    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char *fileContent = (char *)malloc(fileSize + 1);
    size_t bytesRead =fread(fileContent, 1, fileSize, inputFile);
    fileContent[bytesRead] = '\0';
    fclose(inputFile);
    fclose(apiResponseFile);
    fclose(processedDataFile);
    fileContent[fileSize] = '\0';

    processData(fileContent,outputFile,temperature, humidity, precipitation,
                pressure, windSpeed, windDirection);

        // Declare variables for generateReport function
    char reportTemperature[10];
    char reportHumidity[10];
    char reportPrecipitation[10];
    char reportpressure[10];
    char reportwindSpeed[10];
    char reportwindDirection[10];
   // char reportsevereWeather[10];

    // Copy values from the original variables
    strcpy(reportTemperature, temperature);
    strcpy(reportHumidity, humidity);
    strcpy(reportPrecipitation, precipitation);
    strcpy(reportpressure, pressure);
    strcpy(reportwindDirection, windDirection);
    strcpy(reportwindSpeed, windSpeed);
    //strcpy(reportsevereWeather, severeWeather);
 //   strcpy(reportsevereWeather, severeWeather);

    // Free the allocated memory for fileContent
    free(fileContent);

        // Get the current time
    time_t currentTime = time(NULL);
    struct tm *timeInfo = localtime(&currentTime);
    char timeStr[20];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeInfo);

    // Open the report file for writing
    FILE *reportFile = fopen("environmental_report.txt", "w");
    if (reportFile == NULL) {
        fprintf(stderr, "Error opening report file.\n");
        fclose(outputFile);
        return 1;
    }
    generateReport(timeStr, reportTemperature, reportHumidity, reportPrecipitation, reportpressure, reportwindSpeed, reportwindDirection, reportFile);

    // Close the report file
    fclose(reportFile);

    return 0;

}
