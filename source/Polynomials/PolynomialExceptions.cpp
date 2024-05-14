//
// Created by artem627 on 5/3/24.
//
#include "PolynomialExceptions.h"

polynomial_error::UnknownSymbol::UnknownSymbol(std::string const &polynomial) {
    what_message += (" in polynomial " + polynomial);
}

[[nodiscard]]
const char* polynomial_error::UnknownSymbol::what() const noexcept {
    return what_message.c_str();
}
