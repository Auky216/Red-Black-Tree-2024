# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/boost-build/src/boost"
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/boost-build/src/boost-build"
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/boost-build"
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/boost-build/tmp"
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/boost-build/src/boost-stamp"
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/boost-build/src"
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/boost-build/src/boost-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/boost-build/src/boost-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/boost-build/src/boost-stamp${cfgdir}") # cfgdir has leading slash
endif()
