#ifndef DIVE_CONFIG_H
#define DIVE_CONFIG_H

#include <string>
#include <sstream>

namespace dive {
    struct config {
        std::string name;   // The name of this node. Must be unique in the cluster.
        std::string host;
        unsigned short port;

        /// Interval between probes in milliseconds.
        unsigned int probe_interval;

        /// Retransmit multiplier for the number of retransmissions are attempted for messages broadcast
        /// over gossips.
        unsigned int retransmit_multiplier;

        config(std::string host, unsigned short port, unsigned int probe_interval_ = 200,
               unsigned int retransmit_multiplier_ = 2)
                : host(host), port(port), probe_interval(probe_interval_),
                  retransmit_multiplier(retransmit_multiplier_) {
            std::stringstream ss;
            ss << host << ":" << port;
            name = ss.str();
        };

        config(std::string host, unsigned short port, std::string name, unsigned int probe_interval_ = 200,
               unsigned int retransmit_multiplier_ = 2)
                : host(host), port(port), name(name), probe_interval(probe_interval_),
                  retransmit_multiplier(retransmit_multiplier_) {}
    };
}

#endif //DIVE_CONFIG_H
