#include<iostream>
#include<thread>
#include"server.h"
#include"session.h"
int main() {
    try {
        boost::asio::io_context io_context;
        server s(io_context, 8888);
        std::thread t(
            [&io_context]() {
                io_context.run();
            }
        );

        t.join();
    } catch (std::exception& e) {
        std::cerr << "Exception : " << e.what() << std::endl;
    }
}