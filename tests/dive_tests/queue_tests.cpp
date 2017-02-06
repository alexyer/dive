#include <gtest/gtest.h>
#include "lib/proto/message.pb.h"
#include "../../include/queue.h"
#include "../../include/cluster_member.h"

TEST(Queue__Test, RetransmitLimit) {
    dive::Queue queue(2);
    ASSERT_EQ(queue.retransmit_limit(4), 2);
    ASSERT_EQ(queue.retransmit_limit(10), 4);
}

TEST(Queue, DISABLED_Enqueue) {
    dive::Queue queue(2);

    dive::ClusterMember member("0.0.0.0", 6869);

    queue.enqueue_message(member, dive::ACK, dive::ALIVE);
    queue.get_message().retransmitted_count = 3;

    queue.enqueue_message(member, dive::ACK, dive::ALIVE);

    ASSERT_EQ(queue.get_message().retransmitted_count, 0);
}

TEST(Queue, EnqueueMsg) {
    dive::Queue queue(2);

    dive::DiveMessage msg;
    dive::DiveMessage other_msg;

    queue.enqueue_message(msg);
    queue.get_message().retransmitted_count = 3;

    queue.enqueue_message(other_msg);

    ASSERT_EQ(queue.get_message().retransmitted_count, 0);
}