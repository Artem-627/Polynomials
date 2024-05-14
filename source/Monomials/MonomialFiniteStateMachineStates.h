//
// Created by artem627 on 4/20/24.
//
#pragma once

#include <variant>
#include <string>

namespace monomials {
    namespace states {
        struct Begin {
            void operator()() const {
            };
        };

        struct Sign {
            char sign;
            void operator()(char sign_) { sign = sign_; }
        };

        struct Coefficient {
            std::string curr_coefficient;
            void operator()(std::string const &curr_coefficient_) { curr_coefficient = curr_coefficient_; }
        };

        struct Variable {
            char variable;
            void operator()(char variable_) { variable = variable_; }
        };

        struct Caret {
            char variable;
            void operator()(char variable_) { variable = variable_; }
        };

        struct Power {
            char variable;
            std::string curr_power;

            void operator()(char variable_, std::string const &curr_power_) {
                variable = variable_;
                curr_power = curr_power_;
            }
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

    using state = std::variant<monomials::states::Begin, monomials::states::Sign, monomials::states::Coefficient,
        monomials::states::Variable, monomials::states::Caret, monomials::states::Power, monomials::states::End>;
    using event = std::variant<monomials::events::Sign, monomials::events::Number, monomials::events::Letter,
        monomials::events::Caret, monomials::events::End>;
}
