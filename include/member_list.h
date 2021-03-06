#ifndef DIVE_MEMBER_LIST_H
#define DIVE_MEMBER_LIST_H

#include <deque>
#include <unordered_map>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>
#include <boost/date_time.hpp>

#include "cluster_member.h"
#include "errors.h"

using namespace dive;
using namespace boost::asio;
using namespace boost::posix_time;

namespace dive {
    /***
     * TODO(alexyer): proper doc.
     * Membership management.
     */
    template<typename TimerType>
    class BasicMemberList {
    public:
        BasicMemberList(io_service& io_service, unsigned int probe_timeout)
                : probe_timeout_{probe_timeout}, timer_cancelled_{false} {
            probe_deadline_timer_ = std::make_unique<TimerType>(io_service);
        }

        /**
         * Check if member exists.
         * @param name Member name.
         * @return True if member exists otherwise false.
         */
        bool exists(std::string name) const {
            return members_.find(name) != members_.end();
        }

        /**
         * Insert new member.
         */
        void insert(const ClusterMember& new_member) {
            if (members_.find(new_member.name) != members_.end()) {
                throw MemberListError("Member already exists.");
            }

            members_.insert({new_member.name, new_member});
        }

        /**
         * Get member by name.
         * @param name Member name.
         * @return ClusterMember
         */
        const ClusterMember& get(std::string name) {
            return members_.at(name);
        }

        /***
         * Get random member from the list.
         * @return ClusterMember
         */
        const ClusterMember& get_random() const {
            auto pair = std::next(std::begin(members_), std::rand() % members_.size());
            return pair->second;
        }

        /***
         * Get random member from the list and start deadline timer.
         * @return ClusterMember
         */
        const ClusterMember& probe_random() {
            auto member = get_random();
            enqueue_probe_deadline(member);
            return get(member.name);
        }

        /***
         * Get member by name from the list and start deadline timer.
         * @return ClusterMember
         */
        const ClusterMember& probe_member(std::string name) {
            auto member = get(name);
            enqueue_probe_deadline(member);
            return get(member.name);
        }

        /***
         * Consider member alive and remove from deadline queue.
         * @param member
         * @return Return true if the member is new. Otherwise false.
         */
        bool consider_alive(ClusterMember& member) {
            auto new_member = false;

            timer_cancelled_ = true;
            probe_deadline_timer_->cancel();

            if (members_.find(member.name) == members_.end()) {
                new_member = true;
                BOOST_LOG_TRIVIAL(info) << "New member: " << member.name;
                members_.insert({member.name, member});
            }

            remove_member_from_probing(member.name);

            if (!probing_members_.empty()) {
                restart_deadline_timer();
            }

            return new_member;
        }

        bool empty() const {
            return members_.empty();
        }

        size_t size() const {
            return members_.size();
        }

    private:
        struct ProbeDeadline {
            boost::posix_time::ptime expiration_time;
            std::shared_ptr<ClusterMember> member;

            ProbeDeadline(boost::posix_time::ptime expiration_time, ClusterMember member)
                    : expiration_time(expiration_time), member(std::make_shared<ClusterMember>(member)) {}
        };

        // TODO(alexyer): update docs after implementing failure detector.
        /// Time in milliseconds before member considered dead.
        unsigned int probe_timeout_;
        bool timer_cancelled_;

        std::unique_ptr<TimerType> probe_deadline_timer_;
        /// List of members waiting for ACK response.
        std::deque<ProbeDeadline> probing_members_;

        std::unordered_map<std::string, ClusterMember> members_;

        void enqueue_probe_deadline(const ClusterMember& member) {
            timer_cancelled_ = false;
            auto timer_expired = probe_deadline_timer_->expires_at() < microsec_clock::local_time();
            auto restart_timer = probing_members_.empty() || timer_expired;

            probing_members_.emplace_back(
                    microsec_clock::local_time() + milliseconds(probe_timeout_),
                    member);

            if (restart_timer) {
                restart_deadline_timer();
            }
        }

        void handle_probe_deadline() {
            // TODO(alexyer): Ugly. Encapsulate cancellation logic into timer wrapper.
            if (probing_members_.empty() || timer_cancelled_) {
                return;
            }

            auto member_it = members_.find(probing_members_.front().member->name);

            if (member_it != members_.end()) {
                auto name = member_it->first;
                members_.erase(member_it);
                BOOST_LOG_TRIVIAL(debug) << name << " is dead";
            }

            probing_members_.pop_front();

            if (!probing_members_.empty()) {
                restart_deadline_timer();
            }
        }

        void restart_deadline_timer() {
            probe_deadline_timer_->expires_at(probing_members_.front().expiration_time);
            probe_deadline_timer_->async_wait(boost::bind(&BasicMemberList::handle_probe_deadline, this));
        }

        void remove_member_from_probing(std::string name) {
            probing_members_.erase(
                    std::remove_if(probing_members_.begin(), probing_members_.end(), [&](ProbeDeadline probe_deadline) {
                        return probe_deadline.member->name == name;
                    }), probing_members_.end());
        }
    };

    typedef BasicMemberList<deadline_timer> MemberList;
}

#endif //DIVE_MEMBER_LIST_H
