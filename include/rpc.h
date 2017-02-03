#ifndef DIVE_RPC_H
#define DIVE_RPC_H

#include <array>
#include <boost/asio.hpp>
#include "config.h"

using namespace boost::asio;
using ip::udp;
using namespace dive;

namespace dive {
    class RPC {
    public:
        RPC(const config&, io_service&);
        /***
         * Start receiving messages.
         */
        void start_receive();
    private:
        void handle_receive(const boost::system::error_code&, std::size_t);

        udp::socket socket_;
        std::unique_ptr<udp::resolver> resolver_;
        std::array<char, 128> recv_buffer_;
        udp::endpoint remote_endpoint_;
    };
}

#endif //DIVE_RPC_H
