cmake_minimum_required(VERSION 3.28)
project(Polynomials)

# Adding main executable file
add_executable(${PROJECT_NAME}
        main.cpp

        Monomials/Monomial.h
        Monomials/Monomial.cpp

        Monomials/MonomialFiniteStateMachine.h
        Monomials/MonomialFiniteStateMachine.cpp

        Monomials/MonomialFiniteStateMachineStates.h

        Monomials/MonomialExceptions.h
        Monomials/MonomialExceptions.cpp
)
