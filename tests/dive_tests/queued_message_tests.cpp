#include <gtest/gtest.h>
#include <lib/proto/message.pb.h>
#include "../../include/queued_message.h"

TEST(QueuedMessage__Test, ComparisonOperatorLess) {
    dive::QueuedMessage msg1;
    dive::QueuedMessage msg2;

    msg1.retransmitted_count = 3;

    ASSERT_TRUE(msg2 < msg1);
}

TEST(QueuedMessage__Test, ComparisonOperatorGreater) {
    dive::QueuedMessage msg1;
    dive::QueuedMessage msg2;

    msg1.retransmitted_count = 3;

    ASSERT_TRUE(msg1 > msg2);
}