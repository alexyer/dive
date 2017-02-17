#ifndef DIVE_ERRORS_H
#define DIVE_ERRORS_H

#include <sstream>

namespace dive {
    class DiveError : public std::runtime_error {
    public:
        DiveError(const char* msg) : std::runtime_error(msg) {};
    };

    class UnknownCommandTypeError : public DiveError {
    public:
        UnknownCommandTypeError(unsigned short command) : DiveError("Unknown command") {
            std::stringstream ss;
            ss << DiveError::what() << ": " << std::to_string(command);
            msg = ss.str();
        }
        virtual const char* what() const throw() {
            return msg.c_str();
        }
    private:
        std::string msg;
    };
}

#endif //DIVE_ERRORS_H
