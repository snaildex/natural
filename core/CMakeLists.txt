cmake_minimum_required(VERSION 3.9)
project(core)

file(GLOB_RECURSE CORE_SOURCE source/*)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Sources" FILES ${CORE_SOURCE})

add_library(core STATIC ${CORE_SOURCE})

if (MSVC)
   set_target_properties(core PROPERTIES COMPILE_FLAGS "/Yustdafx.h")
   set_source_files_properties(source/stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")
endif(MSVC)

target_include_directories (core PUBLIC source)

find_package(Vulkan REQUIRED)
target_include_directories(core PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(core ${Vulkan_LIBRARIES})
#target_link_libraries(core glfw assimp lua_static)
target_link_libraries(core glfw)
#target_link_libraries (core Bullet3Common BulletCollision BulletDynamics BulletInverseDynamics BulletSoftBody LinearMath)

set_target_properties(core PROPERTIES VS_GLOBAL_ROOTNAMESPACE "ogele")