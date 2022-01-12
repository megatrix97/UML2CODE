cmake_minimum_required(VERSION 3.22.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(UML2CODE VERSION 1.0)

# set variables for directories
set(SRC_FILEIO_DIR src/file_io)
set(SRC_FLEX_BISON src/flex_bison)
set(INC_FILEIO_DIR include/file_io)

# get all src files in listed dirs
file(GLOB all_SRC "${SRC_FILEIO_DIR}/*.cpp" "${SRC_FILEIO_DIR}/cpp_emitter/*.cpp")

# flex bison
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(umlParser ${SRC_FLEX_BISON}/tokens.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(umlScanner ${SRC_FLEX_BISON}/tokens.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp COMPILE_FLAGS --header-file)
ADD_FLEX_BISON_DEPENDENCY(umlScanner umlParser)

add_subdirectory(src/core)
add_subdirectory(test)

# for executable
add_executable(uml2code_exec src/main.cpp ${all_SRC} ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
target_include_directories(uml2code_exec PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include/
${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(uml2code_exec ${CMAKE_PROJECT_NAME}_core)

# for library -- needed for tests
add_library(uml2code ${all_SRC})
target_include_directories(uml2code PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include/
)
target_link_libraries(uml2code ${CMAKE_PROJECT_NAME}_core)
