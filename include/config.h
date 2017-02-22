#ifndef DIVE_CONFIG_H
#define DIVE_CONFIG_H

#include <string>
#include <sstream>

namespace dive {
    struct config {
        /// The name of this node. Must be unique in the cluster.
        std::string name;

        std::string host;
        unsigned short port;

        /// Interval between probes in milliseconds.
        unsigned int probe_interval;
        /// Expected time for ping answer in milliseconds.
        unsigned int probe_timeout;

        /// Interval between sending gossips in milliseconds.
        unsigned int gossip_interval;
        /// Number of gossips retransmitted in a single gossip message.
        unsigned int gossip_batch_count;

        /// Retransmit multiplier for the number of retransmissions are attempted for messages broadcast
        /// over gossips.
        unsigned int retransmit_multiplier;

        config(std::string host, unsigned short port, unsigned int probe_interval = 200,
               unsigned int probe_timeout = 300,
               unsigned int retransmit_multiplier = 2, unsigned int gossip_interval = 200,
               unsigned int gossip_batch_count = 5)
                : host(host), port(port), probe_interval(probe_interval), probe_timeout(probe_timeout),
                  retransmit_multiplier(retransmit_multiplier), gossip_interval(gossip_interval),
                  gossip_batch_count(gossip_batch_count) {
            std::stringstream ss;
            ss << host << ":" << port;
            name = ss.str();
        };

        config(std::string host, unsigned short port, std::string name, unsigned int probe_interval = 200,
               unsigned int probe_timeout = 300, unsigned int retransmit_multiplier = 2,
               unsigned int gossip_interval = 200,
               unsigned int gossip_batch_count = 5)
                : host{host}, port{port}, name{name}, probe_interval{probe_interval}, probe_timeout{probe_timeout},
                  retransmit_multiplier{retransmit_multiplier}, gossip_interval{gossip_interval},
                  gossip_batch_count{gossip_batch_count} {}
    };
}

#endif //DIVE_CONFIG_H
