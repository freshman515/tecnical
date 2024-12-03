#include<iostream>
#include<cstring>
#include<sys/mman.h>
#include<thread>
#include<curl/curl.h>
#include<fstream>
#include<vector>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>
using namespace std;

typedef struct ThreadParam {
    string url;
    long long range[2];
    void* ptr;
    int offset;
    int thread_id;

}ThreadParam;
size_t write_func(void* buffer, size_t size, size_t nmemb, void* userdata) {
    size_t realsize = size * nmemb;

    ThreadParam* param = static_cast<ThreadParam*>(userdata);

    memcpy((char*)param->ptr + param->offset, buffer, realsize);
    param->offset += realsize;
    return realsize;
}
long long get_download_length(const string url) {
    long long length = -1;
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1); //不下载文件，只获取文件大小 1表示生效
    if (CURLE_OK != curl_easy_perform(curl)) {
        cout << "curl_easy_perform error!" << endl;
        return -1;
    }  //执行请求
    //获取成功
    double res;
    curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &res);
    length = (long long)res;
    //请理内存
    curl_easy_cleanup(curl);
    return length;

}
void* thread_func(void* arg) {

    ThreadParam* param = static_cast<ThreadParam*>(arg);
    char range[64] = { 0 };
    sprintf(range, "%lld-%lld", param->range[0], param->range[1]);
    cout << "thread " << param->thread_id << " start download " << range << endl;

    CURL* curl = curl_easy_init(); //创建一个curl对象
    //设置信息(网络路径)
    curl_easy_setopt(curl, CURLOPT_URL, param->url.c_str());
    curl_easy_setopt(curl, CURLOPT_RANGE, range);
    //设置回调函数，perform执行结束后，会调用回调
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_func);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, param);

    //执行网络请求
    curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    cout << "thread " << param->thread_id << " success" << endl;
    return nullptr;
}
int http_download(const string& url, const string& file_name) {
    //先知道下载的文件有多大
    long long length = get_download_length(url);

    int fd = open(file_name.c_str(), O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        cerr << "open file error!" << endl;
        return -1;
    }
    if (length == -1) {
        return -1;
    }
    cout << "file length:" << length << endl;

    //先开辟内存，方便多线程下载
    // outfile.seekp(length - 1, ios::beg);
    // outfile.put('\0');
    lseek(fd, length - 1, SEEK_SET);
    write(fd, "\0", 1);

    //映射内存 共享内存
    void* fileptr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (fileptr == MAP_FAILED) {
        cout << "mmap error" << endl;
        return -1;
    }

    //创建线程
    const int thread_num = 30;
    vector<thread> threads;
    vector<ThreadParam> thread_params(thread_num);
    for (int i = 0; i < thread_num; i++) {
        thread_params[i].url = url;

        thread_params[i].range[0] = length / thread_num * i;

        if (i == thread_num - 1)
            thread_params[i].range[1] = length - 1;
        else
            thread_params[i].range[1] = (length / thread_num) * (i + 1) - 1;

        thread_params[i].ptr = fileptr + thread_params[i].range[0];

        thread_params[i].offset = 0;
        thread_params[i].thread_id = i;

        threads.emplace_back(thread_func, &thread_params[i]);

    }

    for (auto& t : threads) {
        if (t.joinable())
            t.join();
    }
    munmap(fileptr, length);
    close(fd);

    return 0;
}
int main() {
    string url = "https://alicoccdncmnet-xn.inter.71edge.com/cdn/pca/20241111/12.10.5.8786/channel/1731310048508/IQIYIsetup_z42.exe?dis_dz=CMNET-ChongQing&dis_st=36&random=1&rand_hash=0&&ip=39.144.222.202&ssl=1&dis_dx=1";
    string filename = "1.exe";
    return http_download(url, filename);
}