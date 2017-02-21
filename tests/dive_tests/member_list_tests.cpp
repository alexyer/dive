#include <gtest/gtest.h>
#include "../../include/member_list.h"

using namespace boost::asio;
using namespace boost::posix_time;

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


TEST(MemberList, ProbeMember) {
    io_service io_service;
    deadline_timer timer(io_service, milliseconds(300));

    dive::MemberList member_list(io_service, 100);
    auto member = dive::ClusterMember("one", "0.0.0.0", 13);
    auto other_member = dive::ClusterMember("another", "0.0.0.0", 14);

    member_list.insert(member);
    member_list.insert(other_member);

    member_list.probe_member("one");
    member_list.probe_member("another");

    timer.wait();
    io_service.run();

    ASSERT_THROW(member_list.get("one"), std::out_of_range);
    ASSERT_THROW(member_list.get("another"), std::out_of_range);
}
//
//TEST(MemberList, ProbeMemberWithRestart) {
//    io_service io_service;
//    deadline_timer timer(io_service, milliseconds(300));
//
//    dive::MemberList member_list(io_service, 100);
//    auto member = dive::ClusterMember("one", "0.0.0.0", 13);
//    auto other_member = dive::ClusterMember("another", "0.0.0.0", 14);
//
//    member_list.insert(member);
//    member_list.insert(other_member);
//
//    member_list.probe_member("one");
//
//    timer.async_wait([&member_list](const boost::system::error_code) {
//        member_list.probe_member("another");
//    });
//
//    timer.expires_from_now(milliseconds(300));
//    timer.async_wait([&member_list](const boost::system::error_code) {
//        ASSERT_THROW(member_list.get("one"), std::out_of_range);
//        ASSERT_THROW(member_list.get("another"), std::out_of_range);
//    });
//
//    io_service.run();
//
//}