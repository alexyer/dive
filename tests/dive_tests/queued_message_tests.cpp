#include <gtest/gtest.h>
#include <lib/proto/message.pb.h>
#include "../../include/queued_gossip.h"

TEST(QueuedMessage, ComparisonOperatorLess) {
    dive::QueuedGossip msg1;
    dive::QueuedGossip msg2;

    msg1.retransmitted_count = 3;

    ASSERT_TRUE(msg2 < msg1);
}

TEST(QueuedGossip, ComparisonOperatorGreater) {
    dive::QueuedGossip msg1;
    dive::QueuedGossip msg2;

    msg1.retransmitted_count = 3;

    ASSERT_TRUE(msg1 > msg2);
}