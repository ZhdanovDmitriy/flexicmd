#pragma once
#include "TestRunner.h"
#include "../include/Subject.h"
#include "../include/Wrapper.h"
#include "../include/Engine.h"

inline std::vector<TestCase> createAllTests(Subject& subj, Engine& engine) {
    std::vector<TestCase> tests;

    tests.push_back({"f1: permutation", [&](){
        auto w = make_wrapper(&subj, &Subject::f1, {{"arg1",0},{"arg2",0},{"arg3",0}});
        engine.register_command(w, "cmd_f1_1");
        return engine.execute("cmd_f1_1", {{"arg3",10},{"arg2",5},{"arg1",4}}) == "19";
    }});

    tests.push_back({"f1: partial override", [&](){
        auto w = make_wrapper(&subj, &Subject::f1, {{"arg1",1},{"arg2",2},{"arg3",3}});
        engine.register_command(w, "cmd_f1_2");
        return engine.execute("cmd_f1_2", {{"arg2",5}}) == "9";
    }});

    tests.push_back({"f1: edge values", [&](){
        auto w = make_wrapper(&subj, &Subject::f1, {{"arg1",-1},{"arg2",-2},{"arg3",-3}});
        engine.register_command(w, "cmd_f1_3");
        return engine.execute("cmd_f1_3", {{"arg1",10},{"arg2",0},{"arg3",5}}) == "15";
    }});

    tests.push_back({"f2: permutation", [&](){
        auto w = make_wrapper(&subj, &Subject::f2, {{"arg1",0},{"arg2",0}});
        engine.register_command(w, "cmd_f2_1");
        return engine.execute("cmd_f2_1", {{"arg2",7},{"arg1",3}}) == "21";
    }});

    tests.push_back({"f2: partial override", [&](){
        auto w = make_wrapper(&subj, &Subject::f2, {{"arg1",1},{"arg2",2}});
        engine.register_command(w, "cmd_f2_2");
        return engine.execute("cmd_f2_2", {{"arg2",5}}) == "5";
    }});

    tests.push_back({"f2: edge values", [&](){
        auto w = make_wrapper(&subj, &Subject::f2, {{"arg1",-10},{"arg2",20}});
        engine.register_command(w, "cmd_f2_3");
        return engine.execute("cmd_f2_3", {{"arg1",-5},{"arg2",0}}) == "0";
    }});

    tests.push_back({"f3: permutation", [&](){
        auto w = make_wrapper(&subj, &Subject::f3, {{"arg1",0},{"arg2",0}});
        engine.register_command(w, "cmd_f3_1");
        return engine.execute("cmd_f3_1", {{"arg2",5},{"arg1",4}}) == "9";
    }});

    tests.push_back({"f3: partial override", [&](){
        auto w = make_wrapper(&subj, &Subject::f3, {{"arg1",1},{"arg2",2}});
        engine.register_command(w, "cmd_f3_2");
        return engine.execute("cmd_f3_2", {{"arg2",10}}) == "11";
    }});

    tests.push_back({"f3: edge values", [&](){
        auto w = make_wrapper(&subj, &Subject::f3, {{"arg1",-1},{"arg2",100}});
        engine.register_command(w, "cmd_f3_3");
        return engine.execute("cmd_f3_3", {{"arg1",-5},{"arg2",50}}) == "45";
    }});

    tests.push_back({"f4: permutation", [&](){
        auto w = make_wrapper(&subj, &Subject::f4, {{"s",std::string("Test")},{"n",2},{"d",3.5}});
        engine.register_command(w, "cmd_f4_1");
        return engine.execute("cmd_f4_1", {{"d",4.5},{"n",3},{"s", std::string("Test")}}) == "Test 7";
    }});

    tests.push_back({"f4: partial override", [&](){
        auto w = make_wrapper(&subj, &Subject::f4, {{"s",std::string("Test")},{"n",1},{"d",2.5}});
        engine.register_command(w, "cmd_f4_2");
        return engine.execute("cmd_f4_2", {{"n",5}}) == "Test 7";
    }});

    tests.push_back({"f4: edge values", [&](){
        auto w = make_wrapper(&subj, &Subject::f4, {{"s", std::string("Edge")},{"n",-2},{"d",3.0}});
        engine.register_command(w, "cmd_f4_3");
        return engine.execute("cmd_f4_3", {{"n",0},{"d",0.0}}) == "Edge 0";
    }});

    return tests;
}
