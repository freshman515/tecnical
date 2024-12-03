
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

size_t write_callback(char* buffer, size_t size, size_t nmemb, void* userdata) {
    string* response = reinterpret_cast<string*>(userdata);
    response->append(buffer, size * nmemb);
    return size * nmemb;
}

void perform_multi_url(const vector<string>& urls) {
    CURL* easy_handle;
    CURLM* multi_handle;
    int still_running;
    int numfds;
    map<CURL*, string*> responseMap; // 使用指针存储动态分配的响应
    map<CURL*, string> urlMap;       // 存储 URL
    multi_handle = curl_multi_init();

    // 添加请求
    for (const auto& url : urls) {
        easy_handle = curl_easy_init();
        if (easy_handle) {
            string* response = new string();
            curl_easy_setopt(easy_handle, CURLOPT_URL, url.c_str());
            curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, response);

            responseMap[easy_handle] = response; // 保存响应指针
            urlMap[easy_handle] = url;          // 保存 URL
            curl_multi_add_handle(multi_handle, easy_handle);
        }
    }

    // 执行请求
    do {
        curl_multi_perform(multi_handle, &still_running);
        if (still_running) {
            curl_multi_wait(multi_handle, nullptr, 0, 1000, nullptr);
        }
    } while (still_running);

    // 处理结果
    CURLMsg* message;
    int messagesLeft;

    while ((message = curl_multi_info_read(multi_handle, &messagesLeft))) {
        if (message->msg == CURLMSG_DONE) {
            CURL* easy_handle = message->easy_handle;
            CURLcode result = message->data.result;

            if (result == CURLE_OK) {
                cout << "Request to URL: " << urlMap[easy_handle] << " completed successfully" << endl;
                cout << "Response: " << endl;
                cout << *(responseMap[easy_handle]) << endl;
            } else {
                cerr << "Request to URL: " << urlMap[easy_handle] << " failed: "
                    << curl_easy_strerror(result) << endl;
            }

            // 清理每个请求
            delete responseMap[easy_handle];          // 释放动态分配的响应字符串
            curl_multi_remove_handle(multi_handle, easy_handle);
            curl_easy_cleanup(easy_handle);
        }
    }

    // 清理 multi 句柄
    curl_multi_cleanup(multi_handle);
}

int main() {
    vector<string> urls = {
        "http://example.com",
        "https://www.google.com",
        "https://jsonplaceholder.typicode.com/posts/1"
    };
    curl_global_init(CURL_GLOBAL_DEFAULT);
    perform_multi_url(urls);
    curl_global_cleanup();
    return 0;
}
