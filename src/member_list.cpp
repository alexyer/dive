#include "../include/cluster_member.h"
#include "../include/member_list.h"
#include <iostream>

using namespace dive;

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