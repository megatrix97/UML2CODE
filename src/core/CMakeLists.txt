set(LIBRARY_CORE ${CMAKE_PROJECT_NAME}_core)

file(GLOB core_SRC "*.cpp")
add_library(${LIBRARY_CORE} ${core_SRC})
target_include_directories(${LIBRARY_CORE} PUBLIC 
${PROJECT_SOURCE_DIR}/include)