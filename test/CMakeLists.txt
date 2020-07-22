cmake_minimum_required(VERSION 3.9)
project(test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE DUMMY_SOURCE 
source/* 
resources/*
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Sources" FILES ${DUMMY_SOURCE})

add_executable(test ${DUMMY_SOURCE})

target_link_libraries(test core)

set_target_properties(test PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/resources")