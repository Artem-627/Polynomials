#include <iostream>

#include "Monomials/Monomial.h"

int main() {
    std::cout << "Hello, World!" << '\n';

    auto m = Monomial("0d^1");
    std::cout << m.getValue() << '\n';
    for (char a = 'a'; a < 'z'; ++a) {
        // if (m.getPower(a) > 0)
            std::cout << a << ": " << m.getPower(a) << '\n';
    }

    return 0;
}
