cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+


add_executable(utils_unit_tests utils_unit_tests.cpp)
add_test(NAME utils_unit_tests COMMAND utils_unit_tests)
