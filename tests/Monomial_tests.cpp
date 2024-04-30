// module;

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <map>
#include <string>
#include <vector>
#include <cstdint>

#include "../source/Monomials/Monomial.h"

/// Monomial constructor tests
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

    for (auto test: tests) {
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

TEST(MonomailConstructorTest, OnlyLetters) {
    struct monomial_test {
        std::string input;
        int value;
        std::map<char, std::uint16_t> powers;
    };

    std::vector<monomial_test> tests{
        {"a", 1, {{'a', 1}}},
        {"aaaaa", 1, {{'a', 5}}},
        {"abcde", 1, {{'a', 1}, {'b', 1}, {'c', 1}, {'d', 1}, {'e', 1}}},
        {"ababa", 1, {{'a', 3}, {'b', 2}}},
        {"aabaa", 1, {{'a', 4}, {'b', 1}}},
        {"-a", -1, {{'a', 1}}},
        {"-aaaaa", -1, {{'a', 5}}},
        {"-abcde", -1, {{'a', 1}, {'b', 1}, {'c', 1}, {'d', 1}, {'e', 1}}},
        {"-ababa", -1, {{'a', 3}, {'b', 2}}},
        {"-aabaa", -1, {{'a', 4}, {'b', 1}}}
    };

    for (auto test: tests) {
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

TEST(MonomailConstructorTest, ZeroCoefficients) {
    struct monomial_test {
        std::string input;
        int value;
        std::map<char, std::uint16_t> powers;
    };

    std::vector<monomial_test> tests{
        {"0a^2", 0, {}},
        {"0x^7", 0, {}},
        {"0z^2", 0, {}},
        {"0d^1", 0, {}},
        {"0a^2b^3c^1", 0, {}},
        {"0x^5", 0, {}},
        {"0x", 0, {}},
        {"0abc^8", 0, {}},
        {"-0a^2", 0, {}},
        {"-0x^7", 0, {}},
        {"-0z^2", 0, {}},
        {"-0d^1", 0, {}},
        {"-0a^2b^3c^1", 0, {}},
        {"-0x^5", 0, {}},
        {"-0x", 0, {}},
        {"-0abc^8", 0, {}}
    };

    for (auto test: tests) {
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

TEST(MonomailConstructorTest, NumbersWithoutCoefficients) {
    struct monomial_test {
        std::string input;
        int value;
        std::map<char, std::uint16_t> powers;
    };

    std::vector<monomial_test> tests{
        {"b^2", 1, {{'b', 2}}},
        {"a^2ab", 1, {{'a', 3}, {'b', 1}}},
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
        {"a^1b^0c", 1, {{'a', 1}, {'c', 1}}}
    };

    for (auto test: tests) {
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

TEST(MonomailConstructorTest, NormalMonomials) {
    struct monomial_test {
        std::string input;
        int value;
        std::map<char, std::uint16_t> powers;
    };

    std::vector<monomial_test> tests{
        {"72a^3bd^4c^0asf", 72, {{'a', 4}, {'b', 1}, {'d', 4}, {'s', 1}, {'f', 1}}},
        {"10a^2b^3c^4", 10, {{'a', 2}, {'b', 3}, {'c', 4}}},
        {"5x^7", 5, {{'x', 7}}},
        {"5z^2", 5, {{'z', 2}}},
        {"3d^1", 3, {{'d', 1}}},
        {"7a^2b^3c^1", 7, {{'a', 2}, {'b', 3}, {'c', 1}}},
        {"8x^5", 8, {{'x', 5}}},
        {"2e^0", 2, {}},
        {"4a^0b^0c^0", 4, {}},
        {"2y^3", 2, {{'y', 3}}},
        {"5mn^1p", 5, {{'m', 1}, {'n', 1}, {'p', 1}}},
        {"25x^4yz^0y", 25, {{'x', 4}, {'y', 2}}},
        {"9a^1b^0c^5", 9, {{'a', 1}, {'c', 5}}},
        {"-7r^3s^2t^1", -7, {{'r', 3}, {'s', 2}, {'t', 1}}},
        {"-72a^3bd^4c^0asf", -72, {{'a', 4}, {'b', 1}, {'d', 4}, {'s', 1}, {'f', 1}}},
        {"-10a^2b^3c^4", -10, {{'a', 2}, {'b', 3}, {'c', 4}}},
        {"-5x^7", -5, {{'x', 7}}},
        {"-5z^2", -5, {{'z', 2}}},
        {"-3d^1", -3, {{'d', 1}}},
        {"-7a^2b^3c^1", -7, {{'a', 2}, {'b', 3}, {'c', 1}}},
        {"-8x^5", -8, {{'x', 5}}},
        {"-2e^0", -2, {}},
        {"-4a^0b^0c^0", -4, {}},
        {"-2y^3", -2, {{'y', 3}}},
        {"-5mn^1p", -5, {{'m', 1}, {'n', 1}, {'p', 1}}},
        {"-25x^4yz^0y", -25, {{'x', 4}, {'y', 2}}},
        {"-9a^1b^0c^5", -9, {{'a', 1}, {'c', 5}}},
        {"-7r^3s^2t^1", -7, {{'r', 3}, {'s', 2}, {'t', 1}}},
    };

    for (auto test: tests) {
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


/// Operator + for monomials
TEST(MonomialAddTest, Monomials_Addition_SamePowers) {
    Monomial first("3a^2b^3");
    Monomial second("2a^2b^3");
    Monomial result = first + second;

    EXPECT_EQ(result.getValue(), 5);
    EXPECT_EQ(result.getPower('a'), 2);
    EXPECT_EQ(result.getPower('b'), 3);
}

TEST(MonomialAddTest, Monomials_Addition_DifferentPowers) {
    Monomial first("3a^2b^3");
    Monomial second("2a^3b^2");

    EXPECT_THROW(first + second, std::logic_error);
}

TEST(MonomialAddTest, Monomials_Addition_ZeroResult) {
    Monomial first("3a^2b^3");
    Monomial second("-3a^2b^3");
    Monomial result = first + second;

    EXPECT_EQ(result.getValue(), 0);
}

TEST(MonomialAddTest, Monomials_Addition_DifferentVariables) {
    Monomial first("3a^2b^3");
    Monomial second("2c^2d^3");

    EXPECT_THROW(first + second, std::logic_error);
}

TEST(MonomialAddTest, Monomials_Addition_WithoutVariables) {
    Monomial first("3");
    Monomial second("2");
    Monomial result = first + second;

    EXPECT_EQ(result.getValue(), 5);
}


/// Operator - for monomials
TEST(MonomialSumTest, Monomials_Substration_SamePowers) {
    Monomial first("3a^2b^3");
    Monomial second("2a^2b^3");
    Monomial result = first - second;

    EXPECT_EQ(result.getValue(), 1);
    EXPECT_EQ(result.getPower('a'), 2);
    EXPECT_EQ(result.getPower('b'), 3);
}

TEST(MonomialSumTest, Monomials_Substration_DifferentPowers) {
    Monomial first("3a^2b^3");
    Monomial second("2a^3b^2");

    EXPECT_THROW(first - second, std::logic_error);
}

TEST(MonomialSumTest, Monomials_Substration_ZeroResult) {
    Monomial first("3a^2b^3");
    Monomial second("3a^2b^3");
    Monomial result = first - second;

    EXPECT_EQ(result.getValue(), 0);
}

TEST(MonomialSumTest, Monomials_Substration_DifferentVariables) {
    Monomial first("3a^2b^3");
    Monomial second("2c^2d^3");

    EXPECT_THROW(first - second, std::logic_error);
}

TEST(MonomialSumTest, Monomials_Substration_WithoutVariables) {
    Monomial first("3");
    Monomial second("2");
    Monomial result = first - second;

    EXPECT_EQ(result.getValue(), 1);
}


/// Operator * for monomials
TEST(MonomialMultTest, Monomials_Multiplication_SamePowers) {
    Monomial first("3a^2b^3");
    Monomial second("2a^2b^3");
    Monomial result = first * second;

    EXPECT_EQ(result.getValue(), 6);
    EXPECT_EQ(result.getPower('a'), 4);
    EXPECT_EQ(result.getPower('b'), 6);
}

TEST(MonomialMultTest, Monomials_Multiplication_DifferentPowers) {
    Monomial first("3a^2b^3");
    Monomial second("2a^3b^2");
    Monomial result = first * second;

    EXPECT_EQ(result.getValue(), 6);
    EXPECT_EQ(result.getPower('a'), 5);
    EXPECT_EQ(result.getPower('b'), 5);
}

TEST(MonomialMultTest, Monomials_Multiplication_ZeroCoefficient) {
    Monomial first("0a^2b^3");
    Monomial second("2a^2b^3");
    Monomial result = first * second;

    EXPECT_EQ(result.getValue(), 0);
}

TEST(MonomialMultTest, Monomials_Multiplication_MultipleVariables) {
    Monomial first("3a^2b^3c^4");
    Monomial second("2a^2b^3c^4");
    Monomial result = first * second;

    EXPECT_EQ(result.getValue(), 6);
    EXPECT_EQ(result.getPower('a'), 4);
    EXPECT_EQ(result.getPower('b'), 6);
    EXPECT_EQ(result.getPower('c'), 8);
}

TEST(MonomialMultTest, Monomials_Multiplication_SamePowersDifferentOrder) {
    Monomial first("3a^2b^3c^4");
    Monomial second("2c^4b^3a^2");
    Monomial result = first * second;

    EXPECT_EQ(result.getValue(), 6);
    EXPECT_EQ(result.getPower('a'), 4);
    EXPECT_EQ(result.getPower('b'), 6);
    EXPECT_EQ(result.getPower('c'), 8);
}

/// Derivative of monomials
TEST(MonomialDerivativeTest, Monomials_Derivative_SingleVariable) {
    Monomial monomial("3a^2");
    Monomial result = monomial.getDerivative('a');

    EXPECT_EQ(result.getValue(), 6);
    EXPECT_EQ(result.getPower('a'), 1);
}

TEST(MonomialDerivativeTest, Monomials_Derivative_MultipleVariables) {
    Monomial monomial("3a^2b^3");
    Monomial result = monomial.getDerivative('a');

    EXPECT_EQ(result.getValue(), 6);
    EXPECT_EQ(result.getPower('a'), 1);
    EXPECT_EQ(result.getPower('b'), 3);
}

TEST(MonomialDerivativeTest, Monomials_Derivative_ZeroPower) {
    Monomial monomial("3a^0b^3");
    Monomial result = monomial.getDerivative('a');

    EXPECT_EQ(result.getValue(), 0);
}

TEST(MonomialDerivativeTest, Monomials_Derivative_NonExistentVariable) {
    Monomial monomial("3a^2b^3");
    Monomial result = monomial.getDerivative('c');

    EXPECT_EQ(result.getValue(), 0);
}

TEST(MonomialDerivativeTest, Monomials_Derivative_Constant) {
    Monomial monomial("3");
    Monomial result = monomial.getDerivative('a');

    EXPECT_EQ(result.getValue(), 0);
}

TEST(MonomialDerivativeTest, Monomials_Derivative_MultiplePowers) {
    Monomial monomial("3a^2b^3c^4");
    Monomial result = monomial.getDerivative('b');

    EXPECT_EQ(result.getValue(), 9);
    EXPECT_EQ(result.getPower('a'), 2);
    EXPECT_EQ(result.getPower('b'), 2);
    EXPECT_EQ(result.getPower('c'), 4);
}

/// Calculation of monomials
TEST(MonomialCalculateTest, Monomials_Calculate_SingleVariable) {
    Monomial monomial("3a^2");
    std::map<char, std::int64_t> variables_values = {{'a', 2}};
    std::int64_t result = monomial.calculate(variables_values);

    EXPECT_EQ(result, 12);
}

TEST(MonomialCalculateTest, Monomials_Calculate_MultipleVariables) {
    Monomial monomial("3a^2b^3");
    std::map<char, std::int64_t> variables_values = {{'a', 2}, {'b', 3}};
    std::int64_t result = monomial.calculate(variables_values);

    EXPECT_EQ(result, 324);
}

TEST(MonomialCalculateTest, Monomials_Calculate_ZeroPower) {
    Monomial monomial("3a^0b^3");
    std::map<char, std::int64_t> variables_values = {{'a', 2}, {'b', 3}};
    std::int64_t result = monomial.calculate(variables_values);

    EXPECT_EQ(result, 81);
}

TEST(MonomialCalculateTest, Monomials_Calculate_NonExistentVariable) {
    Monomial monomial("3a^2b^3");
    std::map<char, std::int64_t> variables_values = {{'a', 2}};

    EXPECT_THROW(monomial.calculate(variables_values), std::logic_error);
}

TEST(MonomialCalculateTest, Monomials_Calculate_Constant) {
    Monomial monomial("3");
    std::map<char, std::int64_t> variables_values = {{'a', 2}};
    std::int64_t result = monomial.calculate(variables_values);

    EXPECT_EQ(result, 3);
}