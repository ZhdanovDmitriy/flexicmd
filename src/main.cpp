#include <iostream>
#include "../include/Engine.h"
#include "../include/Wrapper.h"
#include "../include/Subject.h"
#include "../tests/TestRunner.h"
#include "../tests/TestCases.h"

int main() {
    Subject subj;
    Engine engine;
    bool allPassed = runTests(createAllTests(subj, engine));
    
    //Пример работы программы
    auto wrapper = make_wrapper(&subj, &Subject::f3, {
        std::pair<std::string,std::any>{"arg1",0},
        std::pair<std::string,std::any>{"arg2",0}
    });

    engine.register_command(wrapper, "command1");
    std::cout<< "command1 registered"<< std::endl;

    std::string out = engine.execute("command1", { { "arg1", 4 }, { "arg2", 5 } });
    std::cout<< "command1 executed"<< std::endl;
    std::cout << "result: " << out << std::endl;

    return 0;
}
