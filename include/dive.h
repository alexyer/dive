#ifndef DIVE_DIVE_H
#define DIVE_DIVE_H

#include <array>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "config.h"
#include "member_list.h"
#include "rpc.h"
#include "queue.h"

using namespace dive;
using boost::asio::ip::udp;

namespace dive {
    class Dive {
    public:
        static const std::string VERSION;
        static const unsigned short PROTOCOL_VERSION;
        static const size_t BUFFER_SIZE;

        const config& getConfig() const;

        /***
         * Create an agent instance.
         * @return new Dive instance.
         */
        static Dive agent(const config&, boost::asio::io_service&);

        /***
         * Create a new agent instance and join existing cluster.
         * @param node_address Address of the known node to join.
         * @return new Dive instance.
         */
        static Dive join(const config&, boost::asio::io_service&, std::string node_address);
        void rpc_receive_cb(std::array<char, 128>, udp::endpoint);
    private:
        Dive(const config&, boost::asio::io_service&);

        void start_probing(boost::asio::io_service&);

        void handle_probe();

        /***
         * Read gossips from the received message and update members list.
         * @param msg Incoming message.
         */
        void read_gossips(const DiveMessage& msg);

        /***
         * Add gossips to message.
         * @param msg Outcoming message.
         */
        void piggyback_gossips(DiveMessage& msg);

        /***
         * Handle received PING message.
         * @param msg Received message.
         * @param remote_endpoint Endpoint of the remote node.
         */
        void handle_ping(const DiveMessage& msg, udp::endpoint remote_endpoint);

        /***
         * Handle received ACK message.
         * @param msg Received message.
         * @param remote_endpoint Endpoint of the remote node.
         */
        void handle_ack(const DiveMessage& msg, udp::endpoint remote_endpoint);

        /***
         * Handle alive gossip.
         * @param gsp Incoming gossip.
         */
        void handle_gossip_alive(const Gossip& gsp);
        void restart_probe_timer();


        config config_;
        RPC rpc_;
        Queue queue_;

        std::unique_ptr<boost::asio::deadline_timer> gossip_timer_;
        std::unique_ptr<boost::asio::deadline_timer> probe_timer_;

        MemberList member_list_;
    };
}


#endif //DIVE_DIVE_H
