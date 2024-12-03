#include<iostream>
#include<boost/asio.hpp>

int main() {
    boost::asio::io_context io;
    boost::asio::steady_timer timer(io, boost::asio::chrono::seconds(5));
    timer.async_wait([](const boost::system::error_code& ec) {
        if (!ec) {
            std::cout << "time is exit" << std::endl;
        } else {
            std::cout << "timer async wait happen error" << std::endl;
        }
        });

    io.run();
    return 0;
}