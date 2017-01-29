#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>
#include "../include/dive.h"


dive::Dive::Dive(const dive::config &conf, boost::asio::io_service &io_service)
        : config_(conf), socket_(io_service, udp::endpoint(udp::v4(), conf.port)) {
    BOOST_LOG_TRIVIAL(info) << "Starting Dive agent on " << socket_.local_endpoint().address().to_string() << ":"
                            << socket_.local_endpoint().port();
}