//#include "send email.h"
//#include <stdio.h>
//#include <curl/curl.h>
//
//size_t read_callback(void *ptr, size_t size, size_t nmemb, FILE *stream) {
//    size_t retcode = fread(ptr, size, nmemb, stream);
//    return retcode;
//}
//
//int send_email_with_attachment(const char *to, const char *cc, const char *file_path) {
//    CURL *curl;
//    CURLcode res = CURLE_OK;
//
//    FILE *file = fopen("environmental_report.txt", "rb");
//    if (!file) {
//        fprintf(stderr, "Error opening file: %s\n", file_path);
//        return 1;
//    }
//
//    curl_global_init(CURL_GLOBAL_DEFAULT);
//    curl = curl_easy_init();
//
//    if(curl) {
//        struct curl_slist *recipients = NULL;
//
//        // Specify email server details
//        // For Gmail
//        curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com");
//        curl_easy_setopt(curl, CURLOPT_USERPWD, "businesswithusamafr@gmail.com:businesswithusama123");
//        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
//
//        // Add email recipients
//        if (to)
//            recipients = curl_slist_append(recipients, to);
//        if (cc)
//            recipients = curl_slist_append(recipients, cc);
//        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
//
//        // Set the read callback function to read the file content
//        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
//        curl_easy_setopt(curl, CURLOPT_READDATA, file);
//        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
//
//        // Perform the email sending
//        res = curl_easy_perform(curl);
//        if(res != CURLE_OK)
//            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
//
//        // Clean up
//        curl_slist_free_all(recipients);
//        curl_easy_cleanup(curl);
//    }
//
//    // Close the file
//    fclose(file);
//
//    curl_global_cleanup();
//    return (int)res;
//}
// sendgrid_request.c
#include "send_email.h"
//#include <curl/curl.h>
//CURLcode sendgrid_patch_request(const char* alert_id) {
//    CURL *hnd = curl_easy_init();
//    if (!hnd) {
//        return CURLE_FAILED_INIT;
//    }
//    CURL *hnd = curl_easy_init();
//
//    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "PATCH");
//    curl_easy_setopt(hnd, CURLOPT_URL, "https://rapidprod-sendgrid-v1.p.rapidapi.com/alerts/1");
//
//    struct curl_slist *headers = NULL;
//    headers = curl_slist_append(headers, "content-type: application/json");
//    headers = curl_slist_append(headers, "X-RapidAPI-Key: 59ebf45566msh90bbd47d19191e1p129e89jsn5411c2e62214");
//    headers = curl_slist_append(headers, "X-RapidAPI-Host: rapidprod-sendgrid-v1.p.rapidapi.com");
//    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
//
//    curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"type\":\"stats_notification\",\"email_to\":\"example@test.com\",\"frequency\":\"daily\"}");
//
//    CURLcode ret = curl_easy_perform(hnd);
//        // Set your CURLOPT options here...
//
//        CURLcode ret = curl_easy_perform(hnd);
//
//        curl_easy_cleanup(hnd);
//        return ret;
//    }
// sendgrid_request.c
//#include "sendgrid_request.h"
#include <curl/curl.h>

CURLcode sendgrid_patch_request(const char* alert_id) {
    CURL *hnd = curl_easy_init();
    if (!hnd) {
        return CURLE_FAILED_INIT;
    }

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(hnd, CURLOPT_URL, "https://rapidprod-sendgrid-v1.p.rapidapi.com/alerts/1" );

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "content-type: application/json");
    headers = curl_slist_append(headers,  "X-RapidAPI-Key: 353dd9c21bmsh27913df22698674p1c9bcdjsnc96f27643b02" );
    headers = curl_slist_append(headers,  "X-RapidAPI-Host: rapidprod-sendgrid-v1.p.rapidapi.com" );
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"type\":\"stats_notification\",\"email_to\":\"smhashaam@gmail.com\",\"frequency\":\"daily\"}");

    CURLcode ret = curl_easy_perform(hnd);

    // Clean up
    curl_slist_free_all(headers);
    curl_easy_cleanup(hnd);

    return ret;
}
