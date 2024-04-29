cmake_minimum_required(VERSION 3.28)
project(tests)


# Import GoogleTest
find_package(PkgConfig REQUIRED)
pkg_check_modules(gtest gtest>=1.10)


include(GoogleTest)


set (TESTS
        Monomial_tests.cpp
)


add_executable(${PROJECT_NAME}
        ${TESTS}
        main.cpp
        ../source/Monomials/Monomial.cpp
        ../source/Monomials/MonomialFiniteStateMachine.cpp
        ../source/Monomials/MonomialExceptions.cpp
        ../source/Monomials/Monomial.h
        ../source/Monomials/MonomialFiniteStateMachine.h
        ../source/Monomials/MonomialFiniteStateMachineStates.h
        ../source/Monomials/MonomialExceptions.h
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
        TEST_SUFFIX     .noArgs
        TEST_LIST       noArgsTests
)