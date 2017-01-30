#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include "../include/dive.h"

dive::Dive dive::Dive::agent(const dive::config &conf, boost::asio::io_service &io_service) {
    return dive::Dive(conf, io_service);
}

dive::Dive::Dive(const dive::config &conf, boost::asio::io_service &io_service)
        : config_(conf), socket_(io_service, udp::endpoint(udp::v4(), conf.port)) {
    BOOST_LOG_TRIVIAL(info) << "Starting Dive agent on " << socket_.local_endpoint().address().to_string() << ":"
                            << socket_.local_endpoint().port();
    start_receive();
}

void dive::Dive::start_receive() {
    socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
                               boost::bind(&Dive::handle_receive, this, boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
}

void dive::Dive::handle_receive(const boost::system::error_code& error_code, std::size_t bytes_transferred) {
    if (!error_code) {
        std::cout << recv_buffer_.data() << std::endl;
    } else {
        // TODO(alexyer): Proper error handling
        std::cerr << error_code.message() << std::endl;
    }
    start_receive();
}

const dive::config& dive::Dive::getConfig() const {
    return config_;
}