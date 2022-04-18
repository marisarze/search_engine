set(SOURCES Converter_test.cpp InvertedIndex_test.cpp SearchServer_test.cpp)
set(BINARY ${CMAKE_PROJECT_NAME}_tst)
add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)