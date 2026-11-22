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

# add_example(<name> <source>)
# Creates the target "<nn>_<name>" (nn = number of the handout folder, for example 03_tour),
# because target names must be unique in the whole project. The program is still called <name>.exe.
function(add_example name source)
  get_filename_component(folder ${CMAKE_CURRENT_SOURCE_DIR} NAME)
  string(REGEX MATCH "^[0-9]+" nn "${folder}")
  add_executable(${nn}_${name} ${source})
  set_target_properties(${nn}_${name} PROPERTIES OUTPUT_NAME ${name})
  # Where programs find their input files and where they write result files.
  target_compile_definitions(${nn}_${name} PRIVATE
    DATA_DIR="${CMAKE_SOURCE_DIR}/data"
    OUTPUT_DIR="${CMAKE_BINARY_DIR}/output")
endfunction()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# Every folder under examples/ that contains a CMakeLists.txt is added automatically.
file(GLOB example_dirs LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/examples
     ${CMAKE_CURRENT_SOURCE_DIR}/examples/*)
foreach(dir ${example_dirs})
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples/${dir}/CMakeLists.txt)
    add_subdirectory(examples/${dir})
  endif()
endforeach()
