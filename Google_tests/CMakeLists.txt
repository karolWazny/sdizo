project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(Google_Tests_run
        ListTests.cpp
        RedBlackTreeTests.cpp
        NodeTest.cpp
        FinderTest.cpp
        PutterTest.cpp
        NodeReplacerTest.cpp
        LiberatorTest.cpp
        RBNodeTest.cpp
        NodeRotatorTest.cpp
        PutRestorerTest.cpp
        DeleteRestorerTest.cpp
        AVLTest.cpp
        ArrayTests.cpp)

# linking Google_Tests_run with structure_templates_lib which will be tested
target_link_libraries(Google_Tests_run structure_templates_lib)

target_link_libraries(Google_Tests_run gtest gtest_main)