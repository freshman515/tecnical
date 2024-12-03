#include<iostream>
#include<boost/asio.hpp>
#include<vector>
#include<thread>
void worker(boost::asio::io_context& io) {
    io.run();
}
int main() {
    boost::asio::io_context io_context;
    std::vector<std::thread> threads;
    for (int i = 0;i < 4;i++) {
        threads.emplace_back(worker, std::ref(io_context));
    }
    for (auto& thread : threads) {
        thread.join();
    }
    return 0;
}