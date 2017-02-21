#include <gtest/gtest.h>
#include "../../include/member_list.h"

using namespace boost::asio;
using namespace boost::posix_time;

TEST(MemberList, InsertMember) {
    io_service io_service;
    dive::MemberList member_list(io_service, 200);
    auto member = dive::ClusterMember("test-name", "0.0.0.0", 13);

    member_list.insert(member);

    auto inserted_member = member_list.get(member.name);

    ASSERT_EQ(member.name, inserted_member.name);
    ASSERT_EQ(member.host, inserted_member.host);
    ASSERT_EQ(member.port, inserted_member.port);
}

TEST(MemberList, InsertExistingMember) {
    io_service io_service;
    dive::MemberList member_list(io_service, 200);
    auto member = dive::ClusterMember("test-name", "0.0.0.0", 13);

    member_list.insert(member);
    ASSERT_ANY_THROW(member_list.insert(member));
}
