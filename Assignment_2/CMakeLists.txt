cmake_minimum_required(VERSION 3.16)
project(assignment_2)

find_package( Threads )

set(CMAKE_CXX_STANDARD 20)
include_directories(${PROJECT_SOURCE_DIR})  # Allows absolute paths: #include <util/bar/bar.h>
enable_testing()

add_subdirectory(lib)
add_subdirectory(test)  # enable_testing() used there

add_executable(assignment_2 main.cpp)
target_link_libraries(assignment_2 sets)
target_link_libraries(assignment_2 ${CMAKE_THREAD_LIBS_INIT} )