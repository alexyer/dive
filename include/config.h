#ifndef DIVE_CONFIG_H
#define DIVE_CONFIG_H

#include <string>
#include <sstream>

namespace dive {
    struct config {
        std::string name;   // The name of this node. Must be unique in the cluster.
        std::string host;
        unsigned short port;

        unsigned int probe_interval;   // Interval between probes in milliseconds.

        config(std::string host, unsigned short port, unsigned int probe_interval_ = 200)
                : host(host), port(port), probe_interval(probe_interval_) {
            std::stringstream ss;
            ss << host << ":" << port;
            name = ss.str();
        };

        config(std::string host, unsigned short port, std::string name, unsigned int probe_interval_ = 200)
                : host(host), port(port), name(name), probe_interval(probe_interval_) {}
    };
}

#endif //DIVE_CONFIG_H
