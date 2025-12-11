cmake_minimum_required(VERSION 3.10)
project(CommandEngine)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(CommandEngineLib
    src/Engine.cpp
    src/Subject.cpp
)
target_include_directories(CommandEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)

add_executable(Flexicmd src/main.cpp)
target_link_libraries(Flexicmd PRIVATE CommandEngineLib)
target_include_directories(Flexicmd PRIVATE include)
