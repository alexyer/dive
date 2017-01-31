#ifndef DIVE_DIVE_H
#define DIVE_DIVE_H

#include <array>
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

        dive::config config_;
        udp::socket socket_;
        std::array<char, 128> recv_buffer_;
        udp::endpoint remote_endpoint_;
    };
}


#endif //DIVE_DIVE_H
