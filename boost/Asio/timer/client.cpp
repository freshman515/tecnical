#include<iostream>
#include<boost/asio.hpp>

void repeat(boost::asio::steady_timer& timer, boost::asio::ip::tcp::socket& socket) {
    //执行任务
    std::cout << "开始执行任务" << std::endl;
    const std::string heartbeat_message = "HEARTBEAD";
    boost::asio::async_write(socket, boost::asio::buffer(heartbeat_message), [](const boost::system::error_code& ec, size_t) {
        if (!ec) {
            std::cout << "send heartbeat message" << std::endl;
        }
        });
        //end
    timer.expires_at(timer.expiry() + boost::asio::chrono::seconds(3));
    timer.async_wait([&](const boost::system::error_code& ec) {
        if (!ec) {
            repeat(timer, socket);
        }
        });

}
int main() {
    boost::asio::io_context io;
    boost::asio::steady_timer timer(io, boost::asio::chrono::seconds(5));

    boost::asio::ip::tcp::socket socket(io);
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 12345);
    socket.async_connect(endpoint, [&](const boost::system::error_code& ec) {
        if (!ec) {
            repeat(timer, socket);
            std::cout << "connect successfully" << std::endl;
        } else {
            std::cout << "connect fail" << std::endl;
        }
        });


    io.run();
    return 0;
}