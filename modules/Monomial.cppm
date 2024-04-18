//
// Created by artem627 on 4/17/24.
//
module;

#include <vector>
#include <cstdint>
#include <cstdio>

export module Monomial;

export class Monomial {
private:
    std::vector <std::uint8_t>* powers = new std::vector<std::uint8_t>(26, 0);
    float value = 0;

    Monomial() = default;

    Monomial(Monomial const &other) {
        printf("[Copy constructor called]");
        powers = other.powers;
        value = other.value;
    }

    Monomial(Monomial &&other) noexcept
        : powers(other.powers),
          value(other.value) {
        printf("[Move constructor called]");
        other.powers = nullptr;
    }

    explicit Monomial(const float &value)
        :value(value) {}

    ~Monomial() = default;

    friend Monomial operator+(Monomial const &first, Monomial const &second);
};

Monomial operator +(Monomial const &first, Monomial const &second) {
    Monomial result(first);

    return result;
}
