cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Set project name and version
project(boids VERSION 0.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug 
    CACHE STRING 
      "Choose the type of build (Debug or Release)" 
      FORCE
    )
endif()

# Generate config.h
configure_file(include/config.h.in config.h)

# Find SFML shared libraries
find_package(SFML 2.5 
  COMPONENTS 
    system window graphics network audio REQUIRED
  )

# Compile executable
add_executable(boids main.cpp src/Universe.cpp src/Boids.cpp src/utils.cpp include/Universe.h include/Boids.h )

# Set include directory search paths
target_include_directories(boids 
  PRIVATE
  "${PROJECT_BINARY_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )

# Link executable to required SFML libraries
target_link_libraries(boids sfml-graphics)

# Install target
install(TARGETS boids DESTINATION bin)

