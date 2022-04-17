file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
add_library(InvertedIndex static ${SOURCES})
target_include_directories (InvertedIndex PUBLIC include)