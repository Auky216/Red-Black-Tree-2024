# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/crow-build/src/crow"
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/crow-build/src/crow-build"
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/crow-build"
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/crow-build/tmp"
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/crow-build/src/crow-stamp"
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/crow-build/src"
  "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/crow-build/src/crow-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/crow-build/src/crow-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/adrian/proyects/Red-Black-Tree-2024/cmake-build-debug/crow-build/src/crow-stamp${cfgdir}") # cfgdir has leading slash
endif()
