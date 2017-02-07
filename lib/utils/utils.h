#ifndef DIVE_UTILS_H
#define DIVE_UTILS_H

#include <boost/asio.hpp>

namespace dive {
    namespace utils {
        inline unsigned long ip_str2ulong(std::string ip) {
            return boost::asio::ip::address_v4::from_string(ip).to_ulong();
        }
    }
}

#endif //DIVE_UTILS_H
