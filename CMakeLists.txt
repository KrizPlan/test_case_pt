cmake_minimum_required(VERSION 3.0.0)
set(CXX_STANDARD_REQUIRED 14)
project(test_case_pt)

find_package( Threads )
add_executable(test_case_pt main.cpp)
target_link_libraries( test_case_pt ${CMAKE_THREAD_LIBS_INIT} )

add_library(event_lib Event.cpp)
target_link_libraries(test_case_pt event_lib)