#ifndef DIVE_UTILS_H
#define DIVE_UTILS_H

#include <sstream>
#include <boost/asio.hpp>
#include <boost/date_time.hpp>

using namespace boost::posix_time;

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

        inline std::string ptime2str(ptime t) {
            boost::gregorian::date_facet *df = new boost::gregorian::date_facet("%Y%m%d_%H%M%S");

            std::stringstream ss;
            ss.imbue(std::locale(ss.getloc(), df));

            ss << t;

            return ss.str();
        }
    }
}

#endif //DIVE_UTILS_H
