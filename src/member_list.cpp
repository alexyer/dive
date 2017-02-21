#include "../include/cluster_member.h"
#include "../include/member_list.h"
#include <iostream>

using namespace dive;

MemberList::MemberList(unsigned int probe_timeout) : probe_timeout_{probe_timeout} {}

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

const ClusterMember& MemberList::probe_random() const {
    auto member = get_random();

    auto restart_timer = probing_members_.empty();

    probing_members_.push_back(ProbeDeadline(boost::posix_time::microsec_clock::universal_time(), member));

    return member;
}

bool MemberList::empty() const {
    return members_.empty();
}