cmake_minimum_required(VERSION 3.22.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(UML2CODE VERSION 1.0)

# set variables for directories
set(SRC_CORE_DIR src/core)
set(SRC_FILEIO_DIR src/file_io)
set(SRC_FLEX_BISON src/flex_bison)
set(INC_CORE_DIR include/core)
set(INC_FILEIO_DIR include/file_io)

file(GLOB all_SRC "${SRC_CORE_DIR}/*.cpp" "${SRC_FILEIO_DIR}/*.cpp" "${SRC_FILEIO_DIR}/cpp_emitter/*.cpp")

# flex bison
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(umlParser ${SRC_FLEX_BISON}/tokens.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(umlScanner ${SRC_FLEX_BISON}/tokens.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(umlScanner umlParser)

add_executable(uml2code src/main.cpp ${all_SRC} ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

target_include_directories(uml2code PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include/core
${CMAKE_CURRENT_SOURCE_DIR}/include/file_io
${CMAKE_CURRENT_SOURCE_DIR}/include/file_io/cpp_emitter
${CMAKE_CURRENT_BINARY_DIR})       