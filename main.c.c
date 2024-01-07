
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


