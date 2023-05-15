set(LIBRARY_FILE_IO ${CMAKE_PROJECT_NAME}_file_io)

file(GLOB src_file_io "*.cpp")
add_library(${LIBRARY_FILE_IO} ${src_file_io})
target_include_directories(${LIBRARY_FILE_IO} PUBLIC 
${PROJECT_SOURCE_DIR}/include)