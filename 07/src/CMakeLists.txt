cmake_minimum_required(VERSION 3.10.2)

# The project name to be used manywheres in the this file
# e.g. ${PROJECT_NAME}
project(my_VMTranslator)





# To see all the warnings from CMake
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")




# set the location of binary/executable program and library files 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)








#### SUB-DIRECTORIES ########
# add lib library as sub_directory
add_subdirectory(lib)



# produce binary/executable file of the project
add_executable(${PROJECT_NAME} main.cpp)




# link the compiled library object to main program file
target_link_libraries(${PROJECT_NAME} 
                        codewriter
                        parser
                        utils)


# include the external/glfw/includes in include_directory of main program
# this is the location header files of glfw project needed for reference
target_include_directories( ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

  
