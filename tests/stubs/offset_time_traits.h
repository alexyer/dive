#ifndef DIVE_OFFSET_TIME_TRAITS_H
#define DIVE_OFFSET_TIME_TRAITS_H

#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/date_time.hpp>
#include <boost/optional.hpp>
#include <boost/thread.hpp>

using namespace boost::asio;
using namespace boost::posix_time;

class offset_time_traits : public deadline_timer::traits_type {
public:
    static time_type now() {
        return *now_;
    }

    static time_type add(time_type t, duration_type d) {
        return deadline_timer::traits_type::add(t, d);
    }

    static duration_type subtract(time_type t, time_type d) {
        return deadline_timer::traits_type::subtract(t, d);
    }

    static void set_now(time_type t) {
        now_ = t;
        boost::this_thread::sleep_for(boost::chrono::milliseconds(2));
    }

    static boost::posix_time::time_duration to_posix_duration(duration_type d) {
        return d < milliseconds(1) ? d : milliseconds(1);
    }

private:
    static boost::optional<time_type> now_;
};

#endif //DIVE_OFFSET_TIME_TRAITS_H
