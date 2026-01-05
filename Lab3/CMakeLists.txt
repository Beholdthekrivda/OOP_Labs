cmake_minimum_required(VERSION 3.10)
project(MyProject)

add_subdirectory(SBase)

add_executable(Lab3 Lab3.cpp)

target_link_libraries(Lab3 PRIVATE base_lib)