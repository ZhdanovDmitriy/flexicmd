#pragma once
#include "ICommand.h"
#include <string>
#include <map>
#include <stdexcept>

class Engine {
private:
    std::map<std::string, ICommand*> commands;

public:
    void register_command(ICommand* cmd, const std::string& name) {
        if (commands.count(name)) {
            throw std::runtime_error("The team is already registered: " + name);
        }
        commands[name] = cmd;
    }

    std::string execute(const std::string& name,
        const std::map<std::string, std::any>& args) {
        auto it = commands.find(name);
        if (it == commands.end()) {
            throw std::runtime_error("The command was not found: " + name);
        }
        return it->second->execute(args);
    }
};
