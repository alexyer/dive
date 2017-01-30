#ifndef DIVE_CONFIG_H
#define DIVE_CONFIG_H

#include <string>
#include <sstream>

namespace dive {
    struct config {
        std::string name;   // The name of this node. Must be unique in the cluster.
        std::string host;
        unsigned short port;

        config(std::string host, unsigned short port) : host(host), port(port) {
            std::stringstream ss;
            ss << host << ":" << port;
            name = ss.str();
        };

        config(std::string host, unsigned short port, std::string name) : host(host), port(port), name(name) {}
    };
}

#endif //DIVE_CONFIG_H
