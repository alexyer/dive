#include "../include/dive.h"
#include "../include/dive_message_factory.h"

using namespace dive;

DiveMessage& DiveMessageFactory::get_ping_message(Member* destination) {
    auto msg = new DiveMessage();
    msg->set_version(Dive::PROTOCOL_VERSION);
    msg->set_message_type(dive::PING);
    msg->set_allocated_destination(destination);
    return *msg;
}