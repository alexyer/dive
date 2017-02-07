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
         * Get member by name.
         * @param name Member name.
         * @return ClusterMember
         */
        const ClusterMember& get(std::string name);

        /***
         * Get random member from the list.
         * @return ClusterMember
         */
        const ClusterMember& get_random() const;
    private:
        std::unordered_map<std::string, ClusterMember> members_;
    };
}

#endif //DIVE_MEMBER_LIST_H
