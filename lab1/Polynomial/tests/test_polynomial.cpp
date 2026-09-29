#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Polynomial.h"

TEST_CASE("Default polynomial is zero", "[Polynomial]") {
    Polynomial p;
    REQUIRE(p.Degree() == 0);
    REQUIRE(p[0] == 0.0);
}

TEST_CASE("Polynomial is created with coefficients", "[Polynomial]") {
    double c[] = {1.0, 2.0, 3.0};
    Polynomial p(2, c);
    REQUIRE(p.Degree() == 2);
    REQUIRE(p[0] == 1.0);
    REQUIRE(p[1] == 2.0);
    REQUIRE(p[2] == 3.0);
}

TEST_CASE("Polynomial evaluate at x=1", "[Polynomial]") {
    double c[] = {1.0, 2.0, 3.0};
    Polynomial p(2, c);
    REQUIRE(p(1.0) == 6.0);
}

TEST_CASE("Polynomial evaluate at x=2", "[Polynomial]") {
    double c[] = {1.0, 2.0, 3.0};
    Polynomial p(2, c);
    REQUIRE(p(2.0) == 17.0);
}

TEST_CASE("Polynomial evaluate at x=0", "[Polynomial]") {
    double c[] = {5.0, 2.0, 3.0};
    Polynomial p(2, c);
    REQUIRE(p(0.0) == 5.0);
}

TEST_CASE("Polynomial out-of-range index returns 0", "[Polynomial]") {
    double c[] = {1.0, 2.0};
    Polynomial p(1, c);
    REQUIRE(p[10] == 0.0);
    REQUIRE(p[-1] == 0.0);
}

TEST_CASE("Polynomial addition", "[Polynomial]") {
    double a[] = {1.0, 2.0};
    double b[] = {3.0, 4.0};
    Polynomial pa(1, a), pb(1, b);
    Polynomial sum = pa + pb;
    REQUIRE(sum[0] == 4.0);
    REQUIRE(sum[1] == 6.0);
}

TEST_CASE("Polynomial addition with different degrees", "[Polynomial]") {
    double a[] = {1.0};
    double b[] = {0.0, 0.0, 1.0};
    Polynomial pa(0, a), pb(2, b);
    Polynomial sum = pa + pb;
    REQUIRE(sum.Degree() == 2);
    REQUIRE(sum[0] == 1.0);
    REQUIRE(sum[2] == 1.0);
}

TEST_CASE("Polynomial subtraction", "[Polynomial]") {
    double a[] = {5.0, 3.0};
    double b[] = {1.0, 1.0};
    Polynomial pa(1, a), pb(1, b);
    Polynomial d = pa - pb;
    REQUIRE(d[0] == 4.0);
    REQUIRE(d[1] == 2.0);
}

TEST_CASE("Polynomial multiplication", "[Polynomial]") {
    double a[] = {1.0, 1.0};
    double b[] = {-1.0, 1.0};
    Polynomial pa(1, a), pb(1, b);
    Polynomial prod = pa * pb;
    REQUIRE(prod.Degree() == 2);
    REQUIRE(prod[0] == -1.0);
    REQUIRE(prod[1] == 0.0);
    REQUIRE(prod[2] == 1.0);
}

TEST_CASE("Polynomial division", "[Polynomial]") {
    double a[] = {-1.0, 0.0, 1.0};
    double b[] = {-1.0, 1.0};
    Polynomial pa(2, a), pb(1, b);
    Polynomial q = pa / pb;
    REQUIRE(q.Degree() == 1);
    REQUIRE(q[0] == 1.0);
    REQUIRE(q[1] == 1.0);
}

TEST_CASE("Polynomial division by zero throws", "[Polynomial]") {
    double a[] = {1.0, 1.0};
    Polynomial pa(1, a);
    Polynomial zero;
    REQUIRE_THROWS_AS(pa / zero, std::invalid_argument);
}

TEST_CASE("Polynomial remainder", "[Polynomial]") {
    double a[] = {1.0, 0.0, 1.0};
    double b[] = {1.0, 1.0};
    Polynomial pa(2, a), pb(1, b);
    Polynomial r = pa.Remainder(pb);
    REQUIRE(r.Degree() == 0);
    REQUIRE(r[0] == 2.0);
}

TEST_CASE("Polynomials are equal", "[Polynomial]") {
    double a[] = {1.0, 2.0};
    Polynomial p1(1, a), p2(1, a);
    REQUIRE(p1 == p2);
}

TEST_CASE("Polynomials are not equal", "[Polynomial]") {
    double a[] = {1.0, 2.0};
    double b[] = {1.0, 3.0};
    Polynomial p1(1, a), p2(1, b);
    REQUIRE(p1 != p2);
}

TEST_CASE("Polynomial copy constructor", "[Polynomial]") {
    double a[] = {1.0, 2.0, 3.0};
    Polynomial p1(2, a);
    Polynomial p2(p1);
    REQUIRE(p1 == p2);
}

TEST_CASE("Polynomial assignment", "[Polynomial]") {
    double a[] = {1.0, 2.0, 3.0};
    Polynomial p1(2, a);
    Polynomial p2;
    p2 = p1;
    REQUIRE(p1 == p2);
}

TEST_CASE("Polynomial self-assignment", "[Polynomial]") {
    double a[] = {1.0, 2.0};
    Polynomial p(1, a);
    p = p;
    REQUIRE(p[0] == 1.0);
}

TEST_CASE("Polynomial trims leading zeros", "[Polynomial]") {
    double a[] = {1.0, 2.0, 0.0, 0.0};
    Polynomial p(3, a);
    REQUIRE(p.Degree() == 1);
}