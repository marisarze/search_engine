set(SOURCES src/InvertedIndex.cpp)
add_library(InvertedIndex ${SOURCES})
target_include_directories (InvertedIndex PUBLIC include)