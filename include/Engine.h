#pragma once
#include "ICommand.h"
#include <string>
#include <map>
#include <unordered_map>
#include <memory>


class Engine {
private:
    std::unordered_map<std::string, std::shared_ptr<ICommand>> commands;

public:
    void register_command(std::shared_ptr<ICommand> cmd, const std::string& name);
    std::string execute(
        const std::string& name,
        const std::map<std::string, std::any>& args);
};