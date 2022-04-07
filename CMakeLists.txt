cmake_minimum_required(VERSION 3.22.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(uml2code VERSION 1.0)

set(CMAKE_CPP_FLAGS, "${CMAKE_CPP_FLAGS} -Wunused-variable")

# set directory variables
set(SRC_FLEX_BISON src/flex_bison)

# flex bison
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(umlParser ${SRC_FLEX_BISON}/tokens.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(umlScanner ${SRC_FLEX_BISON}/tokens.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp COMPILE_FLAGS --header-file)
ADD_FLEX_BISON_DEPENDENCY(umlScanner umlParser)

add_subdirectory(src/core)
add_subdirectory(src/file_io)
add_subdirectory(src/file_io/cpp_emitter)
add_subdirectory(src/utils)
add_subdirectory(test)

# for executable
add_executable(uml2code_exec src/main.cpp ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
target_include_directories(uml2code_exec PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include/
${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(uml2code_exec PUBLIC
${CMAKE_PROJECT_NAME}_core 
${CMAKE_PROJECT_NAME}_file_io 
${CMAKE_PROJECT_NAME}_cpp_emitter
${CMAKE_PROJECT_NAME}_ir_utils
)
