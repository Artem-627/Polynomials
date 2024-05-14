//
// Created by artem627 on 5/3/24.
//
#pragma once

#include <string>

#include "../Monomials/Monomial.h"
#include "../List/List.h"

class Polynomial {
public:
    Polynomial();

    Polynomial(Polynomial const &other);

    Polynomial(Polynomial &&other) noexcept;

    explicit Polynomial(std::string const &str);

    ~Polynomial();

    [[nodiscard]]
    List<Monomial> *getMonomials() const;

    void simplify();

    void sort() const;

    [[nodiscard]]
    std::int64_t calculate(std::map<char, std::int64_t> const &variables_values) const;

    std::string toString() const;

    Polynomial getDerivative(std::uint16_t const &, char const &) const;

    std::vector <std::int64_t> roots();

public:
    bool operator==(Polynomial const &other) const;

    Polynomial operator+(Polynomial const &other) const;

    Polynomial operator*(Polynomial const &other) const;

    void operator+=(Monomial const &monomial) const;

    Polynomial &operator=(const Polynomial &other) {
        monomials = new List<Monomial>();
        for (int i = 0; i < other.monomials->getSize(); ++i) {
            monomials->pushBack(other.monomials->operator[](i));
        }

        return *this;
    }

private:
    List<Monomial> *monomials;
};
