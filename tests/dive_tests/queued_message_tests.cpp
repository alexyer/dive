#include <gtest/gtest.h>
#include <lib/proto/message.pb.h>
#include "../../include/queued_message.h"

TEST(QueuedMessage__Test, ComparisonOperator) {
    dive::QueuedMessage msg1;
    dive::QueuedMessage msg2;

    msg1.retransmitted_count = 3;

    ASSERT_TRUE(msg2 < msg1);
}