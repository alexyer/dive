#include <gtest/gtest.h>
#include <lib/proto/message.pb.h>
#include "../../include/gossip_factory.h"
#include "../../include/member_factory.h"

using namespace dive;

TEST(GossipFactory, GetAliveGossip) {
    auto member = std::make_unique<Member>(MemberFactory::get_member("0.0.0.0", 13));
    auto gossip = GossipFactory::get_alive_gossip(member.get());

    ASSERT_EQ(gossip.gossip_type(), GossipType::ALIVE);
    ASSERT_EQ(gossip.member().ip(), member->ip());
    ASSERT_EQ(gossip.member().port(), member->port());
}