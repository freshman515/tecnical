#include<curl/curl.h>
#include<iostream>
#include<string>
using namespace std;
size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    string* str = (string*)userdata;
    str->append(ptr, size * nmemb);
    return size * nmemb;
}
int main() {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL!" << std::endl;
        return 1;
    }
    string url = "http://192.168.5.15/test";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    //设置post方法
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    //设置post数据
    const char* postdata = "name=xmf&age=20";
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

    std::string response_data;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL request failed: " << curl_easy_strerror(res) << std::endl;
    } else {
        std::cout << "HTTP POST request succeeded." << std::endl;
        std::cout << "Response data: " << response_data << std::endl;
    }
    curl_easy_cleanup(curl);
    return 0;
}