cmake_minimum_required(VERSION 3.9)

project(tests LANGUAGES CXX)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(tests main.cpp tst_examplecase.h)

target_link_libraries(tests
        gtest
        gmock
        lib
        Qt5::Core
)
target_compile_features(tests PRIVATE cxx_std_17)
target_compile_features(tests PRIVATE cxx_std_17)
