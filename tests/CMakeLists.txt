
cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(test)
include(CTest)

# Generate compile_commands.json
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Our Test
add_executable(${PROJECT_NAME} tests.cpp)
add_test(NAME test COMMAND test)

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib physics-core)
