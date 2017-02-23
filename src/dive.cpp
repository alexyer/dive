#include <iostream>
#include <sstream>

#include <boost/asio.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>

#include "../include/errors.h"
#include "../include/cluster_member.h"
#include "../include/dive.h"
#include "../include/member_factory.h"
#include "../include/dive_message_factory.h"

using namespace boost::asio;
using namespace boost::posix_time;
using namespace dive;

const std::string Dive::VERSION = "0.0.1";
const unsigned short Dive::PROTOCOL_VERSION = 1;

Dive Dive::agent(const config& conf, io_service& io_service) {
    return Dive(conf, io_service);
}

Dive Dive::join(const dive::config& conf, boost::asio::io_service& io_service, std::string node_address) {
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

Dive::Dive(const config& conf, io_service& io_service)
        : config_(conf),
          rpc_(conf, io_service, std::bind(&Dive::rpc_receive_cb, this, std::placeholders::_1, std::placeholders::_2)),
          queue_(conf.retransmit_multiplier), member_list_(io_service, conf.probe_timeout) {
    BOOST_LOG_TRIVIAL(info) << "Starting Dive agent on " << config_.host << ":" << config_.port;
    rpc_.start_receive();
    start_probing(io_service);
}

void Dive::start_probing(boost::asio::io_service& io_service_) {
    BOOST_LOG_TRIVIAL(debug) << "Start pinging";
    probe_timer_ = std::make_unique<deadline_timer>(io_service_, milliseconds(config_.probe_interval));
    probe_timer_->async_wait(boost::bind(&Dive::handle_probe, this));
}

void Dive::handle_probe() {
    if (!member_list_.empty()) {
        auto probe_member = member_list_.get_random();

//        BOOST_LOG_TRIVIAL(debug) << "Probing node: " << probe_member.name;

        auto dst_cluster_member = member_list_.probe_random();
        auto destination = std::make_unique<Member>(
                MemberFactory::get_member(dst_cluster_member.host, dst_cluster_member.port));
        auto msg = DiveMessageFactory::get_ping_message(destination.get());
        piggyback_gossips(msg);
        rpc_.enqueue_send_message(msg);
    }

    restart_probe_timer();
}

void Dive::restart_probe_timer() {
    probe_timer_->expires_at(probe_timer_->expires_at() + milliseconds(config_.probe_interval));
    probe_timer_->async_wait(boost::bind(&Dive::handle_probe, this));
}

const config& Dive::getConfig() const {
    return config_;
}

void Dive::rpc_receive_cb(std::array<char, 128> buffer, udp::endpoint remote_endpoint) {
    DiveMessage msg;
    msg.ParseFromArray(buffer.data(), 128);

    switch (msg.message_type()) {
        case dive::PING:
            handle_ping(msg, remote_endpoint);
            break;
        case dive::ACK:
            handle_ack(msg, remote_endpoint);
            break;
        default:
            throw UnknownCommandTypeError(msg.message_type());
    }
}

void Dive::handle_ping(const DiveMessage& msg, udp::endpoint remote_endpoint) {
    read_gossips(msg);

    auto destination = std::make_unique<Member>(
            MemberFactory::get_member(remote_endpoint.address().to_string(), remote_endpoint.port()));
    auto ack_msg = DiveMessageFactory::get_ack_message(destination.get());

    rpc_.enqueue_send_message(ack_msg);
}

void Dive::handle_ack(const DiveMessage& msg, udp::endpoint remote_endpoint) {
    auto member = ClusterMember(remote_endpoint.address().to_string(), remote_endpoint.port());
    member_list_.consider_alive(member);
    read_gossips(msg);
}

void Dive::read_gossips(const DiveMessage& msg) {
    if (msg.gossips_size()) {
        for (auto gossip : msg.gossips()) {
            switch (gossip.gossip_type()) {
                case GossipType::ALIVE:
                    handle_gossip_alive(gossip);
                    break;
            }
        }
    }
}

void Dive::piggyback_gossips(DiveMessage& msg) {
    if (queue_.size()) {
        auto gossip_batch_count =
                config_.gossip_batch_count < queue_.size() ? config_.gossip_batch_count : queue_.size();
        for (unsigned int i = 0; i < gossip_batch_count; ++i) {
            auto& gossip = queue_.get_gossip();
            msg.add_gossips()->CopyFrom(*gossip.gsp);
            ++gossip.retransmitted_count;
            queue_.rebuild();
        }
    }
}

void Dive::handle_gossip_alive(const Gossip& gsp) {
    ip::address_v4 ip(gsp.member().ip());
    auto member = ClusterMember(ip.to_string(), gsp.member().port());
    member_list_.consider_alive(member);
}