cmake_minimum_required(VERSION 3.17)
project(Red_Black_Tree_2024)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_search_module(PISTACHE REQUIRED libpistache)

include_directories(${PISTACHE_INCLUDE_DIRS})

add_executable(Red_Black_Tree_2024 main.cpp RBT.h)

target_link_libraries(Red_Black_Tree_2024 ${PISTACHE_LIBRARIES})
 