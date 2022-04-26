#set(TEST_SOURCES Converter_test.cpp InvertedIndex_test.cpp SearchServer_test.cpp)
set(TEST_SOURCES Converter_test.cpp)
set(target_test ${CMAKE_PROJECT_NAME}_test)
message("cmake project name: " ${CMAKE_PROJECT_NAME})
message("current source dir: " ${PROJECT_SOURCE_DIR})
message("current binary dir: " ${PROJECT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_COMPILER C:/msys64/mingw64/bin/g++.exe )
#set(CMAKE_C_COMPILER C:/msys64/mingw64/bin/gcc.exe )

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories($(gtest_SOURCE_DIR)/include $(gtest_SOURCE_DIR))
set(gtest_disable_pthreads on)
enable_testing()

message("test sources: " ${TEST_SOURCES})
add_executable(target_test ${TEST_SOURCES})
add_test(NAME target_test COMMAND target_test)
target_link_libraries(target_test PUBLIC gtest_main Converter InvertedIndex SearchServer)
#
include(GoogleTest)
gtest_discover_tests(target_test)




