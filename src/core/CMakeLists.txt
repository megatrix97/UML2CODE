set(BINARY ${CMAKE_PROJECT_NAME}_core)

file(GLOB core_SRC "*.cpp")
add_library(${BINARY} ${core_SRC})
target_include_directories(${BINARY} PUBLIC 
${PROJECT_SOURCE_DIR}/include)