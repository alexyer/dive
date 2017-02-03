#include <gtest/gtest.h>
#include "../../include/member.h"

TEST(Member__Test, DefaultNameTest) {
    auto member = dive::Member("0.0.0.0", 13);
    ASSERT_EQ(member.name, "0.0.0.0:13");
}

TEST(Member__Test, CustomNameTest) {
    auto member = dive::Member("test-name", "0.0.0.0", 13);
    ASSERT_EQ(member.name, "test-name");
}
