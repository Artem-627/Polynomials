//
// Created by artem627 on 28/04/24.
//
#pragma once

#include <exception>
#include <string>

namespace monomial_error {
    class UnknownSymbol final
        : std::exception {
    private:
        std::string what_message = "Unknown symbol in monomial";
    public:
        explicit UnknownSymbol(std::string const &monomial);

        [[nodiscard]]
        const char* what() const noexcept override;
    };


}