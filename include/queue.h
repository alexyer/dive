#ifndef DIVE_QUEUE_H
#define DIVE_QUEUE_H

#include <vector>
#include <lib/proto/message.pb.h>
#include "queued_message.h"
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
         * @param msg Message to enqueue.
         */
        void enqueue_message(const DiveMessage& msg);
        void enqueue_message(const ClusterMember& member, MessageType, GossipType);
        QueuedMessage& get_message();
        unsigned int retransmit_limit(unsigned int);
    private:
        unsigned int retransmit_multiplier_;

        /***
         * Min heap of queued messages.
         */
        std::vector<QueuedMessage> queue_;
    };
}

#endif //DIVE_QUEUE_H
