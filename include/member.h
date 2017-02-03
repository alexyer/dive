#ifndef DIVE_MEMBER_H
#define DIVE_MEMBER_H

#include <sstream>

namespace dive {
    struct Member {
        std::string name;
        std::string host;
        unsigned short port;

        Member(std::string name, std::string host, unsigned short port) : name(name), host(host), port(port) {}
        Member(std::string host, unsigned short port) : host(host), port(port) {
            std::stringstream ss;
            ss << host << ":" << port;
            name = ss.str();
        }
    };
}

#endif //DIVE_MEMBER_H
