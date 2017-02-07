#ifndef DIVE_RPC_H
#define DIVE_RPC_H

#include <array>
#include <ostream>
#include <queue>
#include <boost/asio.hpp>
#include "config.h"
#include "lib/proto/message.pb.h"

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

        /***
         * Start sending messages.
         * Sending handler checks sending queue periodically and send messages if available.
         * @param ms Sending queue probing time
         */
        void start_send(io_service&);

        /***
         * Enqueue message for sending.
         * @param stream
         */
        void enqueue_send_message(DiveMessage stream);
    private:
        void handle_receive(const boost::system::error_code&, std::size_t);
        void handle_send();
        void send_messages();
        void async_send_cb(const std::shared_ptr<std::string>, const boost::system::error_code &, std::size_t);

        unsigned int send_probe_period_;
        udp::socket socket_;
        std::array<char, 128> recv_buffer_;
        udp::endpoint remote_endpoint_;
        std::queue<DiveMessage> send_queue_;
        std::unique_ptr<deadline_timer> send_queue_timer_;
    };
}

#endif //DIVE_RPC_H
