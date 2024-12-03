#include <iostream>
#include<fcgi_config.h>
#include<fcgiapp.h>
#include<fcgi_stdio.h>
using namespace std;
// 同步 C 和 C++ 的缓冲区


int main() {

    std::ios::sync_with_stdio(true);
    while (FCGI_Accept() >= 0) { // FastCGI 主循环
        // 使用 <fcgi_stdio.h> 的 C 风格输出
        printf("Content-type: text/html\r\n\r\n");
        printf("<h1>Hello from FastCGI with <fcgi_stdio.h></h1>\n");

                // 使用 <iostream> 的 C++ 风格输出
        printf("<p>Hello from FastCGI with <iostream></p>\n");
        fflush(stdout);
        printf("<p>End of output</p>\n");
        // 这样混用时，输出不会乱序
    }
    return 0;
    /*
    std::cout << "Content-type: text/html\r\n\r\n";
    std::cout << "<html><body><h1>Hello from FastCGI!</h1></body></html>";
     while (FCGI_Accept() >= 0) {
        char* contentLength = getenv("CONTENT_LENGTH");
        int len;

        printf("Content-type: text/html\r\n"
            "\r\n"
            "<title>FastCGI echo</title>"
            "<h1>FastCGI echo</h1>\n"
            "Request number %d,  Process ID: %d<p>\n", ++count, getpid());

    }
    return 0;*/
}