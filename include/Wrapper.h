#pragma once
#include "ICommand.h"
#include <vector>
#include <string>
#include <any>
#include <map>
#include <stdexcept>
#include <sstream>
#include <tuple>
#include <utility>
#include <type_traits>

template<typename T, typename R, typename... Args>
class Wrapper : public ICommand {
private:
    T* object;
    R(T::* method)(Args...);
    std::vector<std::string> argNames;
    std::vector<std::any> argDefaults;

public:
    Wrapper(T* obj, R(T::* meth)(Args...),
        std::initializer_list<std::pair<std::string, std::any>> defaults)
        : object(obj), method(meth)
    {
        for (auto& p : defaults) {
            argNames.push_back(p.first);
            argDefaults.push_back(p.second);
        }
        if (argNames.size() != sizeof...(Args)) {
            throw std::invalid_argument("Invalid number of arguments in Wrapper");
        }
    }

    std::string execute(const std::map<std::string, std::any>& args) override {
        std::vector<std::any> finalArgs = argDefaults;
        for (auto& [name, value] : args) {
            auto it = std::find(argNames.begin(), argNames.end(), name);
            if (it == argNames.end()) {
                throw std::runtime_error("Unexpected parameter: " + name);
            }
            size_t index = std::distance(argNames.begin(), it);
            finalArgs[index] = value;
        }
        return callHelper(std::index_sequence_for<Args...>{}, finalArgs);
    }

private:
    template<std::size_t... I>
    std::string callHelper(std::index_sequence<I...>, const std::vector<std::any>& finalArgs) {
        if constexpr (std::is_void_v<R>) {
            (object->*method)(std::any_cast<Args>(finalArgs[I])...);
            return "";
        }
        else {
            R result = (object->*method)(std::any_cast<Args>(finalArgs[I])...);
            std::ostringstream oss;
            oss << result;
            return oss.str();
        }
    }
};
