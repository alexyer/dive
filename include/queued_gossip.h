#ifndef DIVE_QUEUED_GOSSIP_H
#define DIVE_QUEUED_GOSSIP_H

#include <memory>
#include <lib/proto/message.pb.h>

using namespace dive;

namespace dive {
    struct QueuedGossip {
        std::unique_ptr<Gossip> gsp;
        unsigned int retransmitted_count;

        QueuedGossip() : gsp(nullptr), retransmitted_count(0) {}
        QueuedGossip(const Gossip &gsp) : gsp(std::make_unique<Gossip>(gsp)), retransmitted_count(0) {}
        QueuedGossip(const Member &, GossipType);

        friend bool operator<(const QueuedGossip& l, const QueuedGossip& r) {
            return l.retransmitted_count < r.retransmitted_count;
        };

        friend bool operator>(const QueuedGossip& l, const QueuedGossip& r) {
            return r < l;
        };
    };
}

#endif //DIVE_QUEUED_GOSSIP_H
