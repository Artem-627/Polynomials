//
// Created by artem627 on 5/6/24.
//
#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "PolynomialFiniteStateMachineStates.h"
#include "../Monomials/Monomial.h"

namespace Polynomial_FSM {
    // helper type for the visitor
    template<class... Ts>
    struct overload : Ts... {
        using Ts::operator()...;
    };

    template<class... Ts>
    overload(Ts...) -> overload<Ts...>;

    class ReadPolynomial {
    public:
        explicit ReadPolynomial(std::string const &str);

        ~ReadPolynomial();

        [[nodiscard]]
        std::vector <Monomial>* getMonomials() const;

    private:
        std::string input;
        std::vector<Monomial> *monomials;

        /// Get event type from current symbol
        [[nodiscard]]
        polynomials::event getEvent(char const &symbol) const;

        /// Process event
        polynomials::state processEvent(polynomials::state const &curr_state, polynomials::event const &curr_event);


        /// Begin
        polynomials::state onEvent(polynomials::states::Begin const &curr_state, polynomials::events::Number const &curr_event);
        polynomials::state onEvent(polynomials::states::Begin const &curr_state, polynomials::events::Letter const &curr_event);
        polynomials::state onEvent(polynomials::states::Begin const &curr_state, polynomials::events::Sign const &curr_event);

        /// Monomial
        polynomials::state onEvent(polynomials::states::Monomaial const &curr_state, polynomials::events::Sign const &curr_event);
        polynomials::state onEvent(polynomials::states::Monomaial const &curr_state, polynomials::events::Number const &curr_event);
        polynomials::state onEvent(polynomials::states::Monomaial const &curr_state, polynomials::events::Letter const &curr_event);
        polynomials::state onEvent(polynomials::states::Monomaial const &curr_state, polynomials::events::Caret const &curr_event);
        polynomials::state onEvent(polynomials::states::Monomaial const &curr_state, polynomials::events::End const &curr_event);

        /// Default
        polynomials::state onEvent(polynomials::state const &curr_state, polynomials::event const &curr_event);


        /// Applying states
        void applyState(polynomials::states::Monomaial const &curr_state);
    };
}

