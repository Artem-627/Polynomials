cmake_minimum_required(VERSION 3.28)
project(Polynomials-root)


# Set cmake flags
set(CMAKE_CXX_STANDARD 23)


# Including files
file(GLOB_RECURSE MODULE_HEADERS
        source/Monomials/Monomial.h
        source/Monomials/MonomialFiniteStateMachine.h
        source/Monomials/MonomialFiniteStateMachineStates.h
        source/Monomials/MonomialExceptions.h
)

file(GLOB_RECURSE MODULES_CPP
        source/Monomials/Monomial.cpp
        source/Monomials/MonomialFiniteStateMachine.cpp
        source/Monomials/MonomialFiniteStateMachineStates.cpp
        source/Monomials/MonomialExceptions.cpp
)


# Adding source
add_subdirectory(source)
# Adding tests
add_subdirectory(tests)


# Enabling tests
enable_testing()
add_test(NAME gtest_tests COMMAND tests/tests --gtest_output=xml:./ctest-tests.xml)