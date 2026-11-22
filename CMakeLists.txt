cmake_minimum_required(VERSION 3.21)
project(cpp_handouts LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Every folder under examples/ that contains a CMakeLists.txt is added automatically.
file(GLOB example_dirs LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/examples
     ${CMAKE_CURRENT_SOURCE_DIR}/examples/*)
foreach(dir ${example_dirs})
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples/${dir}/CMakeLists.txt)
    add_subdirectory(examples/${dir})
  endif()
endforeach()
