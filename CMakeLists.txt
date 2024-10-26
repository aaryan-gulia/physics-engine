cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(example)

# Generate compile_commands.json
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(physics-core)
add_subdirectory(example)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        example/compile_commands.json
        physics-core/compile_commands.json
)
