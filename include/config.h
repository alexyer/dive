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

        /// Interval between sending gossips in milliseconds.
        unsigned int gossip_interval;

        /// Retransmit multiplier for the number of retransmissions are attempted for messages broadcast
        /// over gossips.
        unsigned int retransmit_multiplier;

        config(std::string host, unsigned short port, unsigned int probe_interval = 200,
               unsigned int retransmit_multiplier = 2, unsigned int gossip_interval = 200)
                : host(host), port(port), probe_interval(probe_interval),
                  retransmit_multiplier(retransmit_multiplier), gossip_interval(gossip_interval) {
            std::stringstream ss;
            ss << host << ":" << port;
            name = ss.str();
        };

        config(std::string host, unsigned short port, std::string name, unsigned int probe_interval = 200,
               unsigned int retransmit_multiplier = 2)
                : host{host}, port{port}, name{name}, probe_interval{probe_interval},
                  retransmit_multiplier{retransmit_multiplier}, gossip_interval{gossip_interval} {}
    };
}

#endif //DIVE_CONFIG_H
