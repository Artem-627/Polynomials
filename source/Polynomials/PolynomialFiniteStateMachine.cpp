//
// Created by artem627 on 5/6/24.
//
#include "PolynomialFiniteStateMachine.h"

#include <iostream>

#include "PolynomialExceptions.h"


Polynomial_FSM::ReadPolynomial::ReadPolynomial(std::string const &str) {
    input = str;
    monomials = new std::vector<Monomial>;

    auto curr_symbol = str.begin();
    polynomials::state curr_state = polynomials::states::Begin{};
    while (!std::holds_alternative<polynomials::states::End>(curr_state)) {
        polynomials::event curr_event;
        if (curr_symbol == str.end()) {
            curr_event = polynomials::events::End{};
        } else {
            curr_event = getEvent(*curr_symbol);
        }

        curr_state = processEvent(curr_state, curr_event);
        ++curr_symbol;
    }
}

Polynomial_FSM::ReadPolynomial::~ReadPolynomial() {
    delete monomials;
}

std::vector<Monomial> *Polynomial_FSM::ReadPolynomial::getMonomials() const {
    return monomials;
}


polynomials::event Polynomial_FSM::ReadPolynomial::getEvent(char const &symbol) const {
    polynomials::event result;
    if (symbol >= 'a' && symbol <= 'z') {
        result = polynomials::events::Letter{symbol};
    } else if (symbol >= '0' && symbol <= '9') {
        result = polynomials::events::Number{symbol};
    } else if (symbol == '^') {
        result = polynomials::events::Caret{symbol};
    } else if (symbol == '-' || symbol == '+') {
        result = polynomials::events::Sign{symbol};
    } else {
        throw polynomial_error::UnknownSymbol(input);
    }
    return result;
}

polynomials::state Polynomial_FSM::ReadPolynomial::processEvent(polynomials::state const &curr_state,
                                                                polynomials::event const &curr_event) {
    polynomials::state result;
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
polynomials::state Polynomial_FSM::ReadPolynomial::onEvent(polynomials::state const &curr_state,
                                                           polynomials::event const &curr_event) {
    std::cerr << "[Default ReadPolynomial::onEvent() was called]" << '\n';

    return polynomials::states::End{};
}

/// Begin
polynomials::state Polynomial_FSM::ReadPolynomial::onEvent(polynomials::states::Begin const &curr_state,
                                                           polynomials::events::Number const &curr_event) {
    return polynomials::states::Monomaial{std::string(1, curr_event.symbol)};
}

polynomials::state Polynomial_FSM::ReadPolynomial::onEvent(polynomials::states::Begin const &curr_state,
                                                           polynomials::events::Letter const &curr_event) {
    return polynomials::states::Monomaial{std::string(1, curr_event.symbol)};
}

polynomials::state Polynomial_FSM::ReadPolynomial::onEvent(polynomials::states::Begin const &curr_state,
                                                           polynomials::events::Sign const &curr_event) {
    return polynomials::states::Monomaial{std::string(1, curr_event.symbol)};
}

/// Monomial
polynomials::state Polynomial_FSM::ReadPolynomial::onEvent(polynomials::states::Monomaial const &curr_state,
                                                           polynomials::events::Number const &curr_event) {
    return polynomials::states::Monomaial{curr_state.curr_monomial + curr_event.symbol};
}

polynomials::state Polynomial_FSM::ReadPolynomial::onEvent(polynomials::states::Monomaial const &curr_state,
                                                           polynomials::events::Letter const &curr_event) {
    return polynomials::states::Monomaial{curr_state.curr_monomial + curr_event.symbol};
}

polynomials::state Polynomial_FSM::ReadPolynomial::onEvent(polynomials::states::Monomaial const &curr_state,
                                                           polynomials::events::Caret const &curr_event) {
    return polynomials::states::Monomaial{curr_state.curr_monomial + curr_event.symbol};
}

polynomials::state Polynomial_FSM::ReadPolynomial::onEvent(polynomials::states::Monomaial const &curr_state,
                                                           polynomials::events::Sign const &curr_event) {
    applyState(curr_state);

    return polynomials::states::Monomaial{std::string(1, curr_event.symbol)};
}

polynomials::state Polynomial_FSM::ReadPolynomial::onEvent(polynomials::states::Monomaial const &curr_state,
                                                           polynomials::events::End const &curr_event) {
    applyState(curr_state);

    return polynomials::states::End{};
}

void Polynomial_FSM::ReadPolynomial::applyState(polynomials::states::Monomaial const &curr_state) {
    monomials->push_back(Monomial(curr_state.curr_monomial));
}
