set(target_test ${CMAKE_PROJECT_NAME}_test)
set(TEST_PROJECT_NAME search_engine_test)

project(${TEST_PROJECT_NAME})
enable_testing()

if (NOT (TARGET gtest AND TARGET gtest_main))
    message(FATAL_ERROR "gtest and gtest_main targets NOT found")
endif()

add_executable(${TEST_PROJECT_NAME} main.cpp InvertedIndex_test.cpp Converter_test.cpp SearchServer_test.cpp)
add_executable(Converter_test main.cpp Converter_test.cpp)
add_executable(InvertedIndex_test main.cpp InvertedIndex_test.cpp)
add_executable(SearchServer_test main.cpp SearchServer_test.cpp)

target_link_libraries(${TEST_PROJECT_NAME} gtest gtest_main Converter InvertedIndex SearchServer nlohmann_json::nlohmann_json)
target_link_libraries(Converter_test gtest gtest_main Converter SearchServer nlohmann_json::nlohmann_json)
target_link_libraries(InvertedIndex_test gtest gtest_main Converter InvertedIndex)
target_link_libraries(SearchServer_test gtest gtest_main InvertedIndex SearchServer)

add_test(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME})





