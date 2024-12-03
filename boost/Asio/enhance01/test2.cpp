#include <iostream>
#include <boost/asio.hpp>
#include <thread>

void print(boost::asio::io_context& io, boost::asio::strand<boost::asio::io_context::executor_type>& strand, const std::string& msg) {
    std::cout << "Submitting task: " << msg << std::endl;
    boost::asio::post(strand, [msg]() {
        std::cout << "Task started: " << msg << std::endl;
        std::cout << msg << std::endl;
        });
}

int main() {
    boost::asio::io_context io_context;
    boost::asio::strand<boost::asio::io_context::executor_type> strand(io_context.get_executor());

    print(io_context, strand, "hello");
    print(io_context, strand, "world");
    print(io_context, strand, "hello1");
    print(io_context, strand, "world1");

    // 启动一个线程来运行 io_context
    std::thread t([&io_context]() { io_context.run(); });
    t.join();  // 确保主线程等到 io_context 完成所有工作

    return 0;
}