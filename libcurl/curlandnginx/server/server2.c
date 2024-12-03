#include <fcgi_stdio.h>
#include <fcgi_config.h>
#include<stdlib.h>
#include <unistd.h>
int main() {


    int count = 0;

    while (FCGI_Accept() >= 0) {
        char* contentLength = getenv("CONTENT_LENGTH");
        int len;

        printf("Content-type: text/html\r\n"
            "\r\n"
            "<title>FastCGI echo</title>"
            "<h1>FastCGI echo</h1>\n"
            "Request number %d,  Process ID: %d<p>\n", ++count, getpid());

            // std::cout << "Content-type: text/html\r\n\r\n";

            // // 输出响应内容
            // std::cout << "<html><body>";
            // std::cout<<"<title>FastCGI Server Response</title>"
            // std::cout << "<h1>FastCGI Server Response</h1>";
            // std::cout << "<p>Request received successfully.</p>";
            // std::cout << "</body></html>" << std::endl;
    }
    return 0;
}
