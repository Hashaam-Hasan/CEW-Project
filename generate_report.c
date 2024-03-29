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
    fprintf(outputFile, "**********************************************\n");
    fprintf(outputFile, "FINAL ENVIRONMENTAL REPORT\n");
    fprintf(outputFile, "**********************************************\n\n");
    fprintf(outputFile, "Date and Time: %s\n\n", timeStr);

    // Include basic environmental data in the report
    fprintf(outputFile, "TEMPERATURE: %s\n", temperature);
    fprintf(outputFile, "HUMIDITY: %s\n", humidity);
    fprintf(outputFile, "PRECIPITATION: %s\n\n", precipitation);
    fprintf(outputFile, "PRESSURE: %s\n\n", pressure);
    fprintf(outputFile, "WINDSPEED: %s\n\n", windSpeed );
    fprintf(outputFile, "DIRECTION OF WIND: %s\n\n", windDirection);
    //fprintf(outputFile, "severe weather: %s\n\n", severeWeather);

    // Include anomalies detected, if any
    double temp = atof(temperature);
    double precip = atof(precipitation);
    if (temp > 30.0 || precip > 10.0) {
        fprintf(outputFile, "Anomalies Detected:\n");
        fprintf(outputFile, "***********************\n");
        fprintf(outputFile, "Temperature Anomaly: %s\n", (temp > 30.0) ? "High" : "Normal");
        fprintf(outputFile, "Precipitation Anomaly: %s\n", (precip > 10.0) ? "High" : "Normal");

        fprintf(outputFile, "***********************\n");
    }

   // fclose(outputFile); // Close the report file


}
