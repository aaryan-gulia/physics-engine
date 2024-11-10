cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(physics-core)

set(CMAKE_BUILD_PARALLEL_LEVEL 8)

add_subdirectory(utils)

add_library(${PROJECT_NAME} 
  PhysicsWorld.cpp 
  Vector.cpp 
  Constraint.cpp 
  Entity.cpp 
  BroadPhaseGrid.cpp 
  EntityStore.cpp
  CollisionSolver.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC . utils)
