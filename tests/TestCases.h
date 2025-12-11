#pragma once
#include "TestRunner.h"
#include "../include/Subject.h"
#include "../include/Wrapper.h"
#include "../include/Engine.h"

inline std::vector<TestCase> createAllTests(Subject& subj, Engine& engine) {
    std::vector<TestCase> tests;

    tests.push_back({"f3: 2 args, permutation", [&](){
        auto w3 = make_wrapper(&subj, &Subject::f3, {{"arg1",0},{"arg2",0}});
        engine.register_command(w3, "cmd3");
        return engine.execute("cmd3", {{"arg2",5},{"arg1",4}}) == "9";
    }});

    tests.push_back({"f1: 3 args, permutation", [&](){
        auto w1 = make_wrapper(&subj, &Subject::f1, {{"arg1",0},{"arg2",0},{"arg3",0}});
        engine.register_command(w1, "cmd1");
        return engine.execute("cmd1", {{"arg3",10},{"arg2",5},{"arg1",4}}) == "19";
    }});

    tests.push_back({"f2: 2 args, partial redefinition", [&](){
        auto w2 = make_wrapper(&subj, &Subject::f2, {{"arg1",1},{"arg2",2}});
        engine.register_command(w2, "cmd2");
        return engine.execute("cmd2", {{"arg2",5}}) == "5";
    }});

    tests.push_back({"f4: 3 args, different types", [&](){
        auto w4 = make_wrapper(&subj, &Subject::f4, {{"s",std::string("Hi")},{"n",2},{"d",3.5}});
        engine.register_command(w4, "cmd4");
        return engine.execute("cmd4", {{"d",4.5},{"n",3},{"s",std::string("Hello")}}) == "Hello 7";
    }});

    return tests;
}