cmake_minimum_required(VERSION 3.9)

project(lib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(lib SHARED
  lib.cpp
  caesar_cipher.cc
)

add_custom_target(lib_headers SOURCES
    include/lib_global.h
    include/caesar_cipher.h
    include/caesar_cipher_interface.h)

target_link_libraries(lib PRIVATE Qt5::Core)

target_compile_definitions(lib PRIVATE LIB_LIBRARY)

target_include_directories(lib
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
