set(LIBRARY_IR_UTILS ${CMAKE_PROJECT_NAME}_ir_utils)

file(GLOB src_ir_utils "*.cpp")
add_library(${LIBRARY_IR_UTILS} ${src_ir_utils})
target_include_directories(${LIBRARY_IR_UTILS} PUBLIC
${PROJECT_SOURCE_DIR}/include)