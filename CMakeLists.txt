cmake_minimum_required(VERSION 3.21)
project(search_project)

set(CMAKE_CXX_STANDARD 14)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_subdirectory(Converter)
add_subdirectory(InvertedIndex)
add_subdirectory(SearchServer)
add_subdirectory(test)
#add_executable(search_project main.cpp test/Converter_test.cpp test/InvertedIndex_test.cpp test/SearchServer_test.cpp test/main.cpp)
add_executable(search_project main.cpp)

target_link_libraries(search_project Converter InvertedIndex SearchServer)




