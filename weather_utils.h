#ifndef WEATHER_UTILS_H
#define WEATHER_UTILS_H

int findFieldValue(const char *text, const char *field, char *value, size_t valueSize);

void detectAnomalies(const char *temperature, const char *precipitation, FILE *outputFile);

void processData(const char *fileContent, FILE *outputFile, char *temperature, char *humidity, char *precipitation,
                  char *pressure, char *windSpeed, char *windDirection);

#endif





