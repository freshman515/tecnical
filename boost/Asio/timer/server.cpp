#include<iostream>
#include<boost/asio.hpp>

void repeat(boost::asio::steady_timer& timer, boost::asio::ip::tcp::socket& socket) {
    //执行任务
    std::cout << "开始执行任务" << std::endl;
    const std::string heartbeat_message = "HEARTBEAD";
    boost::asio::async_write(socket, boost::asio::buffer(heartbeat_message), [&](const boost::system::error_code& ec, size_t) {
        if (!ec) {
            std::cout << "send heartbeat message" << std::endl;
        } else {
            std::cout << "Failed to send a heartbeat message" << std::endl;
            timer.cancel();
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
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 12345);
    boost::asio::ip::tcp::acceptor acceptor(io, endpoint);
    acceptor.async_accept([&](const boost::system::error_code& ec, boost::asio::ip::tcp::socket socket) {
        if (!ec) {
            std::cout << "客户端已连接" << std::endl;
            repeat(timer, socket);
            // 处理客户端请求
        } else {
            std::cerr << "连接失败: " << ec.message() << std::endl;
        }
        });


    io.run();
    return 0;
}