#ifndef DIVE_CLUSTER_MEMBER_H
#define DIVE_CLUSTER_MEMBER_H

#include <sstream>
#include <boost/asio.hpp>

namespace dive {
    struct ClusterMember {
        std::string name;
        std::string host;
        unsigned short port;

        ClusterMember(std::string name, std::string host, unsigned short port) : name(name), host(host), port(port) {}
        ClusterMember(std::string host, unsigned short port) : host(host), port(port) {
            std::stringstream ss;
            ss << host << ":" << port;
            name = ss.str();
        }

        unsigned long ip_ulong() const {
            return boost::asio::ip::address_v4::from_string(host).to_ulong();
        }
    };
}

#endif //DIVE_CLUSTER_MEMBER_H
