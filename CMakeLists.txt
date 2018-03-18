CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(snoo-cue-supervisor CXX)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/deps/snoo-cue-protocol/include)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/deps/snoo-cue-protocol)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FILE(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
FILE(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_executable(snoo-cue-supervisor ${sources} ${headers})
