cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(physics-core)


add_library(${PROJECT_NAME} PhysicsWorld.cpp Particle.cpp Vector.cpp 
Constraint.cpp Entity.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC .)
