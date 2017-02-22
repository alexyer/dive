#ifndef DIVE_OFFSET_TIMER_H
#define DIVE_OFFSET_TIMER_H

#include <boost/asio.hpp>
#include <boost/date_time.hpp>

#include "offset_time_traits.h"

using namespace boost::asio;
using namespace boost::posix_time;

typedef basic_deadline_timer<ptime, offset_time_traits> offset_timer;

#endif //DIVE_OFFSET_TIMER_H
