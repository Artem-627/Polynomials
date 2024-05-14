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

public:

    bool operator==(Polynomial const &other) const;

    Polynomial operator+(Polynomial const &other) const;

private:
    List<Monomial> *monomials;
};
