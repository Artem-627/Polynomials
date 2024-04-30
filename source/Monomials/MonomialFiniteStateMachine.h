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

namespace FSM {
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
        event getEvent(char const &symbol) const;

        /// Process event
        state processEvent(state const &curr_state, event const &curr_event);

        /// Begin
        state onEvent(states::Begin const &curr_state, events::Number const &curr_event);
        state onEvent(states::Begin const &curr_state, events::Letter const &curr_event);
        state onEvent(states::Begin const &curr_state, events::Sign const &curr_event);

        /// Sign
        state onEvent(states::Sign const &curr_state, events::Number const &curr_event);
        state onEvent(states::Sign const &curr_state, events::Letter const &curr_event);

        /// Coefficient
        state onEvent(states::Coefficient const &curr_state, events::Number const &curr_event);
        state onEvent(states::Coefficient const &curr_state, events::Letter const &curr_event);
        state onEvent(states::Coefficient const &curr_state, events::End const &curr_event);

        /// Variable
        state onEvent(states::Variable const &curr_state, events::Caret const &curr_event);
        state onEvent(states::Variable const &curr_state, events::Letter const &curr_event);
        state onEvent(states::Variable const &curr_state, events::End const &curr_event);

        /// Caret
        state onEvent(states::Caret const &curr_state, events::Number const &curr_event);

        /// Power
        state onEvent(states::Power const &curr_state, events::Number const &curr_event);
        state onEvent(states::Power const &curr_state, events::Letter const &curr_event);
        state onEvent(states::Power const &curr_state, events::End const &curr_event);

        /// Default
        state onEvent(state const &curr_state, event const &curr_event);


        /// Applying states
        void applyState(states::Sign const &curr_state);
        void applyState(states::Coefficient const &curr_state);
        void applyState(states::Variable const &curr_state);
        void applyState(states::Power const &curr_state);
    };
}
