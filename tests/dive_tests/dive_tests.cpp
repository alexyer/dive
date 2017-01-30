#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include "../../include/dive.h"

TEST(Dive__Test, DefaultNameTest) {
    boost::asio::io_service io_service;
    dive::config config("0.0.0.0", 6869);
    dive::Dive dive(config, io_service);

    ASSERT_EQ(dive.getConfig().name, "0.0.0.0:6869");
}

TEST(Dive__Test, CustomNameTest) {
    boost::asio::io_service io_service;
    dive::config config("0.0.0.0", 6869, "test-name");
    dive::Dive dive(config, io_service);

    ASSERT_EQ(dive.getConfig().name, "test-name");
}