#include <algorithm>
#include <functional>
#include "../include/queued_message.h"
#include "../include/queue.h"
#include "../include/cluster_member.h"

using namespace dive;

Queue::Queue(unsigned int retransmit_limit) : retransmit_multiplier_(retransmit_limit) {}

unsigned int Queue::retransmit_limit(unsigned int number_of_nodes) {
    return retransmit_multiplier_ * (unsigned int)std::ceil(std::log10(number_of_nodes + 1));
}

void Queue::enqueue_message(const DiveMessage &msg) {
    queue_.push_back(QueuedMessage(msg));
    std::make_heap(queue_.begin(), queue_.end());
}

void Queue::enqueue_message(const ClusterMember &member, MessageType msg_type, GossipType gsp_type) {
    // TODO(alexyer): Message initialization
    throw std::runtime_error("Not yet implemented");
    queue_.push_back(QueuedMessage());
    std::make_heap(queue_.begin(), queue_.end());
}

QueuedMessage& Queue::get_message() {
    return queue_.back();
}