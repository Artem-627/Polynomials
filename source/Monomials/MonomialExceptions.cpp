//
// Created by artem627 on 4/21/24.
//
#include "MonomialExceptions.h"

monomial_error::UnknownSymbol::UnknownSymbol(std::string const &monomial) {
    what_message += (" in monomial " + monomial);
}

[[nodiscard]]
const char* monomial_error::UnknownSymbol::what() const noexcept {
    return what_message.c_str();
}
