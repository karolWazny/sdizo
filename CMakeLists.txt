cmake_minimum_required(VERSION 3.17)
project(sdizo_1)

set(CMAKE_CXX_STANDARD 17)


add_executable(sdizo_1 program/Main.cpp
        program/ArrayOperations.cpp
        program/ListOperations.cpp
        program/HeapOperations.cpp
        program/RBTreeOperations.cpp
        program/TextFileReader.cpp
        program/StopWatch.cpp
        program/Operations.cpp)

include_directories(structure_templates_lib program)
add_subdirectory(structure_templates_lib program)

target_link_libraries(sdizo_1 structure_templates_lib)

add_subdirectory(Google_tests)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()