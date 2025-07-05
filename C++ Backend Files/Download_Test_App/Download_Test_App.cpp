#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <curl/curl.h>
#include <thread>

// Global variables for timing
std::chrono::steady_clock::time_point g_download_start_time;
bool g_download_started = false;
const int MAX_DOWNLOAD_SECONDS = 20;  // Max time to allow download (seconds)


// Callback function to handle downloaded data
size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::string* buffer = static_cast<std::string*>(userp);
    size_t total_size = size * nmemb;
    buffer->append(static_cast<char*>(contents), total_size);
    return total_size;
}


// Progress callback to monitor download speed and abort after a set time
int progress_callback(void* clientp, curl_off_t dltotal, curl_off_t dlnow,
    curl_off_t ultotal, curl_off_t ulnow) {

    if (!g_download_started) {
        g_download_start_time = std::chrono::steady_clock::now();  // Start timer
        g_download_started = true;
    }

    auto now = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double>(now - g_download_start_time).count();

    // Calculate download speed in megabits per second (Mb/s)
    double speed_mbps = (dlnow * 8.0) / (elapsed * 1'000'000.0);

    // optional detailed output
    // std::cout << "\rDownloading: " << dlnow / (1024 * 1024) << " MB | Time: " << elapsed << " sec | "
    //           << "Live speed: " << (dlnow / (1024 * 1024)) / elapsed << " MB/s " << speed_mbps << " Mb/s" << std::flush;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\r " << speed_mbps << " Mb/s" << std::flush;

    // Abort the download after MAX_DOWNLOAD_SECONDS
    if (elapsed >= MAX_DOWNLOAD_SECONDS) {
        // std::cout << "\nTime limit reached. Aborting download...\n";
        return 1;  // Abort
    }

    return 0;  // Continue
}


int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();

    if (!curl) {
        std::cerr << "Failed to initialize curl\n";
        return 1;
    }

    // Target download URL (Cloudflare speed test file)
    const char* url = "https://speed.cloudflare.com/__down?bytes=10240000000";

    std::string dummy_buffer;  // Buffer to receive data (not used)

    // Set CURL options
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &dummy_buffer);

    // Enable progress tracking
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);

    // Start the download
    CURLcode res = curl_easy_perform(curl);

    // Stop the timer
    auto end_time = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration<double>(end_time - g_download_start_time).count();

    if (res == CURLE_OK || res == CURLE_ABORTED_BY_CALLBACK) {
        curl_off_t total_bytes = 0;
        curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T, &total_bytes);

        // Calculate final download speed
        double speed_mbps = (static_cast<double>(total_bytes) * 8.0) / (elapsed_seconds * 1'000'000.0);

        // Optional detailed output
        /*
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Elapsed Time: " << elapsed_seconds << " seconds\n";
        std::cout << "Data Downloaded: " << total_bytes / (1024.0 * 1024.0) << " MB "
                  << total_bytes * 8 << " Mb\n";
        std::cout << "Estimated Download Speed: " << speed_mbps << " Mb/s "
                  << total_bytes / (1024 * 1024) / elapsed_seconds << " MB/s\n";
        */

        // std::cout << "Download Speed: " << speed_mbps << " Mb/s";
    }
    else {
        std::cerr << "CURL Error: " << curl_easy_strerror(res) << "\n";
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return 0;
}
