#ifndef DIVE_UTILS_H
#define DIVE_UTILS_H

#include <sstream>
#include <boost/asio.hpp>

namespace dive {
    namespace utils {
        inline unsigned long ip_str2ulong(std::string ip) {
            return boost::asio::ip::address_v4::from_string(ip).to_ulong();
        }

        inline std::string remote_endpoint2str(boost::asio::ip::udp::endpoint remote_endpoint) {
            std::stringstream ss;
            ss << remote_endpoint.address().to_string() << ":" << std::to_string(remote_endpoint.port());
            return ss.str();
        }
    }
}

#endif //DIVE_UTILS_H
