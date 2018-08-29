cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-parameter")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-compare")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=integer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(APPLE)
  list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/bison")
endif(APPLE)

find_package(Bison 3 REQUIRED)
find_package(Elektra REQUIRED)

set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Source)

bison_target(YAMBi ${SOURCE_DIRECTORY}/parser.ypp
             ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)

if(NOT BISON_YAMBi_DEFINED)
  message(fatal "Unable to generate parser")
endif(NOT BISON_YAMBi_DEFINED)

set(SOURCE_FILES
    ${SOURCE_DIRECTORY}/lexer.hpp
    ${SOURCE_DIRECTORY}/lexer.cpp
    ${SOURCE_DIRECTORY}/driver.hpp
    ${SOURCE_DIRECTORY}/driver.cpp
    ${SOURCE_DIRECTORY}/symbol.hpp
    ${SOURCE_DIRECTORY}/yambi.cpp
    ${BISON_YAMBi_OUTPUT_SOURCE}
    ${BISON_YAMBi_OUTPUT_HEADER})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${SOURCE_DIRECTORY})
add_executable(yambi ${SOURCE_FILES})
