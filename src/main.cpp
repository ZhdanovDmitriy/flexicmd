#include <iostream>
#include <memory>
#include "../include/Engine.h"
#include "../include/Wrapper.h"
#include "../include/Subject.h"

int main() {
    Subject subj;
    Engine engine;

    auto wrapper = make_wrapper(&subj, &Subject::f3, {
        std::pair<std::string,std::any>{"arg1",0},
        std::pair<std::string,std::any>{"arg2",0}
    });

    engine.register_command(wrapper, "command1");

    std::string out = engine.execute("command1", { { "arg1", 4 }, { "arg2", 5 } });
    std::cout << out << std::endl;
    return 0;
}
