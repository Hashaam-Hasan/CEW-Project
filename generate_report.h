// generate_report.h

#ifndef GENERATE_REPORT_H
#define GENERATE_REPORT_H
#include <curl/curl.h>
#include <stdio.h>
void generateReport(const char* timeStr, const char* temperature, const char* humidity,
                    const char* precipitation, const char* pressure, const char* windSpeed,
                     const char* windDirection, FILE* outputFile);

CURLcode sendgrid_patch_request(const char* alert_id);

#endif // GENERATE_REPORT_H