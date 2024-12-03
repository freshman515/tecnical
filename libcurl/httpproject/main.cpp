#include"HttpClient.h"

int main() {
    HttpClient client;
    nlohmann::json singleResponse = client.get("https://jsonplaceholder.typicode.com/posts/1");
    std::cout << "Single get response :\n" << singleResponse.dump(4) << std::endl;

    // 测试 POST 请求
    nlohmann::json postResponse = client.post(
        "https://jsonplaceholder.typicode.com/posts",
        R"({"title":"foo","body":"bar","userId":1})"
    );
    std::cout << "POST Response:\n" << postResponse.dump(4) << std::endl;

      // 多个异步请求并保存到文件
    std::vector<std::string> urls = {
        "https://jsonplaceholder.typicode.com/posts/1",
        "https://jsonplaceholder.typicode.com/posts/2",
        "https://jsonplaceholder.typicode.com/posts/3"
    };
    //client.perform_sync_requests(urls, "output.json");
    if (!client.download_file("https://example.com/file.zip", "file.zip")) {
        std::cerr << "Failed to dowmload file" << std::endl;
    }
    if (!client.upload_file("http://example.com/upload", "file.zip")) {
        std::cerr << "Failed to upload file." << std::endl;
    }
    return 0;
}