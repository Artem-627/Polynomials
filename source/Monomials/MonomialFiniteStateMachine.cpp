//
// Created by artem627 on 4/20/24.
//
#include <string>
#include <vector>
#include <cstdint>
#include <variant>
#include <gtest/gtest.h>

#include "MonomialFiniteStateMachine.h"
#include "MonomialFiniteStateMachineStates.h"
#include "MonomialExceptions.h"


FSM::ReadMonomial::ReadMonomial(std::string const &str) {
    input = str;

    auto curr_symbol = str.begin();
    state curr_state = states::Begin{};
    while (!std::holds_alternative<states::End>(curr_state)) {
        event curr_event;
        if (curr_symbol == str.end()) {
            curr_event = events::End{};
        } else {
            curr_event = getEvent(*curr_symbol);
        }

        curr_state = processEvent(curr_state, curr_event);
        ++curr_symbol;
    }
}

/// Getters
[[nodiscard]]
int FSM::ReadMonomial::getValue() const {
    return (sign ? -this->value : this->value);
}

[[nodiscard]]
std::vector<std::uint16_t> *FSM::ReadMonomial::getPowers() const {
    return this->powers;
}

FSM::ReadMonomial::~ReadMonomial() {
    delete powers;
}


event FSM::ReadMonomial::getEvent(char const &symbol) const {
    event result;
    if (symbol >= 'a' && symbol <= 'z') {
        result = events::Letter{symbol};
    } else if (symbol >= '0' && symbol <= '9') {
        result = events::Number{symbol};
    } else if (symbol == '^') {
        result = events::Caret{symbol};
    } else if (symbol == '-' || symbol == '+') {
        result = events::Sign{symbol};
    } else {
        throw monomial_error::UnknownSymbol(input);
    }
    return result;
}

state FSM::ReadMonomial::processEvent(state const &curr_state, event const &curr_event) {
    state result;
    std::visit(
        overload{
            [this, &result](auto const &state_, auto const &event_) {
                result = this->onEvent(state_, event_);
            }
        },
        curr_state, curr_event
    );

    return result;
}

state FSM::ReadMonomial::onEvent(state const &curr_state, event const &curr_event) {
    std::cerr << "[Default onEvent() was called]" << '\n';

    return states::End{};
}

state FSM::ReadMonomial::onEvent(states::Begin const &curr_state, events::Number const &curr_event) {
    return states::Coefficient{std::string(1, curr_event.symbol)};
}
state FSM::ReadMonomial::onEvent(states::Begin const &curr_state, events::Sign const &curr_event) {
    return states::Sign{curr_event.symbol};
}

/// Sign
state FSM::ReadMonomial::onEvent(states::Sign const &curr_state, events::Number const &curr_event) {
    applyState(curr_state);

    return states::Coefficient{""};
}
state FSM::ReadMonomial::onEvent(states::Sign const &curr_state, events::Letter const &curr_event) {
    applyState(curr_state);

    return states::Variable{};
}

/// Coefficient
state FSM::ReadMonomial::onEvent(states::Coefficient const &curr_state, events::Number const &curr_event) {
    return states::Coefficient{curr_state.curr_coefficient + curr_event.symbol};
}
state FSM::ReadMonomial::onEvent(states::Coefficient const &curr_state, events::Letter const &curr_event) {
    applyState(curr_state);

    return states::Variable{curr_event.symbol};
}
state FSM::ReadMonomial::onEvent(states::Coefficient const &curr_state, events::End const &curr_event) {
    applyState(curr_state);

    return states::End{};
}

/// Variable
state FSM::ReadMonomial::onEvent(states::Variable const &curr_state, events::Caret const &curr_event) {
    return states::Caret{curr_state.variable};
}
state FSM::ReadMonomial::onEvent(states::Variable const &curr_state, events::Letter const &curr_event) {
    applyState(curr_state);

    return states::Variable{curr_event.symbol};
}
state FSM::ReadMonomial::onEvent(states::Variable const &curr_state, events::End const &curr_event) {
    applyState(curr_state);

    return states::End{};
}

/// Caret
state FSM::ReadMonomial::onEvent(states::Caret const &curr_state, events::Number const &curr_event) {
    return states::Power{curr_state.variable, std::to_string(curr_event.symbol - '0')};
}

/// Power
state FSM::ReadMonomial::onEvent(states::Power const &curr_state, events::Number const &curr_event) {
    return states::Power{curr_state.variable, curr_state.curr_power + curr_event.symbol};
}
state FSM::ReadMonomial::onEvent(states::Power const &curr_state, events::Letter const &curr_event) {
    applyState(curr_state);

    return states::Variable{curr_event.symbol};
}
state FSM::ReadMonomial::onEvent(states::Power const &curr_state, events::End const &curr_event) {
    applyState(curr_state);

    return states::End{};
}

/// Applying states
void FSM::ReadMonomial::applyState(states::Sign const &curr_state) {
    sign = (curr_state.sign == '-');
}
void FSM::ReadMonomial::applyState(states::Coefficient const &curr_state) {
    value = std::stoi(curr_state.curr_coefficient);
}
void FSM::ReadMonomial::applyState(states::Variable const &curr_state) {
    ++powers->at(curr_state.variable - 'a');
}
void FSM::ReadMonomial::applyState(states::Power const &curr_state) {
    powers->at(curr_state.variable - 'a') += std::stoi(curr_state.curr_power);
}
