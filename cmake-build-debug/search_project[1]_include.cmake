if(EXISTS "C:/Users/marisarze/Documents/Clion_proj/search_engine/cmake-build-debug/search_project[1]_tests.cmake")
  include("C:/Users/marisarze/Documents/Clion_proj/search_engine/cmake-build-debug/search_project[1]_tests.cmake")
else()
  add_test(search_project_NOT_BUILT search_project_NOT_BUILT)
endif()
