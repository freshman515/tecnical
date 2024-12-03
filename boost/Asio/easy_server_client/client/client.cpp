#include "client.h"



client::client(boost::asio::io_context& io_context, std::string& ip, std::string& port)
    :socket_(io_context), timer_(io_context), write_num(0) {
    tcp::resolver resolver(io_context);
    boost::asio::connect(socket_, resolver.resolve(ip, port));
    do_write();

}

void client::do_read() {
    std::cout << "this is do_read()" << std::endl;

     // 设置定时器，等待 5 秒后超时
    timer_.expires_after(std::chrono::seconds(5));
    timer_.async_wait([this](boost::system::error_code ec) {
        if (!ec) {
            std::cerr << "Timeout: No data received in time." << std::endl;
            // 可选：在超时后处理逻辑，如关闭连接或重新尝试读取
        }
        });

        // 异步读取数据
    boost::asio::async_read(socket_, boost::asio::buffer(data_, max_length),
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "Receive: " << std::string(data_, length) << std::endl;

                if (write_num == 0) {
                    do_write();
                    write_num++;

                }


            } else {
                std::cerr << "Read error: " << ec.message() << std::endl;
            }

            // 读取完成后取消定时器
            timer_.cancel();
        }
    );
}

void client::do_write() {
    std::string msg = "hello server!";
    boost::asio::async_write(socket_, boost::asio::buffer(msg),
        [this](boost::system::error_code ec, std::size_t) {
            if (!ec) {
                std::cout << "write successfully" << std::endl;
                do_read();
            } else {
                std::cerr << "Write error: " << ec.message() << std::endl;
            }
        }
    );
}
