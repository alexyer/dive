#include <gtest/gtest.h>
#include "../../include/cluster_member.h"

TEST(ClusterMember, DefaultName) {
    auto member = dive::ClusterMember("0.0.0.0", 13);
    ASSERT_EQ(member.name, "0.0.0.0:13");
}

TEST(ClusterMember, CustomName) {
    auto member = dive::ClusterMember("test-name", "0.0.0.0", 13);
    ASSERT_EQ(member.name, "test-name");
}

TEST(ClusterMember, ip_ulong) {
    ASSERT_EQ(dive::ClusterMember("0.0.0.0", 13).ip_ulong(), 0);
    ASSERT_EQ(dive::ClusterMember("127.0.0.1", 13).ip_ulong(), 2130706433);
}