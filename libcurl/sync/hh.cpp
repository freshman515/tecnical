#include<curl/curl.h>
#include<iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;

typedef struct UrlHandleData {
    CURL* eary_handle;
    CURLM* multi_handle;
    bool is_complete;
}UrlHandleData;

size_t write_callback(char* buffer, size_t size, size_t nmemb, void* userdata) {
    string* response = reinterpret_cast<string*>(userdata);
    response->append(buffer, size * nmemb);
    return size * nmemb;
}
void perform_multi_url(const vector<string>& urls) {
    CURL* easy_handle;
    CURLM* multi_handle;
    int still_runging;
    int numfds;
    map<CURL*, string*> responseMap;
    map<CURL*, string> urlMap;
    multi_handle = curl_multi_init();
    //添加
    for (const auto& url : urls) {
        easy_handle = curl_easy_init();
        if (easy_handle) {
            string* response = new string();
            curl_easy_setopt(easy_handle, CURLOPT_URL, url.c_str());
            curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, write_callback);

            curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, response);
            responseMap[easy_handle] = response;
            urlMap[easy_handle] = url;


            curl_multi_add_handle(multi_handle, easy_handle);
        }


    }
    //执行
    do {
        curl_multi_perform(multi_handle, &still_runging);
        if (still_runging) {
            struct timeval timeout;
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            curl_multi_wait(multi_handle, nullptr, 0, 1000, nullptr);
            /*url_multi_fdset(multi_handle, nullptr, nullptr, nullptr, &numfds);

            if (numfds) {
                select(numfds, nullptr, nullptr, nullptr, &timeout);
                //select语句
            }*/

        }
    } while (still_runging);
    //清理
    CURLMsg* message;
    int messageLfet;

    while (message = curl_multi_info_read(multi_handle, &messageLfet)) {
        if (message->msg == CURLMSG_DONE) {
            CURL* easy_handle = message->easy_handle;
            CURLcode result = message->data.result;


            if (result == CURLE_OK) {
                cout << "Request to URL: " << urlMap[easy_handle] << "completed successfully" << endl;
                cout << "Response: " << endl;
                cout << *(responseMap[easy_handle]) << endl;
            } else {
                cerr << "Request URL: " << urlMap[easy_handle] << " failed result: " << curl_easy_strerror(result) << endl;
            }


            delete responseMap[easy_handle];
            curl_multi_remove_handle(multi_handle, easy_handle);
            curl_easy_cleanup(easy_handle);
        }

    }
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
}
