#include <iostream>
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>
#include "../include/rpc.h"

using namespace dive;
using boost::asio::ip::udp;
using namespace boost::posix_time;

RPC::RPC(const config &conf, io_service &io_service)
        : socket_(io_service, udp::endpoint(udp::v4(), conf.port)),
        // Use the smallest interval to empty queue faster
          send_probe_period_(conf.probe_interval < conf.gossip_interval ? conf.probe_interval : conf.gossip_interval) {
    start_send(io_service);
}

void RPC::start_receive() {
    socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
                               boost::bind(&RPC::handle_receive, this, boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
}

void RPC::start_send(io_service &io_service) {
    BOOST_LOG_TRIVIAL(debug) << "RPC: start sending";
    send_queue_timer_ = std::make_unique<deadline_timer>(io_service, milliseconds(send_probe_period_));
    send_queue_timer_->async_wait(boost::bind(&RPC::handle_send, this));
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

void RPC::handle_send() {
    BOOST_LOG_TRIVIAL(debug) << "send";

    send_queue_timer_->expires_at(send_queue_timer_->expires_at() + milliseconds(send_probe_period_));
    send_queue_timer_->async_wait(boost::bind(&RPC::handle_send, this));
}

void RPC::enqueue_send_message(std::string msg) {
    send_queue_.push(msg);
}
