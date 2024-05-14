//
// Created by artem627 on 5/3/24.
//
#include "Polynomial.h"

#include <valarray>

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
            monomials->operator[](curr_monomial_index) =
                    monomials->operator[](curr_monomial_index) + monomials->operator[](curr_monomial_index + 1);
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

std::string Polynomial::toString() const {
    std::string res;

    for (int i = 0; i < monomials->getSize(); ++i) {
        if (i != 0 && monomials->operator[](i).getValue() >= 0) {
            res += "+";
        }
        res += monomials->operator[](i).toString();
    }

    return res;
}

Polynomial Polynomial::getDerivative(std::uint16_t const &derivative_degree, char const &variable) const {
    Polynomial result(*this);

    for (int i = 0; i < derivative_degree; ++i) {
        Polynomial curr_polynomial;
        for (int curr_monomial_index = 0; curr_monomial_index < result.monomials->getSize(); ++curr_monomial_index) {
            // curr_polynomial.monomials->operator[](i) = result.monomials->operator[](i).getDerivative(variable);
            curr_polynomial += result.monomials->operator[](curr_monomial_index).getDerivative(variable);
            // curr_polynomial = curr_polynomial + Polynomial();
        }
        curr_polynomial.simplify();
        result = std::move(curr_polynomial);
    }

    return result;
}

inline std::vector <std::int64_t> dividers(std::int64_t n) {
    std::vector <std::int64_t> result;

    if (n < 0) n = -n;

    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            result.push_back(i);
            result.push_back(-i);
            if (i * i != n) {
                result.push_back(n / i);
                result.push_back(-(n / i));
            }
        }
    }

    return result;
}

std::vector <std::int64_t> Polynomial::roots() {
    std::vector <std::int64_t> roots;

    simplify();

    std::vector<std::uint16_t> last_monomial_powers = monomials->operator[](monomials->getSize() - 1).getPowers();
    int count_not_zero = 0;
    for (char variable = 'a'; variable <= 'z'; ++variable) {
        if (last_monomial_powers[variable - 'a'] != 0) {
            ++count_not_zero;
        }
    }

    std::vector<std::uint16_t> first_monomial_powers = monomials->operator[](0).getPowers();
    char active_variable;
    for (char variable = 'a'; variable <= 'z'; ++variable) {
        if (first_monomial_powers[variable - 'a'] != 0) {
            active_variable = variable;
        }
    }

    if (count_not_zero == 1) {
        roots.push_back(0);
    }

    try {
        std::int64_t last_monomial_value = monomials->operator[](monomials->getSize() - 1).getValue();
        std::vector <std::int64_t> dividers = ::dividers(last_monomial_value);

        for (auto &el : dividers) {
            std::map<char, std::int64_t> variables;
            variables[active_variable] = el;
            if (calculate(variables) == 0) {
                roots.push_back(el);
            }
        }

    } catch (std::logic_error) {
        throw std::logic_error("too mush variables in polynomial");
    }

    std::ranges::sort(roots.begin(), roots.end());
    return roots;
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

Polynomial Polynomial::operator*(Polynomial const &other) const {
    Polynomial result;

    for (int curr_monomial_index = 0; curr_monomial_index < monomials->getSize(); ++curr_monomial_index) {
        for (int curr_monomial_other_index = 0; curr_monomial_other_index < other.monomials->getSize(); ++curr_monomial_other_index) {
            result += monomials->operator[](curr_monomial_index) * other.monomials->operator[](curr_monomial_other_index);
        }
    }

    result.simplify();
    return result;
}

void Polynomial::operator+=(Monomial const &monomial) const {
    monomials->pushBack(monomial);
}
