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


Monomial_FSM::ReadMonomial::ReadMonomial(std::string const &str) {
    input = str;

    auto curr_symbol = str.begin();
    monomials::state curr_state = monomials::states::Begin{};
    while (!std::holds_alternative<monomials::states::End>(curr_state)) {
        monomials::event curr_event;
        if (curr_symbol == str.end()) {
            curr_event = monomials::events::End{};
        } else {
            curr_event = getEvent(*curr_symbol);
        }

        curr_state = processEvent(curr_state, curr_event);
        ++curr_symbol;
    }

    if (value == 0) {
        clearPowers();
    }
}

/// Getters
[[nodiscard]]
int Monomial_FSM::ReadMonomial::getValue() const {
    return (sign ? -this->value : this->value);
}

[[nodiscard]]
std::vector<std::uint16_t> *Monomial_FSM::ReadMonomial::getPowers() const {
    return this->powers;
}

Monomial_FSM::ReadMonomial::~ReadMonomial() {
    delete powers;
}


void Monomial_FSM::ReadMonomial::clearPowers() const {
    std::ranges::fill(powers->begin(), powers->end(), 0);
}

monomials::event Monomial_FSM::ReadMonomial::getEvent(char const &symbol) const {
    monomials::event result;
    if (symbol >= 'a' && symbol <= 'z') {
        result = monomials::events::Letter{symbol};
    } else if (symbol >= '0' && symbol <= '9') {
        result = monomials::events::Number{symbol};
    } else if (symbol == '^') {
        result = monomials::events::Caret{symbol};
    } else if (symbol == '-' || symbol == '+') {
        result = monomials::events::Sign{symbol};
    } else {
        throw monomial_error::UnknownSymbol(input);
    }
    return result;
}

monomials::state Monomial_FSM::ReadMonomial::processEvent(monomials::state const &curr_state, monomials::event const &curr_event) {
    monomials::state result;
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

/// Default state
monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::state const &curr_state, monomials::event const &curr_event) {
    std::cerr << "[Default ReadMonomial::onEvent() was called]" << '\n';

    return monomials::states::End{};
}

/// Begin
monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Begin const &curr_state, monomials::events::Number const &curr_event) {
    return monomials::states::Coefficient{std::string(1, curr_event.symbol)};
}

monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Begin const &curr_state, monomials::events::Letter const &curr_event) {
    return monomials::states::Variable{curr_event.symbol};
}

monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Begin const &curr_state, monomials::events::Sign const &curr_event) {
    return monomials::states::Sign{curr_event.symbol};
}

/// Sign
monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Sign const &curr_state, monomials::events::Number const &curr_event) {
    applyState(curr_state);

    return monomials::states::Coefficient{std::string(1, curr_event.symbol)};
}

monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Sign const &curr_state, monomials::events::Letter const &curr_event) {
    applyState(curr_state);

    return monomials::states::Variable{curr_event.symbol};
}

/// Coefficient
monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Coefficient const &curr_state, monomials::events::Number const &curr_event) {
    return monomials::states::Coefficient{curr_state.curr_coefficient + curr_event.symbol};
}

monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Coefficient const &curr_state, monomials::events::Letter const &curr_event) {
    applyState(curr_state);

    return monomials::states::Variable{curr_event.symbol};
}

monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Coefficient const &curr_state, monomials::events::End const &curr_event) {
    applyState(curr_state);

    return monomials::states::End{};
}

/// Variable
monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Variable const &curr_state, monomials::events::Caret const &curr_event) {
    return monomials::states::Caret{curr_state.variable};
}

monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Variable const &curr_state, monomials::events::Letter const &curr_event) {
    applyState(curr_state);

    return monomials::states::Variable{curr_event.symbol};
}

monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Variable const &curr_state, monomials::events::End const &curr_event) {
    applyState(curr_state);

    return monomials::states::End{};
}

/// Caret
monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Caret const &curr_state, monomials::events::Number const &curr_event) {
    return monomials::states::Power{curr_state.variable, std::string(1, curr_event.symbol)};
}

/// Power
monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Power const &curr_state, monomials::events::Number const &curr_event) {
    return monomials::states::Power{curr_state.variable, curr_state.curr_power + curr_event.symbol};
}

monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Power const &curr_state, monomials::events::Letter const &curr_event) {
    applyState(curr_state);

    return monomials::states::Variable{curr_event.symbol};
}

monomials::state Monomial_FSM::ReadMonomial::onEvent(monomials::states::Power const &curr_state, monomials::events::End const &curr_event) {
    applyState(curr_state);

    return monomials::states::End{};
}

/// Applying states
void Monomial_FSM::ReadMonomial::applyState(monomials::states::Sign const &curr_state) {
    sign = (curr_state.sign == '-');
}

void Monomial_FSM::ReadMonomial::applyState(monomials::states::Coefficient const &curr_state) {
    value = std::stoi(curr_state.curr_coefficient);
}

void Monomial_FSM::ReadMonomial::applyState(monomials::states::Variable const &curr_state) {
    ++powers->at(curr_state.variable - 'a');
}

void Monomial_FSM::ReadMonomial::applyState(monomials::states::Power const &curr_state) {
    powers->at(curr_state.variable - 'a') += std::stoi(curr_state.curr_power);
}
