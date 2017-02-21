#ifndef DIVE_MEMBER_LIST_H
#define DIVE_MEMBER_LIST_H

#include <unordered_map>
#include <queue>
#include "cluster_member.h"

using namespace dive;
using namespace boost::asio;

namespace dive {
    /***
     * TODO(alexyer): proper doc.
     * Membership management.
     */
    class MemberList {
    public:
        MemberList(io_service& io_service, unsigned int probe_timeout);

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

        /***
         * Get random member from the list and start deadline timer.
         * @return ClusterMember
         */
        const ClusterMember& probe_random();

        /***
         * Get member by name from the list and start deadline timer.
         * @return ClusterMember
         */
        const ClusterMember& probe_member(std::string name);
        bool empty() const;
    private:
        struct ProbeDeadline {
            boost::posix_time::ptime expiration_time;
            std::shared_ptr<ClusterMember> member;

            ProbeDeadline (boost::posix_time::ptime expiration_time, ClusterMember member)
                    : expiration_time(expiration_time), member(std::make_shared<ClusterMember>(member)) {}
        };

        void enqueue_probe_deadline(const ClusterMember& member);
        void handle_probe_deadline();
        void restart_deadline_timer();

        // TODO(alexyer): update docs after implementing failure detector.
        /// Time in milliseconds before member considered dead.
        unsigned int probe_timeout_;

        std::unique_ptr<boost::asio::deadline_timer> probe_deadline_timer_;
        /// List of members waiting for ACK response.
        std::queue<ProbeDeadline> probing_members_;

        std::unordered_map<std::string, ClusterMember> members_;
    };
}

#endif //DIVE_MEMBER_LIST_H
