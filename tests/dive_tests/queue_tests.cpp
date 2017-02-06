#include <gtest/gtest.h>
#include "../../include/queue.h"

TEST(Queue__Test, RetransmitLimit) {
    dive::Queue queue(2);
    ASSERT_EQ(queue.retransmit_limit(4), 2);
    ASSERT_EQ(queue.retransmit_limit(10), 4);
}