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

void Queue::enqueue_gossip(const ClusterMember &member, GossipType gsp_type) {
    Gossip gossip;
    gossip.set_gossip_type(gsp_type);

    Member gsp_member;
    gsp_member.set_ip(member.ip_ulong());
    gsp_member.set_port(member.port);

    gossip.mutable_member()->Swap(&gsp_member);

    queue_.push_back(QueuedGossip(gossip));
    std::make_heap(queue_.begin(), queue_.end());
}

QueuedGossip& Queue::get_gossip() {
    return queue_.back();
}