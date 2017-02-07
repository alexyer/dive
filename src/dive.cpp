#include <boost/asio.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include "../include/cluster_member.h"
#include "../include/dive.h"
#include "../include/member_factory.h"
#include "../include/dive_message_factory.h"

using namespace boost::asio;
using namespace boost::posix_time;
using namespace dive;

const std::string Dive::VERSION = "0.0.1";
const unsigned short Dive::PROTOCOL_VERSION = 1;

Dive Dive::agent(const config &conf, io_service &io_service) {
    return Dive(conf, io_service);
}

Dive Dive::join(const dive::config &conf, boost::asio::io_service &io_service, std::string node_address) {
    auto dive = Dive(conf, io_service);

    std::vector<std::string> details;
    boost::split(details, node_address, boost::is_any_of(":"));

    // TODO(alexyer): input data validation.
    auto host = details[0];
    auto port = std::stoi(details[1]);

    dive.queue_.enqueue_gossip(MemberFactory::get_member(conf.host, conf.port), dive::ALIVE);
    dive.member_list_.insert(ClusterMember(host, port));

    return dive;
}

Dive::Dive(const config &conf, io_service &io_service)
        : config_(conf), rpc_(conf, io_service), queue_(conf.retransmit_multiplier) {
    BOOST_LOG_TRIVIAL(info) << "Starting Dive agent on " << config_.host << ":" << config_.port;
    rpc_.start_receive();
    start_gossiping(io_service);
    start_probing(io_service);
}

void Dive::start_gossiping(boost::asio::io_service &io_service_) {
    BOOST_LOG_TRIVIAL(debug) << "Start gossiping";
    gossip_timer_ = std::make_unique<deadline_timer>(io_service_, milliseconds(config_.gossip_interval));
    gossip_timer_->async_wait(boost::bind(&Dive::handle_gossip, this));
}

void Dive::start_probing(boost::asio::io_service &io_service_) {
    BOOST_LOG_TRIVIAL(debug) << "Start pinging";
    probe_timer_ = std::make_unique<deadline_timer>(io_service_, milliseconds(config_.probe_interval));
    probe_timer_->async_wait(boost::bind(&Dive::handle_probe, this));
}

void Dive::handle_gossip() {
    restart_gossip_timer();
}

void Dive::handle_probe() {
    if (!member_list_.empty()) {
        auto probe_member = member_list_.get_random();

        BOOST_LOG_TRIVIAL(debug) << "Probing node: " << probe_member.name;

        auto dst_cluster_member = member_list_.get_random();
        auto destination = std::make_unique<Member>(
                MemberFactory::get_member(dst_cluster_member.host, dst_cluster_member.port));
        auto msg = DiveMessageFactory::get_ping_message(destination.get());
        rpc_.enqueue_send_message(msg);
    }

    restart_probe_timer();
}

void Dive::restart_gossip_timer() {
    gossip_timer_->expires_at(gossip_timer_->expires_at() + milliseconds(config_.gossip_interval));
    gossip_timer_->async_wait(boost::bind(&Dive::handle_gossip, this));
}

void Dive::restart_probe_timer() {
    probe_timer_->expires_at(probe_timer_->expires_at() + milliseconds(config_.probe_interval));
    probe_timer_->async_wait(boost::bind(&Dive::handle_probe, this));
}

const config &Dive::getConfig() const {
    return config_;
}