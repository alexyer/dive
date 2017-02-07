#ifndef DIVE_QUEUE_H
#define DIVE_QUEUE_H

#include <vector>
#include <lib/proto/message.pb.h>
#include "queued_gossip.h"
#include "cluster_member.h"

using namespace dive;

namespace dive {
    /***
     * Gossip queue.
     * Contains messages for retransmitting.
     */
    class Queue {
    public:
        Queue(unsigned int);

        /***
         * Enqueue message.
         * @param gsp Message to enqueue.
         */
        void enqueue_gossip(const Gossip& gsp);
        void enqueue_gossip(const ClusterMember& member, GossipType);
        QueuedGossip& get_gossip();
        unsigned int retransmit_limit(unsigned int);
    private:
        unsigned int retransmit_multiplier_;

        /***
         * Min heap of queued messages.
         */
        std::vector<QueuedGossip> queue_;
    };
}

#endif //DIVE_QUEUE_H
