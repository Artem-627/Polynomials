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


        List/List.h


        Polynomials/Polynomial.h
        Polynomials/Polynomial.cpp

        Polynomials/PolynomialExceptions.h
        Polynomials/PolynomialExceptions.cpp

        Polynomials/PolynomialFiniteStateMachineStates.h

        Polynomials/PolynomialFiniteStateMachine.h
        Polynomials/PolynomialFiniteStateMachine.cpp
)
