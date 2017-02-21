#include "../include/cluster_member.h"
#include "../include/member_list.h"
#include <iostream>
#include <boost/bind.hpp>

using namespace boost::asio;
using namespace boost::posix_time;
using namespace dive;

MemberList::MemberList(io_service& io_service, unsigned int probe_timeout) : probe_timeout_{probe_timeout} {
    probe_deadline_timer_ = std::make_unique<deadline_timer>(io_service, milliseconds(probe_timeout));
    probe_deadline_timer_->async_wait(boost::bind(&MemberList::handle_probe_deadline, this));
}

void MemberList::insert(const ClusterMember& new_member) {
    if (members_.find(new_member.name) != members_.end()) {
        // TODO(alexyer): Custom exception
        throw std::runtime_error("Member already exists.");
    }

    members_.insert({new_member.name, new_member});
}

const ClusterMember& MemberList::get(std::string name) {
    return members_.at(name);
}

const ClusterMember& MemberList::get_random() const {
    auto pair = std::next(std::begin(members_), std::rand() % members_.size());
    return pair->second;
}

const ClusterMember& MemberList::probe_random() {
    auto member = get_random();
    enqueue_probe_deadline(member);
    return get(member.name);
}

const ClusterMember& MemberList::probe_member(std::string name) {
    auto member = get(name);
    enqueue_probe_deadline(member);
    return get(member.name);
}

void MemberList::enqueue_probe_deadline(const ClusterMember& member) {
    auto restart_timer = probing_members_.empty();
    probing_members_.emplace(boost::posix_time::microsec_clock::universal_time() + milliseconds(probe_timeout_),
                             member);

    if (restart_timer) {
        restart_deadline_timer();
    }
}

bool MemberList::empty() const {
    return members_.empty();
}

void MemberList::handle_probe_deadline() {
    if (probing_members_.empty()) {
        return;
    }

    members_.erase(members_.find(probing_members_.front().member->name));
    probing_members_.pop();

    if(!probing_members_.empty()) {
        restart_deadline_timer();
    }
}

void MemberList::restart_deadline_timer() {
    probe_deadline_timer_->expires_at(probing_members_.front().expiration_time);
    probe_deadline_timer_->async_wait(boost::bind(&MemberList::handle_probe_deadline, this));
}