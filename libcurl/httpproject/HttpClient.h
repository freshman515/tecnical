#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>
#include  <fstream>
#include <log4cpp/Category.hh>
#include <log4cpp/BasicConfigurator.hh>
#include <thread>
#include <sys/stat.h>

class HttpClient {
public:
    HttpClient();
    ~HttpClient();
    nlohmann::json get(const std::string& url);
    nlohmann::json post(const std::string& rul, const std::string& data);
    void perform_sync_requests(std::vector<std::string>& urls, const std::string& outPutFileName);
    bool download_file(const std::string& url, const std::string filename);
    bool upload_file(const std::string& url, const std::string filename);
private:
    static size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* data);
    static size_t write_data(void* contents, size_t size, size_t nmemb, FILE* file);
    static size_t progress_callback(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
    nlohmann::json parse_json(const std::string& rawData);
    void save_to_file(const std::string& fileName, nlohmann::json& jsonData);

    CURLM* multiHandle;
    log4cpp::Category& logger;

};



