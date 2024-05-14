//
// Created by artem627 on 5/3/24.
//
#include "Polynomial.h"
#include "PolynomialFiniteStateMachine.h"

#include "../Monomials/MonomialFiniteStateMachineStates.h"

Polynomial::Polynomial() {
    monomials = new List<Monomial>;
}

Polynomial::Polynomial(Polynomial const &other) {
    monomials = new List<Monomial>(*other.monomials);
    simplify();
}

Polynomial::Polynomial(Polynomial &&other) noexcept {
    monomials = other.monomials;
    other.monomials = nullptr;
}

Polynomial::Polynomial(std::string const &str) {
    monomials = new List<Monomial>;

    auto FSM_polynomial = Polynomial_FSM::ReadPolynomial(str);
    std::vector<Monomial> *monomials_vector = FSM_polynomial.getMonomials();
    for (Monomial const &monomial: *monomials_vector) {
        monomials->pushBack(monomial);
    }
    simplify();
}

List<Monomial> *Polynomial::getMonomials() const {
    return monomials;
}

Polynomial::~Polynomial() {
    delete monomials;
}


void Polynomial::sort() const {
    monomials->sort();
}

void Polynomial::simplify() {
    sort();

    int curr_monomial_index = 0;
    while (curr_monomial_index < monomials->getSize() - 1) {
        if (monomials->operator[](curr_monomial_index) == monomials->operator[](curr_monomial_index + 1)) {
            monomials->operator[](curr_monomial_index) = monomials->operator[](curr_monomial_index) + monomials->operator[](curr_monomial_index + 1);
            monomials->remove(curr_monomial_index + 1);
        } else {
            ++curr_monomial_index;
        }
    }

    if (monomials->getSize() != 1) {
        int curr_monomial_index = 0;
        while (curr_monomial_index < monomials->getSize()) {
            if (monomials->operator[](curr_monomial_index) == Monomial("0") &&
                monomials->operator[](curr_monomial_index).getValue() == 0) {
                monomials->remove(curr_monomial_index);
            } else {
                ++curr_monomial_index;
            }
        }
    }
}

std::int64_t Polynomial::calculate(std::map<char, std::int64_t> const &variables_values) const {
    std::int64_t result = 0;
    for (int i = 0; i < monomials->getSize(); ++i) {
        result += monomials->operator[](i).calculate(variables_values);
    }

    return result;
}


bool Polynomial::operator==(Polynomial const &other) const {
    for (int i = 0; i < monomials->getSize(); ++i) {
        if (monomials->operator[](i) != other.monomials->operator[](i)) {
            return false;
        }
    }
    return true;
}

Polynomial Polynomial::operator+(Polynomial const &other) const {
    Polynomial result(*this);
    for (int i = 0; i < other.monomials->getSize(); ++i) {
            result.monomials->pushBack(other.monomials->operator[](i));
    }
    result.simplify();
    return result;
}

