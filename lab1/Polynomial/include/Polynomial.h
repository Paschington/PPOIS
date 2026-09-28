#pragma once
#include <iostream>

class Polynomial {
public:
    Polynomial(int degree, const double* coeffs);
    Polynomial();
    Polynomial(const Polynomial& other);
    Polynomial& operator=(const Polynomial& other);
    ~Polynomial();

    int Degree() const;
    double operator[](int power) const;
    double operator()(double x) const;

    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);
    Polynomial& operator/=(const Polynomial& other);

    Polynomial Remainder(const Polynomial& other) const;

    bool operator==(const Polynomial& other) const;
    bool operator!=(const Polynomial& other) const;

private:
    int degree;
    double* coeffs;

    void Trim();
};

Polynomial operator+(Polynomial lhs, const Polynomial& rhs);
Polynomial operator-(Polynomial lhs, const Polynomial& rhs);
Polynomial operator*(Polynomial lhs, const Polynomial& rhs);
Polynomial operator/(Polynomial lhs, const Polynomial& rhs);

std::ostream& operator<<(std::ostream& os, const Polynomial& p);
std::istream& operator>>(std::istream& is, Polynomial& p);