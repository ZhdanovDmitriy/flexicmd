#include "../include/Subject.h"

int Subject::f1(int arg1, int arg2, int arg3) {
    return arg1 + arg2 + arg3;
}

int Subject::f2(int arg1, int arg2) {
    return arg1 * arg2;
}

int Subject::f3(int arg1, int arg2) {
    return arg1 + arg2;
}

std::string Subject::f4(std::string s, int n, double d) {
    return s + " " + std::to_string(n + static_cast<int>(d));
}