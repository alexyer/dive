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