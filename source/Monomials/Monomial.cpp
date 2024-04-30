//
// Created by artem627 on 4/17/24.
//
#include "Monomial.h"

#include <algorithm>

#include "MonomialFiniteStateMachine.h"

Monomial::Monomial(Monomial const &other) {
    // printf("[Copy constructor called]");
    // powers = other.powers;
    value = other.value;
    std::ranges::copy(other.powers->begin(), other.powers->end(), powers->begin());
}

Monomial::Monomial(Monomial &&other) noexcept {
    value = other.value;
    std::ranges::move(other.powers->begin(), other.powers->end(), powers->begin());
    // printf("[Move constructor called]");
    // other.powers = nullptr;
}

Monomial::Monomial(int const &value)
    : value(value) {
}

Monomial::Monomial(std::string const &str) {
    // auto FSM_monomial = FSM::ReadMonomial(str);
    auto FSM_monomial = FSM::ReadMonomial(str);
    this->value = FSM_monomial.getValue();

    auto FSM_powers = FSM_monomial.getPowers();
    // for (int i = 0; i < powers->size(); ++i) {
    //
    // }
    std::move(FSM_powers->begin(), FSM_powers->end(), powers->begin());
}

Monomial::~Monomial() {
    delete powers;
};


[[nodiscard]]
int Monomial::getValue() const {
    return value;
}

[[nodiscard]]
std::uint16_t Monomial::getPower(char const &variable) const {
    if (variable < 'a' || variable > 'z') {
        throw std::logic_error("Invalid variable");
    }
    return powers->at(variable - 'a');
}

[[nodiscard]]
Monomial Monomial::getDerivative(char const &variable) const {
    if (variable < 'a' || variable > 'z') {
        throw std::logic_error("Invalid variable");
    }

    Monomial result = Monomial(*this);
    result.value *= result.powers->at(variable - 'a');
    --result.powers->at(variable - 'a');

    return result;
};

[[nodiscard]]
std::int64_t Monomial::calculate(std::map <char, std::int64_t> const &variables_values) const {
    for (int i = 0; i < powers->size(); ++i) {
        if (powers->at(i) > 0 && variables_values.contains('a' + i)) {
            throw std::logic_error("Variable not found");
        }
    }

    std::int64_t result = value;
    for (std::pair <const char, const std::int64_t> curr_variable : variables_values) {
        std::int64_t curr_degree_value = 1;
        for (int curr_degree = 0; curr_degree < this->getPower(curr_variable.first); ++curr_degree) {
            curr_degree_value *= curr_variable.second;
        }
        result *= curr_degree_value;
    }
    return result;
}


Monomial operator +(Monomial const &first, Monomial const &second) {
    if (std::equal(first.powers->begin(), first.powers->end(), second.powers->begin())) {
        auto result = Monomial(first);
        result.value += second.value;
        if (result.value == 0) {
            return Monomial(0);
        }
        return result;
    }
    throw std::logic_error("Monomials is not homogeneous");
}

Monomial operator -(Monomial const &first, Monomial const &second) {
    if (std::equal(first.powers->begin(), first.powers->end(), second.powers->begin())) {
        auto result = Monomial(first);
        result.value -= second.value;
        if (result.value == 0) {
            return Monomial(0);
        }
        return result;
    }
    throw std::logic_error("Monomials is not homogeneous");
}

Monomial operator *(Monomial const &first, Monomial const &second) {
    auto result = Monomial(first);
    result.value *= second.value;
    for (int i = 0; i < result.powers->size(); ++i) {
        result.powers->at(i) += second.powers->at(i);
    }
    return result;
}
