cmake_minimum_required(VERSION 3.21)
project(search_project)

set(CMAKE_CXX_STANDARD 14)

#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        # Specify the commit you depend on and update it regularly.
#        URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
#)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#set(gtest_disable_pthreads on)
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)
#enable_testing()


add_subdirectory(Converter)
add_subdirectory(InvertedIndex)
add_executable(search_project main.cpp test/Converter_test.cpp test/InvertedIndex_test.cpp test/SearchServer_test.cpp test/main.cpp)

#target_link_libraries(search_project PRIVATE gtest_main)
#include(GoogleTest)
#gtest_discover_tests(search_project)


