cmake_minimum_required(VERSION 3.21)
project(search_engine VERSION "0.0.9.2")

set(CMAKE_CXX_STANDARD 17)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_Declare(
        cli11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11
        GIT_TAG        v2.2.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(cli11)
enable_testing()

add_subdirectory(Converter)
add_subdirectory(InvertedIndex)
add_subdirectory(SearchServer)
add_subdirectory(test)
add_executable(search_engine main.cpp)

target_link_libraries(search_engine Converter InvertedIndex SearchServer CLI11::CLI11)




