#ifndef DIVE_MEMBER_FACTORY_H
#define DIVE_MEMBER_FACTORY_H

#include <memory>
#include "lib/proto/message.pb.h"

namespace dive {
    class MemberFactory {
    public:
        static Member& get_member(unsigned long ip, unsigned int port);
        static Member& get_member(std::string host, unsigned int port);
    };
}

#endif //DIVE_MEMBER_FACTORY_H