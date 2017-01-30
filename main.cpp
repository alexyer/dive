#include <iostream>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include "include/config.h"
#include "include/dive.h"

namespace po = boost::program_options;

std::string host;
u_short port;

int main(int argc, char* argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("host", po::value<std::string>(&host)->default_value("0.0.0.0"), "Dive server host. Default: 0.0.0.0")
            ("port", po::value<u_short>(&port)->default_value(6869), "Dive server port. Default: 6869");

    po::variables_map vm;

    try {
        po::store(po::parse_command_line(argc, (const char *const *) argv, desc), vm);
    } catch (std::exception& exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    }

    po::notify(vm);
    boost::asio::io_service io_service;

    dive::config config(host, port);
    dive::Dive dive(config, io_service);

    io_service.run();

    return 0;
}