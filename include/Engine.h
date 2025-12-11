#pragma once
#include "ICommand.h"
#include <string>
#include <map>

class Engine {
private:
    std::map<std::string, ICommand*> commands;

public:
    void register_command(ICommand* cmd, const std::string& name);
    std::string execute(
        const std::string& name,
        const std::map<std::string, std::any>& args);
};