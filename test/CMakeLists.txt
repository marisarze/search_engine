set(target_test ${CMAKE_PROJECT_NAME}_test)
set(TEST_PROJECT_NAME search_engine_test)

project(${TEST_PROJECT_NAME})
enable_testing()

if (NOT (TARGET gtest AND TARGET gtest_main))
    message(FATAL_ERROR "gtest and gtest_main targets NOT found")
endif()

add_executable(${TEST_PROJECT_NAME} main.cpp InvertedIndex_test.cpp Converter_test.cpp SearchServer_test.cpp)
target_link_libraries(${TEST_PROJECT_NAME} gtest gtest_main Converter InvertedIndex SearchServer nlohmann_json::nlohmann_json)

add_test(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME})





