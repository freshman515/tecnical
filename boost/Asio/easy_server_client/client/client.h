#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

class client {
public:
    client(boost::asio::io_context& io_context, std::string& ip, std::string& port);

private:
    void do_read();
    void do_write();

    boost::asio::ip::tcp::socket socket_;
    boost::asio::steady_timer timer_;
    enum { max_length = 1024 };
    char data_[max_length];
    int write_num;
};

#endif