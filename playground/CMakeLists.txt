cmake_minimum_required(VERSION 3.22)

project(plantuml_pg VERSION 1.0)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(plantumlParser ${CMAKE_SOURCE_DIR}/plantuml.y ${CMAKE_CURRENT_BINARY_DIR}/plantuml_parser.cpp COMPILE_FLAGS -Wcounterexamples)
FLEX_TARGET(plantumlScanner ${CMAKE_SOURCE_DIR}/plantuml.l ${CMAKE_CURRENT_BINARY_DIR}/plantuml_lexer.cpp COMPILE_FLAGS --header-file)
ADD_FLEX_BISON_DEPENDENCY(plantumlScanner plantumlParser)

add_executable(plantuml_parser_exec ${CMAKE_SOURCE_DIR}/main.cpp 
${CMAKE_CURRENT_BINARY_DIR}/plantuml_parser.cpp 
${CMAKE_CURRENT_BINARY_DIR}/plantuml_lexer.cpp)

target_include_directories(plantuml_parser_exec PUBLIC 
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_SOURCE_DIR}/../include/)

target_link_directories(plantuml_parser_exec PUBLIC 
${CMAKE_SOURCE_DIR}/../build/src/core
${CMAKE_SOURCE_DIR}/../build/src/utils)
target_link_libraries(plantuml_parser_exec PUBLIC 
uml2code_core
uml2code_ir_utils)