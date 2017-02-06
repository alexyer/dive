#ifndef DIVE_QUEUED_MESSAGE_H
#define DIVE_QUEUED_MESSAGE_H

#include <lib/proto/message.pb.h>

using namespace dive;

namespace dive {
    struct QueuedMessage {
        std::unique_ptr<DiveMessage> msg;
        unsigned int retransmitted_count;

        QueuedMessage() : msg(nullptr), retransmitted_count(0) {}
        QueuedMessage(const DiveMessage &msg) : msg(std::make_unique<DiveMessage>(msg)), retransmitted_count(0) {}
        QueuedMessage(const Member &, MessageType, GossipType);

        inline bool operator<(const QueuedMessage &other) {
            return retransmitted_count < other.retransmitted_count;
        };
    };
}

#endif //DIVE_QUEUED_MESSAGE_H
