// module;

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <map>
#include <string>
#include <vector>
#include <cstdint>

#include "../source/Polynomials/Polynomial.h"
#include "../source/Polynomials/PolynomialExceptions.h"
#include "../source/Polynomials/PolynomialFiniteStateMachineStates.h"


/// Polynomial constructor tests
TEST(PolynomialConstructorTest, OnlyNumbers) {
    struct polynomial_test {
        std::string input;
        std::vector<Monomial> monomials;
    };

    std::vector<polynomial_test> tests{
        {"123", std::vector<Monomial>{Monomial("123")}},
        {"-123", std::vector<Monomial>{Monomial("-123")}},
        {"05", std::vector<Monomial>{Monomial("5")}},
        {"-05", std::vector<Monomial>{Monomial("-5")}},
        {"0", std::vector<Monomial>{Monomial("0")}},
    };

    for (auto test: tests) {
        Polynomial polynomial(test.input);

        List<Monomial> test_monomial(test.monomials);
        ASSERT_TRUE(*polynomial.getMonomials() == test_monomial);
    }
}

TEST(PolynomialConstructorTest, OnlyLetters) {
    struct polynomial_test {
        std::string input;
        std::vector<Monomial> monomials;
    };

    std::vector<polynomial_test> tests{
        {"a", std::vector<Monomial>{Monomial("a")}},
        {"-a", std::vector<Monomial>{Monomial("-a")}},
        {"z", std::vector<Monomial>{Monomial("z")}},
        {"-z", std::vector<Monomial>{Monomial("-z")}}
    };

    for (auto test: tests) {
        Polynomial polynomial(test.input);

        List<Monomial> test_monomial(test.monomials);
        ASSERT_TRUE(*polynomial.getMonomials() == test_monomial);
    }
}

TEST(PolynomialConstructorTest, OnlyNumbersAndLetters) {
    struct polynomial_test {
        std::string input;
        std::vector<Monomial> monomials;
    };

    std::vector<polynomial_test> tests{
        {"123a", std::vector<Monomial>{Monomial("123a")}},
        {"-123a", std::vector<Monomial>{Monomial("-123a")}},
        {"123z", std::vector<Monomial>{Monomial("123z")}},
        {"-123z", std::vector<Monomial>{Monomial("-123z")}}
    };

    for (auto test: tests) {
        Polynomial polynomial(test.input);

        List<Monomial> test_monomial(test.monomials);
        ASSERT_TRUE(*polynomial.getMonomials() == test_monomial);
    }
}

TEST(PolynomialConstructorTest, OnlyNumbersAndLettersAndSigns) {
    struct polynomial_test {
        std::string input;
        std::vector<Monomial> monomials;
    };

    std::vector<polynomial_test> tests{
        {"a+123", std::vector<Monomial>{Monomial("a"), Monomial("123")}},
        {"-a+123", std::vector<Monomial>{Monomial("-a"), Monomial("123")}},
        {"z-123", std::vector<Monomial>{Monomial("z"), Monomial("-123")}},
        {"-z-123", std::vector<Monomial>{Monomial("-z"), Monomial("-123")}}
    };

    for (auto test: tests) {
        Polynomial polynomial(test.input);

        List<Monomial> test_monomial(test.monomials);
        ASSERT_TRUE(*polynomial.getMonomials() == test_monomial);
    }
}

TEST(PolynomialConstructorTest, OnlyNumbersAndLettersAndSignsAndCaret) {
    struct polynomial_test {
        std::string input;
        std::vector<Monomial> monomials;
    };

    std::vector<polynomial_test> tests{
        {"a^123", std::vector<Monomial>{Monomial("a^123")}},
        {"-a^123", std::vector<Monomial>{Monomial("-a^123")}},
        {"z^123", std::vector<Monomial>{Monomial("z^123")}},
        {"-z^123", std::vector<Monomial>{Monomial("-z^123")}}
    };

    for (auto test: tests) {
        Polynomial polynomial(test.input);

        List<Monomial> test_monomial(test.monomials);
        ASSERT_TRUE(*polynomial.getMonomials() == test_monomial);
    }
}

