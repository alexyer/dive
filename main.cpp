#include <iostream>
#include <boost/program_options.hpp>

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

    std::cout << host << ":" << std::to_string(port) << std::endl;
    return 0;
}