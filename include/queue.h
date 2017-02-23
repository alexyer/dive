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
        Queue(unsigned int retransmit_multiplier);

        /***
         * Enqueue message.
         * @param gsp Message to enqueue.
         */
        void enqueue_gossip(const Gossip& gsp);
        void enqueue_gossip(const ClusterMember& member, GossipType);
        void enqueue_gossip(const Member& member, GossipType);
        /***
         * Update heap.
         * FIXME(alexyer): Bad name.
         */
        void rebuild();
        QueuedGossip& get_gossip();
        unsigned int retransmit_limit(size_t);
        unsigned long size();

        /***
         * Pop gossip and rebuild queue.
         */
        void pop();

    private:
        unsigned int retransmit_multiplier_;

        /***
         * Min heap of queued messages.
         */
        std::vector<QueuedGossip> queue_;
    };
}

#endif //DIVE_QUEUE_H
