#pragma once
#include<iostream>
#include<boost/asio.hpp>
using boost::asio::ip::tcp;

class server {
public:

    server(boost::asio::io_context& io_context, short port);
private:
    void do_accept();
    tcp::acceptor acceptor_;
};