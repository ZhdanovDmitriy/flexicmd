#include "../include/Engine.h"
#include <stdexcept>

void Engine::register_command(ICommand* cmd, const std::string& name) {
    if (commands.count(name)) {
        throw std::runtime_error("The command is already registered: " + name);
    }
    commands[name] = cmd;
}

std::string Engine::execute(const std::string& name,
    const std::map<std::string, std::any>& args) {
    auto it = commands.find(name);
    if (it == commands.end() || it->second == nullptr) {
        throw std::runtime_error("The command was not found: " + name);
    }
    return it->second->execute(args);
}
