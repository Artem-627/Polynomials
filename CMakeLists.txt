cmake_minimum_required(VERSION 3.28)
project(Polynomials-root)

# Set cmake flags
set(CMAKE_CXX_STANDARD 23)


# Adding source
add_subdirectory(source)
# Adding tests
add_subdirectory(tests)


# Enabling tests
enable_testing()
add_test(NAME gtest_tests COMMAND tests/tests --gtest_output=xml:./ctest-tests.xml)