#include <boost/asio.hpp>
#include <iostream>

int main() {
    try {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::socket socket(io_context);

        // 解析服务器地址并连接
        boost::asio::connect(socket, resolver.resolve("127.0.0.1", "8888"));

        std::cout << "Connected to the server!" << std::endl;

        // 向服务器发送数据
        std::string message = "Hello from client!";
        boost::asio::write(socket, boost::asio::buffer(message));

        // 读取服务器响应
        char response[128];
        size_t length = socket.read_some(boost::asio::buffer(response));
        std::cout << "Received from server: " << std::string(response, length) << std::endl;

        socket.close();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}