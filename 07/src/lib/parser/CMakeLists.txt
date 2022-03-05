# CMake file for this library subdirecotry
# This is done by adding add_subdirectory (lib/math) to the main CMake

cmake_minimum_required(VERSION 3.9.1)

# set the location of binary library files 
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


# create library objects as either static or shared libraries
# add_library(parser SHARED parser.cpp)
add_library(parser STATIC parser.cpp)



target_include_directories(parser
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )