#include <cassert>
#include <iostream>
#include "../include/Subject.h"
#include "../include/Wrapper.h"
#include "../include/Engine.h"

int main() {
    Subject subj;
    Wrapper<Subject, int, int, int> wrapper(&subj, &Subject::f3, {{"arg1", 0}, {"arg2", 0}});
    Engine engine;
    engine.register_command(&wrapper, "command1");

    std::string result = engine.execute("command1", {{"arg1", 4}, {"arg2", 5}});
    std::cout << "Execution result:" << result << std::endl;
    assert(result == "9");
    std::cout << "The test was passed successfully!" << std::endl;
    return 0;
}
