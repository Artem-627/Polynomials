//
// Created by artem627 on 4/20/24.
//
#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <variant>
#include <gtest/gtest.h>

#include "MonomialFiniteStateMachineStates.h"

namespace Monomial_FSM {
    // helper type for the visitor
    template<class... Ts>
    struct overload : Ts... {
        using Ts::operator()...;
    };

    template<class... Ts>
    overload(Ts...) -> overload<Ts...>;

    class ReadMonomial {
    public:
        explicit ReadMonomial(std::string const &str);

        ~ReadMonomial();

        /// Getters
        [[nodiscard]]
        int getValue() const;

        [[nodiscard]]
        std::vector<std::uint16_t> *getPowers() const;

    private:
        std::string input;
        bool sign = false;
        int value = 1;
        std::vector<std::uint16_t> *powers = new std::vector<std::uint16_t>(26, 0);

        /// Set all powers to 0 if value is 0
        void clearPowers() const;

        /// Get event type from current symbol
        [[nodiscard]]
        monomials::event getEvent(char const &symbol) const;

        /// Process event
        monomials::state processEvent(monomials::state const &curr_state, monomials::event const &curr_event);


        /// Begin
        monomials::state onEvent(monomials::states::Begin const &curr_state, monomials::events::Number const &curr_event);
        monomials::state onEvent(monomials::states::Begin const &curr_state, monomials::events::Letter const &curr_event);
        monomials::state onEvent(monomials::states::Begin const &curr_state, monomials::events::Sign const &curr_event);

        /// Sign
        monomials::state onEvent(monomials::states::Sign const &curr_state, monomials::events::Number const &curr_event);
        monomials::state onEvent(monomials::states::Sign const &curr_state, monomials::events::Letter const &curr_event);

        /// Coefficient
        monomials::state onEvent(monomials::states::Coefficient const &curr_state, monomials::events::Number const &curr_event);

        monomials::state onEvent(monomials::states::Coefficient const &curr_state, monomials::events::Letter const &curr_event);

        monomials::state onEvent(monomials::states::Coefficient const &curr_state, monomials::events::End const &curr_event);

        /// Variable
        monomials::state onEvent(monomials::states::Variable const &curr_state, monomials::events::Caret const &curr_event);
        monomials::state onEvent(monomials::states::Variable const &curr_state, monomials::events::Letter const &curr_event);
        monomials::state onEvent(monomials::states::Variable const &curr_state, monomials::events::End const &curr_event);

        /// Caret
        monomials::state onEvent(monomials::states::Caret const &curr_state, monomials::events::Number const &curr_event);

        /// Power
        monomials::state onEvent(monomials::states::Power const &curr_state, monomials::events::Number const &curr_event);
        monomials::state onEvent(monomials::states::Power const &curr_state, monomials::events::Letter const &curr_event);
        monomials::state onEvent(monomials::states::Power const &curr_state, monomials::events::End const &curr_event);

        /// Default
        monomials::state onEvent(monomials::state const &curr_state, monomials::event const &curr_event);


        /// Applying states
        void applyState(monomials::states::Sign const &curr_state);
        void applyState(monomials::states::Coefficient const &curr_state);
        void applyState(monomials::states::Variable const &curr_state);
        void applyState(monomials::states::Power const &curr_state);
    };
}
