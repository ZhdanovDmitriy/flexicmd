enable_testing()

add_executable(CommandEngineTest test_commands.cpp)
target_link_libraries(CommandEngineTest PRIVATE CommandEngineLib)

target_include_directories(CommandEngineTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_test(NAME RunCommandEngineTest COMMAND CommandEngineTest)
