#pragma once
#include <string>
#include <map>
#include <any>

class ICommand {
public:
    virtual ~ICommand() = default;
virtual std::string execute(const std::map<std::string, std::any>& args) = 0;
};
