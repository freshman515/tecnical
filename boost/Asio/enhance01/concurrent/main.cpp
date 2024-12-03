#include<iostream>
#include<boost/asio.hpp>
#include<thread>
#include<vector>
#include<functional>

//#include<string.h>
void client_handle(boost::asio::ip::tcp::socket socket) {
    auto data = std::make_shared<std::array<char, 4096>>();
    auto sock_ptr = std::make_shared<boost::asio::ip::tcp::socket>(std::move(socket));

    // 创建一个shared_ptr来存储lambda
    auto do_read = std::make_shared<std::function<void()>>();

    *do_read = [data, sock_ptr, do_read]() {
        sock_ptr->async_read_some(
            boost::asio::buffer(*data),
            [data, sock_ptr, do_read](const boost::system::error_code& ec, std::size_t length) {
                if (!ec) {
                    std::cout << "Receive: " << std::string(data->data(), length) << std::endl;
                    const char* response = "hello client\n";
                    strcpy(data->data(), response);
                    size_t response_length = strlen(response);

                    boost::asio::async_write(
                        *sock_ptr,
                        boost::asio::buffer(data->data(), response_length),
                        [data, sock_ptr, do_read](const boost::system::error_code& ec, std::size_t /*length*/) {
                            if (!ec) {
                                std::cout << "Write: hello client" << std::endl;
                                // 写完后继续读取下一个消息
                                //sock_ptr->async_read_some(boost::asio::buffer(*data), do_read);
                                *(do_read);
                            } else {
                                std::cerr << "Write error: " << ec.message() << std::endl;
                            }
                        });
                } else {
                    if (ec == boost::asio::error::eof) {
                        std::cout << "Client disconnected" << std::endl;
                    } else {
                        std::cerr << "Read error: " << ec.message() << std::endl;
                    }
                }
            });
        };

        // 开始第一次读取
    //sock_ptr->async_read_some(boost::asio::buffer(*data), do_read);
    (*do_read)();
}


void start_accept(boost::asio::io_context& io, boost::asio::ip::tcp::acceptor& acceptor) {
    acceptor.async_accept([&](const boost::system::error_code& ec, boost::asio::ip::tcp::socket socket) {
        if (!ec) {
            std::cout << "Accept a new connection" << std::endl;
            client_handle(std::move(socket));
        }
        start_accept(io, acceptor);
        });
}
int main() {
    boost::asio::io_context io;

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 12345));
    boost::asio::ip::tcp::acceptor acceptor(io, endpoint);
    start_accept(io, acceptor);
    std::vector<std::thread> threads;
    for (int i = 0;i < 5;i++) {
        threads.emplace_back([&io]() { io.run();});
    }
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}

