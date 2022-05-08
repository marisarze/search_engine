set(target_test ${CMAKE_PROJECT_NAME}_test)
message("cmake project name: " ${CMAKE_PROJECT_NAME})
message("current source dir: " ${PROJECT_SOURCE_DIR})
message("current binary dir: " ${PROJECT_BINARY_DIR})

set(TEST_PROJECT_NAME search_engine_test)

project(${TEST_PROJECT_NAME})
enable_testing()

if (NOT (TARGET gtest AND TARGET gtest_main))
    message(FATAL_ERROR "gtest and gtest_main targets NOT found")
endif()

add_executable(${TEST_PROJECT_NAME} main.cpp InvertedIndex_test.cpp)
target_link_libraries(${TEST_PROJECT_NAME} gtest gtest_main Converter InvertedIndex SearchServer)

add_test(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME})





