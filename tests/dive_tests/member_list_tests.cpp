#include <gtest/gtest.h>
#include <boost/date_time.hpp>
#include "../stubs/offset_time_traits.h"
#include "../stubs/offset_timer.h"
#include "../../include/member_list.h"

using namespace boost::asio;
using namespace boost::posix_time;

class MemberListTest : public ::testing::Test {
public:
    MemberListTest() : member_list_(io_service_, 100) {
        offset_time_traits::set_now(microsec_clock::local_time());
    };
protected:
    io_service io_service_;
    dive::BasicMemberList<offset_timer> member_list_;
};

TEST(MemberList, InsertMember) {
    io_service io_service;
    dive::MemberList member_list(io_service, 200);
    auto member = dive::ClusterMember("test-name", "0.0.0.0", 13);

    member_list.insert(member);

    auto inserted_member = member_list.get(member.name);

    ASSERT_EQ(member.name, inserted_member.name);
    ASSERT_EQ(member.host, inserted_member.host);
    ASSERT_EQ(member.port, inserted_member.port);
}

TEST(MemberList, InsertExistingMember) {
    io_service io_service;
    dive::MemberList member_list(io_service, 200);
    auto member = dive::ClusterMember("test-name", "0.0.0.0", 13);

    member_list.insert(member);
    ASSERT_ANY_THROW(member_list.insert(member));
}

TEST_F(MemberListTest, ProbeMember) {
    auto member = dive::ClusterMember("one", "0.0.0.0", 13);
    auto other_member = dive::ClusterMember("another", "0.0.0.0", 14);

    member_list_.insert(member);
    member_list_.insert(other_member);

    member_list_.probe_member("one");
    member_list_.probe_member("another");

    offset_time_traits::set_now(offset_time_traits::now() + seconds(10));
    io_service_.poll();

    ASSERT_THROW(member_list_.get("one"), std::out_of_range);
    ASSERT_THROW(member_list_.get("another"), std::out_of_range);
}

TEST_F(MemberListTest, ConsiderAlive) {
    auto member = dive::ClusterMember("one", "0.0.0.0", 13);
    member_list_.insert(member);

    member_list_.probe_member("one");

    offset_time_traits::set_now(offset_time_traits::now() + milliseconds(1));
    io_service_.poll();

    member_list_.consider_alive(member);
    offset_time_traits::set_now(offset_time_traits::now() + seconds(1));
    io_service_.poll();

    ASSERT_NO_THROW(member_list_.get("one"));
}

TEST_F(MemberListTest, ConsiderAliveNew) {
    auto member = dive::ClusterMember("0.0.0.0", 13);
    member_list_.consider_alive(member);
    io_service_.poll();

    offset_time_traits::set_now(offset_time_traits::now() + seconds(1));
    io_service_.poll();

    ASSERT_NO_THROW(member_list_.get("0.0.0.0:13"));
}