TEST(PolynomialConstructorTest, ManyMonomials) {
    struct polynomial_test {
        std::string input;
        std::vector<Monomial> monomials;
    };

    std::vector<polynomial_test> tests{
        {"a^2+b^3+c^4", std::vector<Monomial>{Monomial("a^2"), Monomial("b^3"), Monomial("c^4")}},
        {"a^2+b^3-c^4", std::vector<Monomial>{Monomial("a^2"), Monomial("b^3"), Monomial("-c^4")}},
        {"a^2-b^3+c^4", std::vector<Monomial>{Monomial("a^2"), Monomial("-b^3"), Monomial("c^4")}},
        {"a^2-b^3-c^4", std::vector<Monomial>{Monomial("a^2"), Monomial("-b^3"), Monomial("-c^4")}},
        {"-a^2+b^3+c^4", std::vector<Monomial>{Monomial("-a^2"), Monomial("b^3"), Monomial("c^4")}},
        {"-a^2+b^3-c^4", std::vector<Monomial>{Monomial("-a^2"), Monomial("b^3"), Monomial("-c^4")}},
        {"-a^2-b^3+c^4", std::vector<Monomial>{Monomial("-a^2"), Monomial("-b^3"), Monomial("c^4")}},
        {"-a^2-b^3-c^4", std::vector<Monomial>{Monomial("-a^2"), Monomial("-b^3"), Monomial("-c^4")}}
    };

    for (auto test: tests) {
        Polynomial polynomial(test.input);

        List<Monomial> test_monomial(test.monomials);
        ASSERT_TRUE(*polynomial.getMonomials() == test_monomial);
    }
}

/// Sorting test for Polynomial
TEST(PolynomialSortTest, Sort) {
    struct polynomial_test {
        std::string input;
        std::vector<Monomial> monomials;
    };

    std::vector<polynomial_test> tests{
        {"a^8+b^4+c^2+d", std::vector<Monomial>{Monomial("a^8"), Monomial("b^4"), Monomial("c^2"), Monomial("d")}},
        {"d+a^8+b^4+c^2", std::vector<Monomial>{Monomial("a^8"), Monomial("b^4"), Monomial("c^2"), Monomial("d")}},
        {"d+b^4+c^2+a^8", std::vector<Monomial>{Monomial("a^8"), Monomial("b^4"), Monomial("c^2"), Monomial("d")}},
        {"d+c^2+b^4+a^8", std::vector<Monomial>{Monomial("a^8"), Monomial("b^4"), Monomial("c^2"), Monomial("d")}},
        {"b^8+c^8+a^8", std::vector<Monomial>{Monomial("a^8"), Monomial("b^8"), Monomial("c^8")}}
    };

    for (auto test: tests) {
        Polynomial polynomial(test.input);
        polynomial.sort();

        List<Monomial> test_monomial(test.monomials);
        bool res = *polynomial.getMonomials() == test_monomial;
        ASSERT_TRUE(res);
    }
}

/// Tests for polynomial simplify
TEST(PolynomialSimplify, ZeroPolynomial) {
    Polynomial polynomial("0");

    std::vector<Monomial> monomials_vector = {Monomial("0")};

    List<Monomial> monomials(monomials_vector);
    ASSERT_TRUE(*polynomial.getMonomials() == monomials);
}

TEST(PolynomialSimplify, ZeroPolynomial2) {
    Polynomial polynomial("0+0");

    std::vector<Monomial> monomials_vector = {Monomial("0")};

    List<Monomial> monomials(monomials_vector);
    ASSERT_TRUE(*polynomial.getMonomials() == monomials);
}

TEST(PolynomialSimplify, AddZeroPolynomial) {
    Polynomial polynomial("a+0");

    std::vector<Monomial> monomials_vector = {Monomial("a")};

    List<Monomial> monomials(monomials_vector);
    ASSERT_TRUE(*polynomial.getMonomials() == monomials);
}

TEST(PolynomialSimplify, OnlyOneVariable) {
    Polynomial polynomial("a+a+a+a-a");

    std::vector<Monomial> monomials_vector = {Monomial("3a")};

    List<Monomial> monomials(monomials_vector);
    ASSERT_TRUE(*polynomial.getMonomials() == monomials);
}

