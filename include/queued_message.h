#ifndef DIVE_QUEUED_MESSAGE_H
#define DIVE_QUEUED_MESSAGE_H

using namespace dive;

namespace dive {
    struct QueuedMessage {
        std::shared_ptr<DiveMessage> msg;
        unsigned int retransmitted_count;

        QueuedMessage(msg) : msg(msg), retransmitted_count(0) {}
        QueuedMessage(const Member&, MessageType, GossipType);
    };
}

#endif //DIVE_QUEUED_MESSAGE_H
