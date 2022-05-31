set(LIBRARY_CPP_EMITTER ${CMAKE_PROJECT_NAME}_cpp_emitter)

file(GLOB src_cpp_emitter "*.cpp")
add_library(${LIBRARY_CPP_EMITTER} ${src_cpp_emitter})
target_include_directories(${LIBRARY_CPP_EMITTER} PUBLIC 
${PROJECT_SOURCE_DIR}/include)