// module;

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <map>
#include <string>
#include <vector>
#include <cstdint>

#include "../source/Monomials/Monomial.h"


/// Tests for monomials without variables
TEST(MonomailConstructorTest, OnlyNumbers) {
    struct monomial_test {
        std::string input;
        int value;
        std::map<char, std::uint16_t> powers;
    };

    std::vector<monomial_test> tests{
                {"123", 123, {}},
                {"-123", -123, {}},

                {"05", 5, {}},
                {"-05", -5, {}},

                {"0", 0, {}},
            };

    for (auto test : tests) {
        Monomial monomial(test.input);
        if (monomial.getValue() != test.value) {
            FAIL() << "Incorrect value at test " << test.input << " (received " << monomial.getValue() << ")";
        }
        for (char variable = 'a'; variable <= 'z'; ++variable) {
            if (monomial.getPower(variable) != test.powers[variable]) {
                FAIL() << "Incorrect power of " << variable << " at test " << test.input;
            }
        }
    }

    SUCCEED();
}


/// Tests for monomials with variables
TEST(MonomailConstructorTest, NumbersWithVariables) {
    struct monomial_test {
        std::string input;
        int value;
        std::map<char, std::uint16_t> powers;
    };

    std::vector<monomial_test> tests{
            {"a", 1, {{'a', 1}}},
            {"b^2", 1, {{'b', 2}}},

            {"aaaaa", 1, {{'a', 5}}},
            {"abcde", 1, {{'a', 1}, {'b', 1}, {'c', 1}, {'d', 1}, {'e', 1}}},
            {"ababa", 1, {{'a', 3}, {'b', 2}}},
            {"aabaa", 1, {{'a', 4}, {'b', 1}}},
            {"a^2ab", 1, {{'a', 3}, {'b', 1}}},

            {"0d^1", 0, {}},
            {"0a^2b^3c^1", 0, {}},
            {"0x^5", 0, {}},
            {"0x", 0, {}},
            {"0abc^8", 0, {}},

            {"a^2b^3c^4", 1, {{'a', 2}, {'b', 3}, {'c', 4}}},
            {"x^7", 1, {{'x', 7}}},
            {"z^2", 1, {{'z', 2}}},
            {"d^1", 1, {{'d', 1}}},
            {"a^2b^3c^1", 1, {{'a', 2}, {'b', 3}, {'c', 1}}},
            {"x^5", 1, {{'x', 5}}},
            {"e^0", 1, {}},
            {"a^0b^0", 1, {}},
            {"m^2n^1p^3", 1, {{'m', 2}, {'n', 1}, {'p', 3}}},
            {"x^4yz^0", 1, {{'x', 4}, {'y', 1}}},
            {"a^1b^0c", 1, {{'a', 1}, {'c', 1}}},

            {"72a^3bd^4c^0asf", 72, {{'a', 4}, {'b', 1}, {'d', 4}, {'s', 1}, {'f', 1}}},
            {"-10a^2b^3c^4", -10, {{'a', 2}, {'b', 3}, {'c', 4}}},
            {"5x^7", 5, {{'x', 7}}},
            {"5z^2", 5, {{'z', 2}}},
            {"3d^1", 3, {{'d', 1}}},
            {"7a^2b^3c^1", 7, {{'a', 2}, {'b', 3}, {'c', 1}}},
            {"-8x^5", -8, {{'x', 5}}},
            {"2e^0", 2, {}},
            {"4a^0b^0c^0", 4, {}},
            {"-2y^3", -2, {{'y', 3}}},
            {"5mn^1p", 5, {{'m', 1}, {'n', 1}, {'p', 1}}},
            {"-25x^4yz^0y", -25, {{'x', 4}, {'y', 2}}},
            {"9a^1b^0c^5", 9, {{'a', 1}, {'c', 5}}},
            {"-7r^3s^2t^1", -7, {{'r', 3}, {'s', 2}, {'t', 1}}},
        };

    for (auto test : tests) {
        Monomial monomial(test.input);
        if (monomial.getValue() != test.value) {
            FAIL() << "Incorrect value at test " << test.input << " (received " << monomial.getValue() << ")";
        }
        for (char variable = 'a'; variable <= 'z'; ++variable) {
            if (monomial.getPower(variable) != test.powers[variable]) {
                FAIL() << "Incorrect power of " << variable << " at test " << test.input;
            }
        }
    }

    SUCCEED();
}
