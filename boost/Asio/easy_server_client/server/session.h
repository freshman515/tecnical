#pragma once
#include<iostream>
#include<boost/asio.hpp>
using boost::asio::ip::tcp;
class session :public std::enable_shared_from_this<session> {
public:
   // explicit session(boost::asio::io_context& io_context) :socket_(io_context) {}
    explicit session(tcp::socket socket) : socket_(std::move(socket)) {}
    tcp::socket& socket();
    void start();
private:
    void do_read();
    void do_write();
    tcp::socket socket_;
    enum { max_length = 4096 };
    char data_[max_length];
    char response_[max_length];
};