#ifndef RUDOLPH_UTILS_COMMAND_H
#define RUDOLPH_UTILS_COMMAND_H

#include <string>
#include <vector>

namespace command {

struct Command {
    std::string command;
    std::vector<std::string> args;
};

Command parse(const std::string& cmd);

std::string prettify(const Command& cmd);

}

#endif
