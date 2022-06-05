
set(SOURCES src/SearchServer.cpp)
add_library(SearchServer ${SOURCES})
target_link_libraries(SearchServer InvertedIndex)
target_include_directories (SearchServer PUBLIC include ${PROJECT_SOURCE_DIR}/InvertedIndex)