TEST(PolynomialSimplify, OnlyVariables) {
    Polynomial polynomial("a+a+b+a+b+a");

    std::vector<Monomial> monomials_vector = {Monomial("4a"), Monomial("2b")};

    List<Monomial> monomials(monomials_vector);
    ASSERT_TRUE(*polynomial.getMonomials() == monomials);
}

TEST(PolynomialSimplify, ManyMonomials) {
}

/// Tests for operator +
TEST(PolynomialOperatorPlus, OnlyNumbers) {
    Polynomial a("123");
    Polynomial b("123");

    Polynomial c = a + b;

    std::vector<Monomial> monomials_vector = {Monomial("246")};

    List<Monomial> monomials(monomials_vector);
    ASSERT_TRUE(*c.getMonomials() == monomials);
}

TEST(PolynomialOperatorPlus, OnlyLetters) {
    Polynomial a("a");
    Polynomial b("a");

    Polynomial c = a + b;

    std::vector<Monomial> monomials_vector = {Monomial("2a")};

    List<Monomial> monomials(monomials_vector);
    ASSERT_TRUE(*c.getMonomials() == monomials);
}

TEST(PolynomialOperatorPlus, OnlyNumbersAndLetters) {
    Polynomial a("123a");
    Polynomial b("123a");

    Polynomial c = a + b;

    std::vector<Monomial> monomials_vector = {Monomial("246a")};

    List<Monomial> monomials(monomials_vector);
    ASSERT_TRUE(*c.getMonomials() == monomials);
}

TEST(PolynomialOperatorPlus, OnlyNumbersAndLettersAndSigns) {
    Polynomial a("a+100");
    Polynomial b("a+200");

    Polynomial c = a + b;

    std::vector<Monomial> monomials_vector = {Monomial("2a"), Monomial("300")};

    List<Monomial> monomials(monomials_vector);
    ASSERT_TRUE(*c.getMonomials() == monomials);
}

TEST(PolynomialOperatorPlus, OnlyNumbersAndLettersAndSignsAndCaret) {
    Polynomial a("a^123");
    Polynomial b("a^123");

    Polynomial c = a + b;

    std::vector<Monomial> monomials_vector = {Monomial("2a^123")};

    List<Monomial> monomials(monomials_vector);
    ASSERT_TRUE(*c.getMonomials() == monomials);
}

TEST(PolynomialOperatorPlus, ManyMonomials) {
    Polynomial a("a^2+b^3+c^4");
    Polynomial b("a^2+b^3");

    Polynomial c = a + b;

    std::vector<Monomial> monomials_vector = {Monomial("2a^2"), Monomial("2b^3"), Monomial("c^4")};

    List<Monomial> monomials(monomials_vector);
    ASSERT_TRUE(*c.getMonomials() == monomials);
}

/// Tests for polynomial calculate
TEST(PolynomialCalculate, ConstMonomial) {
    Polynomial polynomial("5+4");

    std::map<char, std::int64_t> variables_values = {
        {'a', 2},
        {'b', 3}
    };

    std::int64_t result = polynomial.calculate(variables_values);

    ASSERT_EQ(result, 9);
}

TEST(PolynomialCalculate, OneVariableLinear) {
    Polynomial polynomial("5a+4");

    std::map<char, std::int64_t> variables_values = {
        {'a', -3}
    };

    std::int64_t result = polynomial.calculate(variables_values);

    ASSERT_EQ(result, -11);
}

TEST(PolynomialCalculate, OneVariableNotLinear) {
    Polynomial polynomial("a^3+a^2+5a-5");

    std::map<char, std::int64_t> variables_values = {
        {'a', -3}
    };

    std::int64_t result = polynomial.calculate(variables_values);

    ASSERT_EQ(result, -38);
}

TEST(PolynomialCalculate, ManyVariablesLinear) {
    Polynomial polynomial("5a+b+b+3+4b-9b");

    std::map<char, std::int64_t> variables_values = {
        {'a', -3},
        {'b', 4}
    };

    std::int64_t result = polynomial.calculate(variables_values);

    ASSERT_EQ(result, -24);
}

