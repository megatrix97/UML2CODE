set(BINARY ${CMAKE_PROJECT_NAME}_test)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# get all src files in test directory
file(GLOB test_SRC "*.cpp")

add_executable(${BINARY} ${test_SRC} ${PROJECT_BINARY_DIR}/lexer.cpp ${PROJECT_BINARY_DIR}/parser.cpp)
target_include_directories(${BINARY} PUBLIC 
${PROJECT_SOURCE_DIR}/include
${PROJECT_BINARY_DIR}
)

add_test(NAME ${BINARY} COMMAND ${BINARY})

# link gtest_main
target_link_libraries(${BINARY} PUBLIC uml2code gtest_main)
