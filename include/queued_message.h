#ifndef DIVE_QUEUED_MESSAGE_H
#define DIVE_QUEUED_MESSAGE_H

#include <lib/proto/message.pb.h>

using namespace dive;

namespace dive {
    struct QueuedMessage {
        std::unique_ptr<DiveMessage> msg;
        unsigned int retransmitted_count;

        QueuedMessage(const DiveMessage& msg) : msg(std::make_unique<DiveMessage>(msg)), retransmitted_count(0) {}
        QueuedMessage(const Member&, MessageType, GossipType);
    };
}

#endif //DIVE_QUEUED_MESSAGE_H
