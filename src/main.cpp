#include <iostream>
#include "../include/Engine.h"
#include "../include/Wrapper.h"
#include "../include/Subject.h"

int main() {
    Subject s;
    Engine engine;

    Wrapper<Subject, int, int, int> wrap(
        &s, &Subject::f3,
        { {"a", 1}, {"b", 2} }
    );

    engine.register_command(&wrap, "sum");

    std::string out = engine.execute("sum", { {"a", 10}, {"b", 20} });
    std::cout << "Sum = " << out << std::endl;

    return 0;
}
