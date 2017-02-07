#include <gtest/gtest.h>
#include "lib/proto/message.pb.h"
#include "../../include/queue.h"
#include "../../include/cluster_member.h"

TEST(Queue__Test, RetransmitLimit) {
    dive::Queue queue(2);
    ASSERT_EQ(queue.retransmit_limit(4), 2);
    ASSERT_EQ(queue.retransmit_limit(10), 4);
}

TEST(Queue, Enqueue) {
    dive::Queue queue(2);

    dive::ClusterMember member("0.0.0.0", 6869);

    queue.enqueue_gossip(member, dive::ALIVE);
    queue.get_gossip().retransmitted_count = 3;

    queue.enqueue_gossip(member, dive::ALIVE);

    ASSERT_EQ(queue.get_gossip().retransmitted_count, 0);
}

TEST(Queue, EnqueueMsg) {
    dive::Queue queue(2);

    dive::Gossip gsp;
    dive::Gossip other_gsp;

    queue.enqueue_gossip(gsp);
    queue.get_gossip().retransmitted_count = 3;

    queue.enqueue_gossip(other_gsp);

    ASSERT_EQ(queue.get_gossip().retransmitted_count, 0);
}