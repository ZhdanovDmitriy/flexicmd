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
#include <algorithm>
#include <functional>

template<typename T, typename R, typename... Args>
class Wrapper : public ICommand {
private:
    T* object;
    std::function<R(Args...)> invoker;
    std::vector<std::string> argNames;
    std::vector<std::any> argDefaults;

public:
    Wrapper(T* obj, R(T::*meth)(Args...),std::initializer_list<std::pair<std::string, std::any>> defaults): object(obj)
    {
        for (auto& p : defaults) {
            argNames.push_back(p.first);
            argDefaults.push_back(p.second);
        }

        constexpr size_t expectedCount = sizeof...(Args);
        if (argNames.size() != expectedCount) {
            throw std::invalid_argument("Wrapper: invalid number of arguments. Expected" 
                + std::to_string(expectedCount) + ", got " 
                + std::to_string(argNames.size()));
        }

        if constexpr (std::is_void_v<R>) {
            invoker = [obj, meth](Args... a) -> R {
                (obj->*meth)(std::forward<Args>(a)...);
            };
        } else {
            invoker = [obj, meth](Args... a) -> R {
                return (obj->*meth)(std::forward<Args>(a)...);
            };
        }
    }

    std::string execute(const std::map<std::string, std::any>& args) override {
        std::vector<std::any> finalArgs = argDefaults;

        for (const auto& [name, value] : args) {
            auto it = std::find(argNames.begin(), argNames.end(), name);
            if (it == argNames.end()) {
                throw std::runtime_error("Wrapper: unexpected parameter: " + name);
            }
            size_t index = static_cast<size_t>(std::distance(argNames.begin(), it));
            finalArgs[index] = value;
        }

        return callHelper(std::index_sequence_for<Args...>{}, finalArgs);
    }

private:
    template<std::size_t... I>
    std::string callHelper(std::index_sequence<I...>, const std::vector<std::any>& finalArgs) {
        try {
            if constexpr (std::is_void_v<R>) {
                invoker(std::any_cast<Args>(finalArgs[I])...);
                return std::string();
            } else {
                R result = invoker(std::any_cast<Args>(finalArgs[I])...);
                std::ostringstream oss;
                oss << result;
                return oss.str();
            }
        }
        catch (const std::bad_any_cast& e) {
            throw std::runtime_error(std::string("Wrapper: bad_any_cast — wrong argument type: ") + e.what());
        }
    }
};

template<typename T, typename R, typename... Args>
std::shared_ptr<Wrapper<T,R,Args...>> make_wrapper(
    T* obj,
    R(T::*meth)(Args...),
    std::initializer_list<std::pair<std::string,std::any>> defaults
) {
    return std::make_shared<Wrapper<T,R,Args...>>(obj, meth, defaults);
}