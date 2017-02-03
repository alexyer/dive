#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include "../include/dive.h"

using namespace boost::asio;
using namespace boost::posix_time;
using namespace dive;

const std::string Dive::VERSION = "0.0.1";
const unsigned short Dive::PROTOCOL_VERSION = 1;

Dive Dive::agent(const config& conf, io_service &io_service) {
    return Dive(conf, io_service);
}

Dive Dive::join(const dive::config& conf, boost::asio::io_service& io_service, std::string node_address) {
    auto dive = Dive(conf, io_service);
    return dive;
}

Dive::Dive(const config &conf, io_service &io_service)
        : config_(conf), rpc_(conf, io_service) {
    BOOST_LOG_TRIVIAL(info) << "Starting Dive agent on " << config_.host << ":" << config_.port << std::endl;
    rpc_.start_receive();
    start_gossiping(io_service);
}

void Dive::start_gossiping(boost::asio::io_service& io_service_) {
    BOOST_LOG_TRIVIAL(debug) << "Start gossiping" << std::endl;
    gossip_timer_ = std::make_shared<deadline_timer>(io_service_, milliseconds(config_.gossip_interval));
    gossip_timer_->async_wait(boost::bind(&Dive::handle_gossip, this));
}

void Dive::handle_gossip() {
    std::cout << "Hey, Dude!" << std::endl;
    restart_gossip_timer();
}

void Dive::restart_gossip_timer() {
    gossip_timer_->expires_at(gossip_timer_->expires_at() + milliseconds(config_.gossip_interval));
    gossip_timer_->async_wait(boost::bind(&Dive::handle_gossip, this));
}

const config &Dive::getConfig() const {
    return config_;
}