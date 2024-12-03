#include "server.h"
#include "session.h"



server::server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {

    if (!acceptor_.is_open()) {
        std::cerr << "Failed to open acceptor on port " << port << std::endl;
    } else {
        std::cout << "Server is running on port " << port << std::endl;
    }
    do_accept();
}

void server::do_accept() {
    //std::cout << "Waiting for connections..." << std::endl;
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::cout << "have a accept!" << std::endl;
                std::make_shared<session>(std::move(socket))->start();
            }
            do_accept();
        }
    );

}
