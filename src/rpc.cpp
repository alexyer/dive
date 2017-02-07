#include <iostream>
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>
#include "../include/rpc.h"

using namespace dive;
using boost::asio::ip::udp;
using namespace boost::posix_time;

RPC::RPC(const config &conf, io_service &io_service, receive_handler handler)
        : socket_(io_service, udp::endpoint(udp::v4(), conf.port)),
        // Use the smallest interval to empty queue faster
          send_probe_period_(conf.probe_interval < conf.gossip_interval ? conf.probe_interval : conf.gossip_interval),
          receive_handler_cb_(handler) {
    start_send(io_service);
}

void RPC::start_receive() {
    socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
                               boost::bind(&RPC::handle_receive, this, boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
}

void RPC::start_send(io_service & io_service) {
    BOOST_LOG_TRIVIAL(debug) << "RPC: start sending";
    send_queue_timer_ = std::make_unique<deadline_timer>(io_service, milliseconds(send_probe_period_));
    send_queue_timer_->async_wait(boost::bind(&RPC::handle_send, this));
}

void RPC::handle_receive(const boost::system::error_code &error_code, std::size_t bytes_transferred) {
    if (!error_code) {
        receive_handler_cb_(recv_buffer_);
    } else {
        // TODO(alexyer): Proper error handling
        std::cerr << error_code.message() << std::endl;
    }
    start_receive();
}

void RPC::handle_send() {
    send_messages();

    send_queue_timer_->expires_at(send_queue_timer_->expires_at() + milliseconds(send_probe_period_));
    send_queue_timer_->async_wait(boost::bind(&RPC::handle_send, this));
}

void RPC::send_messages() {
    while (!send_queue_.empty()) {
        const auto &msg = send_queue_.front();
        auto serialized_msg = std::make_shared<std::string>();
        msg.SerializeToString(serialized_msg.get());

        ip::address_v4 addr(msg.destination().ip());
        udp::endpoint endpoint;
        endpoint.address(addr);
        endpoint.port(msg.destination().port());

        socket_.async_send_to(boost::asio::buffer(*serialized_msg), endpoint,
                              boost::bind(&RPC::async_send_cb, this, serialized_msg, boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred));
        send_queue_.pop();
    }
}

void RPC::async_send_cb(const std::shared_ptr<std::string>, const boost::system::error_code &, std::size_t) {}

void RPC::enqueue_send_message(DiveMessage msg) {
    send_queue_.push(msg);
}
