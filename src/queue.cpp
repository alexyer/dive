#include <algorithm>
#include <functional>
#include "../include/queued_gossip.h"
#include "../include/queue.h"
#include "../include/cluster_member.h"

using namespace dive;

Queue::Queue(unsigned int retransmit_limit) : retransmit_multiplier_(retransmit_limit) {}

unsigned int Queue::retransmit_limit(unsigned int number_of_nodes) {
    return retransmit_multiplier_ * (unsigned int)std::ceil(std::log10(number_of_nodes + 1));
}

void Queue::enqueue_gossip(const Gossip &gsp) {
    queue_.push_back(QueuedGossip(gsp));
    std::make_heap(queue_.begin(), queue_.end());
}

void Queue::enqueue_gossip(const ClusterMember &member, GossipType msg_type) {
    // TODO(alexyer): Gossip initialization
    throw std::runtime_error("Not yet implemented");
    queue_.push_back(QueuedGossip());
    std::make_heap(queue_.begin(), queue_.end());
}

QueuedGossip& Queue::get_gossip() {
    return queue_.back();
}