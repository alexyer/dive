#include "../include/dive.h"
#include "../include/dive_message_factory.h"

using namespace dive;

DiveMessage& DiveMessageFactory::get_ping_message(Member* destination) {
    return DiveMessageFactory::get_message(destination, dive::PING);
}

DiveMessage& DiveMessageFactory::get_ack_message(Member* destination) {
    return DiveMessageFactory::get_message(destination, dive::ACK);
}

DiveMessage& DiveMessageFactory::get_message(Member* destination, MessageType msg_type) {
    auto msg = new DiveMessage();
    msg->set_version(Dive::PROTOCOL_VERSION);
    msg->set_message_type(msg_type);
    msg->set_allocated_destination(destination);
    return *msg;
}