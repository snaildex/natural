cmake_minimum_required(VERSION 3.9)
project(utils)

file(GLOB_RECURSE utils_SOURCE source/*)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Sources" FILES ${utils_SOURCE})

add_library(utils STATIC ${utils_SOURCE})

target_include_directories (utils PUBLIC source)