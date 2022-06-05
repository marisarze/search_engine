
set(SOURCES src/Converter.cpp)
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)
set(JSON_BuildTests OFF CACHE INTERNAL "")


add_library(Converter ${SOURCES})
target_include_directories (Converter PUBLIC include ${PROJECT_SOURCE_DIR}/SearchServer)
target_link_libraries(Converter PRIVATE nlohmann_json::nlohmann_json SearchServer)