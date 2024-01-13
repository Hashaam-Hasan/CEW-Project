// report_generator.c
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "send_email.h"


#include "generate_report.h"

void generateReport(const char* timeStr, const char* temperature, const char* humidity,
                    const char* precipitation,const char* pressure,const char* windSpeed
                    ,const char* windDirection, FILE* outputFile) {
    // Check for errors in opening the output file
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening report file.\n");
        return; // Exit the function if an error occurs
    }

    // Add headers and timestamp to the report
    fprintf(outputFile, "-----------------------\n");
    fprintf(outputFile, "Environmental Report\n");
    fprintf(outputFile, "-----------------------\n\n");
    fprintf(outputFile, "Timestamp: %s\n\n", timeStr);

    // Include basic environmental data in the report
    fprintf(outputFile, "Temperature: %s\n", temperature);
    fprintf(outputFile, "Humidity: %s\n", humidity);
    //fprintf(outputFile, "severe weather: %s\n\n", severeWeather);

    // Include anomalies detected, if any
    double temp = atof(temperature);
    double precip = atof(precipitation);
    if (temp > 30.0 || precip > 10.0) {
        fprintf(outputFile, "Anomalies Detected:\n");

   // fclose(outputFile); // Close the report file


}