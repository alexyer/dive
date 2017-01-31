#ifndef DIVE_MEMBER_LIST_H
#define DIVE_MEMBER_LIST_H

#include "member.h"

namespace dive {
    /***
     * TODO(alexyer): proper doc.
     * Membership management.
     */
    class MemberList {
    private:
        std::vector<dive::Member> members_;
    };
}

#endif //DIVE_MEMBER_LIST_H
