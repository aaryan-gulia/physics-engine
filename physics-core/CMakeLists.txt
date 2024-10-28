cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(physics-core)

# Generate compile_commands.json
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} System.cpp Particle.cpp Vector.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC .)
