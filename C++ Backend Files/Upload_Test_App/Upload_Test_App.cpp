#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <curl/curl.h>

// Global variables to track upload start time
std::chrono::steady_clock::time_point g_upload_start_time;
bool g_upload_started = false;
const int MAX_UPLOAD_SECONDS = 20;  // Max time to allow upload (seconds)


// Discards response body (we don’t care about the server response)
size_t discard_response(char* ptr, size_t size, size_t nmemb, void* userdata) {
    return size * nmemb;  // Tell libcurl we "handled" all received data
}


// Progress callback (called during upload)
int upload_progress_callback(void* clientp, curl_off_t dltotal, curl_off_t dlnow,
    curl_off_t ultotal, curl_off_t ulnow) {

    if (!g_upload_started) {
        g_upload_start_time = std::chrono::steady_clock::now();  // Start timer
        g_upload_started = true;
    }

    auto now = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double>(now - g_upload_start_time).count();

    // Calculate upload speed in megabits per second
    double speed_mbps = (ulnow * 8.0) / (elapsed * 1'000'000.0);

    // optional detailed output
    // std::cout << "\rUploading: " << ulnow / (1024 * 1024) << " MB | Time: " << elapsed << " sec | "
    //           << "Live speed: " << (ulnow / (1024 * 1024)) / elapsed << " MB/s " << speed_mbps << " Mb/s" << std::flush;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\r " << speed_mbps << " Mb/s" << std::flush;

    // Abort the upload after MAX_UPLOAD_SECONDS
    if (elapsed >= MAX_UPLOAD_SECONDS) {
        // std::cout << "\nTime limit reached. Aborting upload...\n";
        return 1;  // Abort
    }

    return 0;  // Continue
}


int main() {
    const size_t upload_size_bytes = 1000 * 1024 * 1024;  // 1000 MB = ~1 GB
    std::string upload_data(upload_size_bytes, 'x');       // Filler data to upload

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize curl.\n";
        return 1;
    }

    // Set the upload target URL
    const char* url = "https://upload-server-production-6c12.up.railway.app/";

    // Configure libcurl for HTTP POST upload
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, upload_data.data());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, upload_size_bytes);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discard_response);

    // Enable progress tracking
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, upload_progress_callback);

    // Perform the upload
    CURLcode res = curl_easy_perform(curl);

    // Stop the timer
    auto end_time = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration<double>(end_time - g_upload_start_time).count();

    if (res == CURLE_OK || res == CURLE_ABORTED_BY_CALLBACK) {
        curl_off_t uploaded_bytes = 0;
        curl_easy_getinfo(curl, CURLINFO_SIZE_UPLOAD_T, &uploaded_bytes);

        // Calculate final upload speed
        double speed_mbps = (uploaded_bytes * 8.0) / (elapsed_seconds * 1'000'000.0);

        // Optional detailed output
        /*
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\nUpload completed.\n";
        std::cout << "Elapsed Time: " << elapsed_seconds << " seconds\n";
        std::cout << "Data Uploaded: " << uploaded_bytes / (1024 * 1024) << " MB\n";
        std::cout << "Estimated Upload Speed: " << speed_mbps << " Mb/s "
                  << uploaded_bytes / (1024 * 1024) / elapsed_seconds << " MB/s\n";
        */
    }
    else {
        std::cerr << "CURL Error: " << curl_easy_strerror(res) << "\n";
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return 0;
}
