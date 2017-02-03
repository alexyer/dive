#include <iostream>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include "include/config.h"
#include "include/dive.h"

namespace po = boost::program_options;

std::string command;
std::string node_addr;
std::string host;
u_short port;
po::options_description join_desc("join options");


int main(int argc, char *argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("command", po::value<std::string>(&command), "command to execute")
            ("subargs", po::value<std::vector<std::string> >(), "Arguments for command")
            ("host", po::value<std::string>(&host)->default_value("0.0.0.0"), "Dive server host. Default: 0.0.0.0")
            ("port", po::value<u_short>(&port)->default_value(6869), "Dive server port. Default: 6869");

    po::positional_options_description pos;
    pos.add("command", 1).add("subargs", -1);

    po::variables_map vm;

    try {
        auto parsed_options = po::command_line_parser(argc, (const char *const *) argv).
                options(desc).
                positional(pos).
                allow_unregistered().
                run();

        po::store(parsed_options, vm);
        po::notify(vm);

        if (command == "join") {
            join_desc.add_options()
                    ("node-addr", po::value<std::string>(&node_addr), "Address to the server you want to connect.");

            std::vector<std::string> opts = po::collect_unrecognized(parsed_options.options, po::include_positional);
            opts.erase(opts.begin());

            po::store(po::command_line_parser(opts).options(join_desc).run(), vm);
        }

    } catch (std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    }

    boost::asio::io_service io_service;
    dive::config config(host, port);

    if (command == "agent") {
        auto dive = dive::Dive::agent(config, io_service);
        io_service.run();
    } else if (command == "join") {
        auto dive = dive::Dive::join(config, io_service, node_addr);
        io_service.run();
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}