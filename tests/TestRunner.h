#pragma once
#include <vector>
#include <string>
#include <functional>
#include <iostream>

struct TestCase {
    std::string name;
    std::function<bool()> func;
};

#ifdef NDEBUG
#define DEBUG_LOG(x)
#else
#define DEBUG_LOG(x) std::cout << x << std::endl
#endif

/**
 * @brief Runs a list of tests and prints the results
 * @param tests Vector of TestCase
 * @return true if all tests passed
 */
inline bool runTests(const std::vector<TestCase>& tests) {
    int passed = 0;
    std::vector<std::string> failedTests;

    for (size_t i = 0; i < tests.size(); ++i) {
        bool result = false;
        try {
            result = tests[i].func();
        } catch (const std::exception& e) {
            DEBUG_LOG("Exception in test '" << tests[i].name << "': " << e.what());
            result = false;
        }

#ifdef NDEBUG
        if (!result) failedTests.push_back(tests[i].name);
#else
        std::cout << "Test " << (i+1) << ": " << tests[i].name
                  << " - " << (result ? "Success" : "Failure") << std::endl;
#endif
        if (result) ++passed;
    }

#ifdef NDEBUG
    if (!failedTests.empty()) {
        std::cout << "[Failed tests]:\n";
        for (const auto& name : failedTests) std::cout << " - " << name << "\n";
    }
#else
    std::cout << "[" << passed << "/" << tests.size() << "] tests completed successfully." << std::endl;
#endif

    return failedTests.empty();
}
