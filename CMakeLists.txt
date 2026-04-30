cmake_minimum_required(VERSION 3.23)

project(algorithm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ALGORITHM_ENABLE_WARNINGS "Enable compiler warnings for algorithm targets" ON)
option(ALGORITHM_ENABLE_CLANG_TIDY "Run clang-tidy during builds when available" OFF)

add_library(algorithm_warnings INTERFACE)

if(ALGORITHM_ENABLE_WARNINGS)
  if(MSVC)
    target_compile_options(algorithm_warnings INTERFACE /W4 /permissive-)
  else()
    target_compile_options(algorithm_warnings INTERFACE -Wall -Wextra -Wpedantic)
  endif()
endif()

if(ALGORITHM_ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_EXE NAMES clang-tidy)
  if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
  else()
    message(WARNING "ALGORITHM_ENABLE_CLANG_TIDY is ON, but clang-tidy was not found.")
  endif()
endif()

file(GLOB algorithm_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

foreach(source_file IN LISTS algorithm_sources)
  get_filename_component(target_name "${source_file}" NAME_WE)

  add_executable("${target_name}" "${source_file}")
  target_link_libraries("${target_name}" PRIVATE algorithm_warnings)
  target_compile_features("${target_name}" PRIVATE cxx_std_17)

  set_target_properties(
    "${target_name}"
    PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )
endforeach()

if(NOT algorithm_sources)
  message(STATUS "No C++ sources found under src/. Add src/<topic>.cpp files to create targets.")
endif()
