#include "../include/member_factory.h"
#include "../lib/utils/utils.h"

using namespace dive;

Member& MemberFactory::get_member(unsigned long ip, unsigned int port) {
    auto member = new Member();
    member->set_ip(ip);
    member->set_port(port);

    return *member;
}

Member& MemberFactory::get_member(std::string ip, unsigned int port) {
    return get_member(utils::ip_str2ulong(ip), port);
}

Member& MemberFactory::get_member(const ClusterMember& cluster_member) {
    return get_member(cluster_member.host, cluster_member.port);
}