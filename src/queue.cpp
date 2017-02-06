#include <cmath>
#include "../include/queue.h"

using namespace dive;

Queue::Queue(unsigned int retransmit_limit) : retransmit_multiplier_(retransmit_limit) {}

unsigned int Queue::retransmit_limit(unsigned int number_of_nodes) {
    return retransmit_multiplier_ * (unsigned int)std::ceil(std::log10(number_of_nodes + 1));
}
