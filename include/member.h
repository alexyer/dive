#ifndef DIVE_MEMBER_H
#define DIVE_MEMBER_H

namespace dive {
    struct Member {
        std::string name;
        std::string host;
        unsigned short port;

        Member(std::string name, std::string host, unsigned short port) : name(name), host(host), port(port) {}
    };
}

#endif //DIVE_MEMBER_H
