#include <gtest/gtest.h>
#include "../../include/dive.h"
#include "../../include/dive_message_factory.h"
#include "../../include/member_factory.h"

using namespace dive;

TEST(DiveMessageFactory, get_ping_message) {
    auto member = std::make_unique<Member>(MemberFactory::get_member("0.0.0.0", 13));
    auto msg = std::make_unique<DiveMessage>(DiveMessageFactory::get_ping_message(member.get()));
    ASSERT_EQ(msg->version(), Dive::PROTOCOL_VERSION);
    ASSERT_EQ(msg->message_type(), dive::PING);
}