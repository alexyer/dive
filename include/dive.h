#ifndef DIVE_DIVE_H
#define DIVE_DIVE_H

#include <array>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "config.h"

using boost::asio::ip::udp;

namespace dive {
    class Dive {
    public:
        static const std::string VERSION;
        static const unsigned short PROTOCOL_VERSION;

        const dive::config& getConfig() const;

        /***
         * Create agent instance.
         * @return new Dive instance.
         */
        static Dive agent(const dive::config&, boost::asio::io_service&);
    private:
        Dive(const dive::config&, boost::asio::io_service&);
        void start_receive();
        void handle_receive(const boost::system::error_code&, std::size_t);
        void start_gossiping(boost::asio::io_service&);
        void handle_gossip();
        void restart_gossip_timer();

        dive::config config_;
        udp::socket socket_;
        std::array<char, 128> recv_buffer_;
        udp::endpoint remote_endpoint_;
        std::shared_ptr<boost::asio::deadline_timer> gossip_timer_;
    };
}


#endif //DIVE_DIVE_H
