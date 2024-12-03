#include "session.h"





tcp::socket& session::socket() {
    return socket_;
}

void session::start() {
    do_read();
}

void session::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "Received :" << data_ << std::endl;
                memcpy(response_, "hello client,im server", sizeof("hello client,im server"));
                do_write();
            } else {
                std::cerr << "Read error: " << ec.message() << std::endl;
            }
        }
    );
}

void session::do_write() {
    auto self(shared_from_this());
    if (!response_) {
        std::cout << "Ready to write response: " << response_ << std::endl;
       // do_write();
    } else {
        std::cerr << "Response is empty, not writing to client!" << std::endl;
    }
    boost::asio::async_write(socket_, boost::asio::buffer(response_, max_length),
        [this, self](boost::system::error_code ec, std::size_t) {
            if (!ec) {
                std::cout << "Send a new message to client" << std::endl;
                do_read();
            } else {
                std::cerr << "Write error: " << ec.message() << std::endl;
            }
        }
    );
}