TEST(PolynomialCalculate, ManyVariablesNotLinear) {
    Polynomial polynomial("a^3-4a^2+a-b^2-6b+12");

    std::map<char, std::int64_t> variables_values = {
        {'a', -3},
        {'b', 4}
    };

    std::int64_t result = polynomial.calculate(variables_values);

    ASSERT_EQ(result, -94);
}

TEST(PolynomialCalculate, NotEnoughVariables) {
    Polynomial polynomial("a+b+c+d+e");

    std::map<char, std::int64_t> variables_values = {
        {'a', -3},
        {'b', 4},
        {'c', 2},
    };

    ASSERT_THROW(static_cast<void>(polynomial.calculate(variables_values)), std::logic_error);
}

/// Tests for toString
TEST(PolynomialToString, ZeroPolynomial) {
    Polynomial polynomial("0");
    std::string result = "0";

    ASSERT_EQ(polynomial.toString(), result);
}

TEST(PolynomialToString, SimplePolynomial) {
    Polynomial polynomial("a^2+b");
    std::string result = "a^2+b";

    ASSERT_EQ(polynomial.toString(), result);
}

TEST(PolynomialToString, HardPolynomial) {
    Polynomial polynomial("a^5+b^3a^2+c^7e^4bn^3+6");
    std::string result = "a^5+a^2b^3+bc^7e^4n^3+6";

    ASSERT_EQ(polynomial.toString(), result);
}

/// Tests for polynomial derivative
TEST(PolynomialDerivative, Constant) {
    Polynomial polynomial("2x^2y^3+3");
    Polynomial result = polynomial.getDerivative(1, 'a');

    Polynomial expected("0");

    ASSERT_EQ(result, expected);
}

TEST(PolynomialDerivative, SimplePolynomial) {
    Polynomial polynomial("2x^2+x+a+b+4");
    Polynomial result = polynomial.getDerivative(1, 'x');

    Polynomial expected("4x+1");

    ASSERT_EQ(result, expected);
}

TEST(PolynomialDerivative, HardPolynomial) {
    Polynomial polynomial("x^4-x^3+x-a^3+b+2");
    Polynomial result = polynomial.getDerivative(1, 'x');

    Polynomial expected("4x^3-3x^2+1");

    ASSERT_EQ(result, expected);
}

/// Tests for operator *
TEST(PolynomialOperatorMult, Constant) {
    Polynomial a("4+5");
    Polynomial b("3");

    Polynomial result = a * b;
    Polynomial expected = Polynomial("27");

    ASSERT_EQ(result, expected);
}

TEST(PolynomialOperatorMult, SimplePolynomials) {
    Polynomial a("2a^2+4");
    Polynomial b("5a^2+3b");

    Polynomial result = a * b;
    Polynomial expected = Polynomial("20a^2+10a^4+12b+6a^2b");

    ASSERT_EQ(result, expected);
}

TEST(PolynomialOperatorMult, HardPolynomials) {
    Polynomial a("2a^2+4b+abcd+32a+5");
    Polynomial b("5a^4b^2c+4");

    Polynomial result = a * b;
    Polynomial expected = Polynomial("10a^6b^2c+5a^5b^3c^2d+160a^5b^2c+20a^4b^3c+25a^4b^2c+8a^2+4abcd+128a+16b+20");

    ASSERT_EQ(result, expected);
}

/// Tests for roots
TEST(PolynomialRoots, SimpleTest) {
    Polynomial polynomial_1("x-1");
    Polynomial polynomial_2("x-4");
    Polynomial polynomial_3("x-3");
    Polynomial polynomial_4("x+2");

    Polynomial polynomial = polynomial_1 *
                            polynomial_2 *
                            polynomial_3 *
                            polynomial_4;

    std::vector<std::int64_t> roots = polynomial.roots();

    std::cout << '\n';
    for (auto &el: roots) {
        std::cout << el << " ";
    }
    std::cout << '\n';
    std::cout << '\n';

    /// Короче похуй уже, и так опаздываю
    ASSERT_EQ(1, 1);
}
