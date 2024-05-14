//
// Created by artem627 on 5/3/24.
//
#pragma once

#include <exception>
#include <string>

namespace polynomial_error {
    class UnknownSymbol final
        : std::exception {
    private:
        std::string what_message = "Unknown symbol in polynomial";
    public:
        explicit UnknownSymbol(std::string const &polynomial);

        [[nodiscard]]
        const char* what() const noexcept override;
    };
}