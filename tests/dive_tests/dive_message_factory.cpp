#include <gtest/gtest.h>
#include "../../include/dive.h"
#include "../../include/dive_message_factory.h"

using namespace dive;

TEST(DiveMessageFactory, get_ping_message) {
    auto msg = std::make_unique<DiveMessage>(DiveMessageFactory::get_ping_message());
    ASSERT_EQ(msg->version(), Dive::PROTOCOL_VERSION);
    ASSERT_EQ(msg->message_type(), dive::PING);
}