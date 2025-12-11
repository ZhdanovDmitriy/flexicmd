#include "../include/Subject.h"
#include <iostream>

int Subject::f3(int arg1, int arg2) {
    std::cout << "Inside Subject::f3: arg1=" << arg1 
              << ", arg2=" << arg2 << "\n";
    return arg1 + arg2;
}
