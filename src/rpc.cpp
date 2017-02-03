#include <iostream>
#include <boost/bind.hpp>
#include "../include/rpc.h"

using namespace dive;
using boost::asio::ip::udp;

RPC::RPC(const config &conf, io_service &io_service)
        : socket_(io_service, udp::endpoint(udp::v4(), conf.port)) {}

void RPC::start_receive() {
    socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
                               boost::bind(&RPC::handle_receive, this, boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
}

void RPC::handle_receive(const boost::system::error_code &error_code, std::size_t bytes_transferred) {
    if (!error_code) {
        std::cout << recv_buffer_.data() << std::endl;
    } else {
        // TODO(alexyer): Proper error handling
        std::cerr << error_code.message() << std::endl;
    }
    start_receive();
}
