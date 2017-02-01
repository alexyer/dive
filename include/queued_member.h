#ifndef DIVE_QUEUED_MEMBER_H
#define DIVE_QUEUED_MEMBER_H

#include "member.h"

namespace dive {
    struct QueuedMember {
        std::shared_ptr<Member> member;
        unsigned int retransmitted_count;

        explicit QueuedMember(std::shared_ptr<Member> member) : member(member), retransmitted_count(0) {}
    };
}

#endif //DIVE_QUEUED_MEMBER_H
