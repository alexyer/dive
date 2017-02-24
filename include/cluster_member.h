#ifndef DIVE_CLUSTER_MEMBER_H
#define DIVE_CLUSTER_MEMBER_H

#include <sstream>
#include "../lib/utils/utils.h"
#include "../lib/lamport_clock/lamport_clock.h"

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
            return utils::ip_str2ulong(host);
        }
    };
}

#endif //DIVE_CLUSTER_MEMBER_H
