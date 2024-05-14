#include <iostream>

#include "Monomials/Monomial.h"
#include "Polynomials/Polynomial.h"

int main() {
    std::cout << "Hello, World!" << '\n';

    auto a = Polynomial("a^2+b");
    auto b = Polynomial("b+a^2");

    std::cout << (a == b);

    b.sort();

    std::cout << (a == b);

    return 0;
}
