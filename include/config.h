#ifndef DIVE_CONFIG_H
#define DIVE_CONFIG_H

#include <string>

namespace dive {
    struct config {
        std::string host;
        unsigned short port;

        config(std::string host, unsigned short port) : host(host), port(port) {};
    };
}

#endif //DIVE_CONFIG_H
