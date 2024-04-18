cmake_minimum_required(VERSION 3.28)
project(Polynomials)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(PREBUILT_MODULE_PATH ${CMAKE_BINARY_DIR}/engine/modules)

#include(CTest)


file(GLOB_RECURSE TEST_MODULE_FILES
        modules/Monomial.cppm
)
add_library(Polynomial_modules)
target_sources(Polynomial_modules PUBLIC
        FILE_SET CXX_MODULES
        FILES modules/Monomial.cppm
)

add_executable(Polynomials
        source/main.cpp
)

target_link_libraries(Polynomials Polynomial_modules)
