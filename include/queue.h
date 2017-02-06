#ifndef DIVE_QUEUE_H
#define DIVE_QUEUE_H

#include <lib/proto/message.pb.h>

using namespace dive;

namespace dive {
    /***
     * Gossip queue.
     * Contains messages for retransmitting.
     */
    class Queue {
    public:
        Queue(unsigned int);
        void enqueue_message(const DiveMessage&);
        unsigned int retransmit_limit(unsigned int);
    private:
        unsigned int retransmit_multiplier_;
    };
}

#endif //DIVE_QUEUE_H
