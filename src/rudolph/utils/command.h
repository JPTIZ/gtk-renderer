#ifndef RUDOLPH_UTILS_COMMAND_H
#define RUDOLPH_UTILS_COMMAND_H

#include <string>
#include <vector>

namespace command {

struct Command {
    std::string command;
    std::vector<std::string> args;
};

Command parse(const std::string& cmd) {
    auto sep_index = cmd.find(" ");
    auto command = cmd.substr(0, sep_index);
    auto args = std::vector<std::string>{};

    while (sep_index != std::string::npos) {
        sep_index += 1;

        auto next_sep = cmd.find(" ", sep_index);
        args.push_back(cmd.substr(sep_index, next_sep - sep_index));
        sep_index = next_sep;
    }
    return {command, args};
}

std::string prettify(const Command& cmd) {
    auto str = cmd.command + "(\n";
    for (auto arg: cmd.args) {
        str += std::string(cmd.command.size(), ' ') + arg + ",\n";
    }
    return str + ")\n";
}

}

#endif
