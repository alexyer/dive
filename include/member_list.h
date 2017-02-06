#ifndef DIVE_MEMBER_LIST_H
#define DIVE_MEMBER_LIST_H

#include <unordered_map>
#include "cluster_member.h"

using namespace dive;

namespace dive {
    /***
     * TODO(alexyer): proper doc.
     * Membership management.
     */
    class MemberList {
    public:
        /**
         * Insert new member.
         */
        void insert(const ClusterMember&);

        /**
         *
         * @param name Member name.
         * @return Member
         */
        const ClusterMember& get(std::string name);
    private:
        std::unordered_map<std::string, ClusterMember> members_;
    };
}

#endif //DIVE_MEMBER_LIST_H
