#ifndef DIVE_GOSSIP_FACTORY_H
#define DIVE_GOSSIP_FACTORY_H

#include <lib/proto/message.pb.h>

namespace dive {
    class GossipFactory {
    public:
        static Gossip& get_alive_gossip(Member*);
    };
}

#endif //DIVE_GOSSIP_FACTORY_H
