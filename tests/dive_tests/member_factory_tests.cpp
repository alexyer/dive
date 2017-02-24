#include <gtest/gtest.h>
#include "../../include/member_factory.h"

using namespace dive;

TEST(MemberFactory, get_member__ulong) {
    auto member = dive::MemberFactory::get_member(2130706433, 13);
    ASSERT_EQ(member.ip(), 2130706433);
    ASSERT_EQ(member.port(), 13);
}

TEST(MemberFactory, get_member__str) {
    auto member = dive::MemberFactory::get_member("127.0.0.1", 13);
    ASSERT_EQ(member.ip(), 2130706433);
    ASSERT_EQ(member.port(), 13);
}
TEST(MemberFactory, get_member__cluster_member) {
    auto cluster_member = ClusterMember("127.0.0.1", 13);
    auto member = dive::MemberFactory::get_member(cluster_member);

    ASSERT_EQ(member.ip(), 2130706433);
    ASSERT_EQ(member.port(), 13);
}
