cmake_minimum_required(VERSION 3.28)
project(tests)


# Import GoogleTest
find_package(PkgConfig REQUIRED)
pkg_check_modules(gtest gtest>=1.10)


include(GoogleTest)


set(TESTS
        List_tests.cpp
        Monomial_tests.cpp
)


add_executable(${PROJECT_NAME}
        ${TESTS}
        main.cpp

        ../source/Monomials/Monomial.h
        ../source/Monomials/Monomial.cpp
        ../source/Monomials/MonomialExceptions.h
        ../source/Monomials/MonomialExceptions.cpp
        ../source/Monomials/MonomialFiniteStateMachine.h
        ../source/Monomials/MonomialFiniteStateMachine.cpp
        ../source/Monomials/MonomialFiniteStateMachineStates.h

        ../source/List/List.h
)

# Adding libraries
target_link_libraries(${PROJECT_NAME}
        gtest
        gtest_main
        gmock
        pthread
)
target_link_libraries(${PROJECT_NAME}
        gcov
)


# Connecting tests
gtest_add_tests(TARGET ${PROJECT_NAME}
        TEST_SUFFIX .noArgs
        TEST_LIST noArgsTests
)