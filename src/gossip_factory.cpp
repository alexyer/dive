#include <lib/proto/message.pb.h>
#include "../include/gossip_factory.h"

using namespace dive;

Gossip& GossipFactory::get_alive_gossip(Member* member) {
    auto gossip = new Gossip();

    gossip->set_gossip_type(GossipType::ALIVE);
    gossip->set_allocated_member(member);

    return *gossip;
}
