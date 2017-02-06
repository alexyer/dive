#ifndef DIVE_QUEUED_MESSAGE_H
#define DIVE_QUEUED_MESSAGE_H

#include <memory>
#include <lib/proto/message.pb.h>

using namespace dive;

namespace dive {
    struct QueuedMessage {
        std::unique_ptr<DiveMessage> msg;
        unsigned int retransmitted_count;

        QueuedMessage() : msg(nullptr), retransmitted_count(0) {}
        QueuedMessage(const DiveMessage &msg) : msg(std::make_unique<DiveMessage>(msg)), retransmitted_count(0) {}
        QueuedMessage(const Member &, MessageType, GossipType);

        friend bool operator<(const QueuedMessage& l, const QueuedMessage &r) {
            return l.retransmitted_count < r.retransmitted_count;
        };

        friend bool operator>(const QueuedMessage& l, const QueuedMessage& r) {
            return r < l;
        };
    };
}

#endif //DIVE_QUEUED_MESSAGE_H
