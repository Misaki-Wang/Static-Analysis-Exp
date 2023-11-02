cmake_minimum_required(VERSION 3.10)

project(Static-Analysis)

# Setting the C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the default compiler to clang, but allow users to override it
if(NOT DEFINED CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER clang++)
endif()

# Add source files here. For now, as an example:
set(SOURCES 
    src/main.cpp
)

# Add header files location
include_directories(${PROJECT_SOURCE_DIR}/include)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# If any external libraries are required, add them after finding them
# Example:
# find_package(SomeLibrary REQUIRED)
# target_link_libraries(${PROJECT_NAME} SomeLibrary)
