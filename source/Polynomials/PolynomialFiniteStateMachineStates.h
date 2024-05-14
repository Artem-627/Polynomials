//
// Created by artem627 on 5/4/24.
//
#pragma once

#include <variant>
#include <string>

namespace polynomials {
    namespace states {
        struct Begin {
            void operator()() const {
            };
        };

        struct Monomaial {
            std::string curr_monomial;
            void operator()(std::string const &curr_monomial_) { curr_monomial = curr_monomial_; }
        };

        struct End {
            void operator()() {
            };
        };
    };

    namespace events {
        struct Sign {
            char symbol;
            void operator()(char symbol_) { symbol = symbol_; }
        };

        struct Number {
            char symbol;
            void operator()(char symbol_) { symbol = symbol_; };
        };

        struct Letter {
            char symbol;
            void operator()(char symbol_) { symbol = symbol_; };
        };

        struct Caret {
            char symbol;
            void operator()(char symbol_) { symbol = symbol_; };
        };

        struct End {
            void operator()() {
            };
        };
    }

    using state = std::variant<states::Begin, states::Monomaial, states::End>;
    using event = std::variant<events::Sign, events::Number, events::Letter, events::Caret, events::End>;
}


