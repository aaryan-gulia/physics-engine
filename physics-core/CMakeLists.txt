cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(physics-core)

# Dependencies
set(EIGEN_VERSION 3.4.0)
find_package(eigen ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT eigen_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    eigen
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz)
  FetchContent_GetProperties(eigen)
  if (NOT eigen_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(eigen)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${eigen_SOURCE_DIR} ${eigen_BINARY_DIR})
  endif()
endif()

add_library(${PROJECT_NAME} PhysicsWorld.cpp Particle.cpp Vector.cpp 
Constraint.cpp Entity.cpp BroadPhaseGrid.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME} eigen)
