#ifndef DIVE_DIVE_MESSAGE_FACTORY_H
#define DIVE_DIVE_MESSAGE_FACTORY_H

#include <lib/proto/message.pb.h>

using namespace dive;

namespace dive {
    class DiveMessageFactory {
    public:
        static DiveMessage& get_ping_message(Member*);
    };
}

#endif //DIVE_DIVE_MESSAGE_FACTORY_H
