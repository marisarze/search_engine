cmake_minimum_required(VERSION 3.21)
project(search_project)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_COMPILER C:/msys64/mingw64/bin/g++.exe )
#set(CMAKE_C_COMPILER C:/msys64/mingw64/bin/gcc.exe )

#include_directories(Converter InvertedIndex SearchServer)
add_subdirectory(Converter)
add_subdirectory(InvertedIndex)
add_subdirectory(SearchServer)
add_subdirectory(test)
#add_executable(search_project main.cpp test/Converter_test.cpp test/InvertedIndex_test.cpp test/SearchServer_test.cpp test/main.cpp)
add_executable(search_project main.cpp)

target_link_libraries(search_project Converter InvertedIndex SearchServer)




