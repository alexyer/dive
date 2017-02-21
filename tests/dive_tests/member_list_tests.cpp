#include <gtest/gtest.h>
#include "../../include/member_list.h"

TEST(MemberList__Test, InsertMember) {
    dive::MemberList member_list(200);
    auto member = dive::ClusterMember("test-name", "0.0.0.0", 13);

    member_list.insert(member);

    auto inserted_member = member_list.get(member.name);

    ASSERT_EQ(member.name, inserted_member.name);
    ASSERT_EQ(member.host, inserted_member.host);
    ASSERT_EQ(member.port, inserted_member.port);
}

TEST(Member__Test, InsertExistingMember) {
    dive::MemberList member_list(200);
    auto member = dive::ClusterMember("test-name", "0.0.0.0", 13);

    member_list.insert(member);
    ASSERT_ANY_THROW(member_list.insert(member));
}
