
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <time.h>





int findFieldValue(const char *text, const char *field, char *value, size_t valueSize) {
    const char *start = strstr(text, field);

    if (start == NULL) {
        fprintf(stderr, "Field %s not found in text.\n", field);
        return 0;
    }

    // Move the pointer to the value part
    start = strchr(start, ':');
    if (start == NULL) {
        fprintf(stderr, "Invalid text format.\n");
        return 0;
    }

    // Skip any whitespace
    while (*start != '\0' && (*start == ':' || *start == ' ' || *start == '\t' || *start == '\n' || *start == '\r')) {
        start++;
    }

    // Check for the start of a string or number
    if (*start == '"' || (*start >= '0' && *start <= '9') || *start == '-') {
        sscanf(start, "%[^,}]", value);
        return 1;
    } else {
        fprintf(stderr, "Invalid text value format.\n");
        return 0;
    }
}

void detectAnomalies(const char *temperature, const char *precipitation, FILE *outputFile) {
    double temp = atof(temperature);
    double precip = atof(precipitation);

    if (temp > 30.0) {
        printf("High temperature anomaly detected!\n");
    }

    if (precip > 10.0) {
        printf("High precipitation anomaly detected!\n");
    }
}






void processData(const char *fileContent, FILE*outputFile) {
    //FILE *outputFile;
    char city[10];
    char temperature[10];
    char humidity[10];
    char precipitation[10];
    char windSpeed[10];
    char windDirection[10];
    char severeWeather[10];

    findFieldValue(fileContent, "\"name\"", city, sizeof(city));
    findFieldValue(fileContent, "\"temp_c\"", temperature, sizeof(temperature));
    findFieldValue(fileContent, "\"humidity\"", humidity, sizeof(humidity));
    findFieldValue(fileContent, "\"precip_mm\"", precipitation, sizeof(precipitation));
    findFieldValue(fileContent, "\"wind_kph\"", windSpeed, sizeof(windSpeed));
    findFieldValue(fileContent, "\"wind_dir\"", windDirection, sizeof(windDirection));

    char condition[50];
    findFieldValue(fileContent, "\"text\"", condition, sizeof(condition));
    int isSevereWeather = (strcmp(condition, "Thunderstorm") == 0 || strcmp(condition, "Rain") == 0);

    // Get the current time
    time_t currentTime = time(NULL);
    struct tm *timeInfo = localtime(&currentTime);
    char timeStr[20];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeInfo);

    // Append the processed data with the current time to the output file
//    fprintf(outputFile, "Processed data at %s\n", timeStr);
//    printf("Temperature: %s\n", temperature);
//    printf("Humidity: %s\n", humidity);
//    printf("Precipitation: %s\n", precipitation);
//    printf("Pressure: %s\n", pressure);
//    printf("Wind Speed: %s\n", windSpeed);
//    printf("Wind Direction: %s\n", windDirection);
//    printf("Severe Weather: %s\n", isSevereWeather ? "Yes" : "No");

    outputFile = fopen("processed_data.txt", "a");
    if (outputFile) {
        fprintf(outputFile, "City: %s\n", city);
        fprintf(outputFile, "Temperature: %s\n", temperature);
        fprintf(outputFile, "Humidity: %s\n", humidity);
        fprintf(outputFile, "Precipitation: %s\n", precipitation);
        fprintf(outputFile, "Wind Speed: %s\n", windSpeed);
        fprintf(outputFile, "Wind Direction: %s\n", windDirection);
        fprintf(outputFile, "Severe Weather: %s\n", isSevereWeather ? "Yes" : "No");
        fprintf(outputFile, "\n");
        //fclose(outputFile);


    detectAnomalies(temperature, precipitation,outputFile);
    fclose(outputFile);
}
}
