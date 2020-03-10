cmake_minimum_required(VERSION 3.9)

project(cryptography CXX)

set(BUILD_TESTING OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_TESTING OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(third_party/googletest)
add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(tests)
