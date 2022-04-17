file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
add_library(SearchServer static ${SOURCES})
target_include_directories (SearchServer PUBLIC include)