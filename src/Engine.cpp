#include "../include/Engine.h"
#include <stdexcept>

void Engine::register_command(std::shared_ptr<ICommand> cmd, const std::string& name) {
    if (!cmd) throw std::invalid_argument("Engine::register_command: null command");
    if (commands.find(name) != commands.end()) {
        throw std::runtime_error("Engine::register_command: command already registered: " + name);
    }
    commands[name] = std::move(cmd);
}

std::string Engine::execute(const std::string& name, const std::map<std::string, std::any>& args) {
    auto it = commands.find(name);
    if (it == commands.end() || !it->second) {
        throw std::runtime_error("Engine::execute: command not found: " + name);
    }
    return it->second->execute(args);
}