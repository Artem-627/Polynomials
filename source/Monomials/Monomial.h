//
// Created by artem627 on 28/04/24.
//
#pragma once

#include <vector>
#include <cstdint>
#include <cstdio>
#include <string>
#include <map>
#include <stdexcept>


class Monomial {
public:
    Monomial() = default;

    Monomial(Monomial const &other);

    Monomial(Monomial &&other) noexcept;

    explicit Monomial(int const &value);

    explicit Monomial(std::string const &str);

    ~Monomial();

    [[nodiscard]]
    int getValue() const;

    [[nodiscard]]
    std::uint16_t getPower(char const &variable) const;

    [[nodiscard]]
    Monomial getDerivative(char const &variable) const;

    std::int64_t calculate(std::map <char, std::int64_t> const &variables_values) const;

private:
    std::vector <std::uint16_t>* powers = new std::vector<std::uint16_t>(26, 0);
    int value = 0;

public:

    friend Monomial operator+(Monomial const &first, Monomial const &second);
    friend Monomial operator-(Monomial const &first, Monomial const &second);
    friend Monomial operator*(Monomial const &first, Monomial const &second);
};
