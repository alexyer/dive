#ifndef DIVE_DIVE_H
#define DIVE_DIVE_H

#include "config.h"

using boost::asio::ip::udp;

namespace dive {
    class Dive {
    public:
        Dive(const dive::config&, boost::asio::io_service&);
    private:
        dive::config config_;
        udp::socket socket_;
    };
}


#endif //DIVE_DIVE_H
