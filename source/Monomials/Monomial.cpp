//
// Created by artem627 on 4/17/24.
//
#include "Monomial.h"
#include "MonomialFiniteStateMachine.h"

Monomial::Monomial(Monomial const &other) {
    printf("[Copy constructor called]");
    powers = other.powers;
    value = other.value;
}

Monomial::Monomial(Monomial &&other) noexcept
    : powers(other.powers),
      value(other.value) {
    printf("[Move constructor called]");
    other.powers = nullptr;
}

Monomial::Monomial(int const &value)
    :value(value) {}

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

Monomial operator +(Monomial const &first, Monomial const &second) {
    Monomial result(first);

    return result;
}
