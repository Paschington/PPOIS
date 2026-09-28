#include "Polynomial.h"
#include <cmath>
#include <stdexcept>

namespace {
    const double kEpsilon = 1e-9;

    bool IsZero(double v) {
        return v < kEpsilon && v > -kEpsilon;
    }

    double Abs(double v) {
        return (v < 0.0) ? -v : v;
    }
}

Polynomial::Polynomial(int degree, const double* coeffs) {
    if (degree < 0) {
        throw std::invalid_argument("Polynomial degree must be non-negative");
    }
    if (coeffs == nullptr) {
        throw std::invalid_argument("Coefficients array must not be null");
    }
    this->degree = degree;
    this->coeffs = new double[degree + 1];
    for (int i = 0; i <= degree; i++) {
        this->coeffs[i] = coeffs[i];
    }
    Trim();
}

Polynomial::Polynomial() {
    degree = 0;
    coeffs = new double[1];
    coeffs[0] = 0.0;
}

Polynomial::Polynomial(const Polynomial& other) {
    degree = other.degree;
    coeffs = new double[degree + 1];
    for (int i = 0; i <= degree; i++) {
        coeffs[i] = other.coeffs[i];
    }
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this == &other) {
        return *this;
    }
    double* newCoeffs = new double[other.degree + 1];
    for (int i = 0; i <= other.degree; i++) {
        newCoeffs[i] = other.coeffs[i];
    }
    delete[] coeffs;
    coeffs = newCoeffs;
    degree = other.degree;
    return *this;
}

Polynomial::~Polynomial() {
    delete[] coeffs;
}

void Polynomial::Trim() {
    while (degree > 0 && IsZero(coeffs[degree])) {
        degree--;
    }
}

int Polynomial::Degree() const {
    return degree;
}

double Polynomial::operator[](int power) const {
    if (power < 0 || power > degree) {
        return 0.0;
    }
    return coeffs[power];
}

double Polynomial::operator()(double x) const {
    double result = 0.0;
    for (int i = degree; i >= 0; i--) {
        result = result * x + coeffs[i];
    }
    return result;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    int newDegree = (degree > other.degree) ? degree : other.degree;
    double* newCoeffs = new double[newDegree + 1];

    for (int i = 0; i <= newDegree; i++) {
        double a = (i <= degree) ? coeffs[i] : 0.0;
        double b = (i <= other.degree) ? other.coeffs[i] : 0.0;
        newCoeffs[i] = a + b;
    }

    delete[] coeffs;
    coeffs = newCoeffs;
    degree = newDegree;
    Trim();
    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
    int newDegree = (degree > other.degree) ? degree : other.degree;
    double* newCoeffs = new double[newDegree + 1];

    for (int i = 0; i <= newDegree; i++) {
        double a = (i <= degree) ? coeffs[i] : 0.0;
        double b = (i <= other.degree) ? other.coeffs[i] : 0.0;
        newCoeffs[i] = a - b;
    }

    delete[] coeffs;
    coeffs = newCoeffs;
    degree = newDegree;
    Trim();
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
    int newDegree = degree + other.degree;
    double* newCoeffs = new double[newDegree + 1];
    for (int i = 0; i <= newDegree; i++) {
        newCoeffs[i] = 0.0;
    }

    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= other.degree; j++) {
            newCoeffs[i + j] += coeffs[i] * other.coeffs[j];
        }
    }

    delete[] coeffs;
    coeffs = newCoeffs;
    degree = newDegree;
    Trim();
    return *this;
}

Polynomial& Polynomial::operator/=(const Polynomial& other) {
    bool divisorIsZero = (other.degree == 0) && IsZero(other.coeffs[0]);
    if (divisorIsZero) {
        throw std::invalid_argument("Division by zero polynomial");
    }

    int remainderDegree = degree;
    double* remainder = new double[degree + 1];
    for (int i = 0; i <= degree; i++) {
        remainder[i] = coeffs[i];
    }

    int quotientDegree = (degree - other.degree >= 0) ? (degree - other.degree) : 0;
    double* quotient = new double[quotientDegree + 1];
    for (int i = 0; i <= quotientDegree; i++) {
        quotient[i] = 0.0;
    }

    while (remainderDegree >= other.degree) {
        bool remainderIsZero = true;
        for (int i = 0; i <= remainderDegree; i++) {
            if (!IsZero(remainder[i])) {
                remainderIsZero = false;
                break;
            }
        }
        if (remainderIsZero) break;

        double leadCoeff = remainder[remainderDegree] / other.coeffs[other.degree];
        int shift = remainderDegree - other.degree;
        quotient[shift] = leadCoeff;

        for (int i = 0; i <= other.degree; i++) {
            remainder[shift + i] -= leadCoeff * other.coeffs[i];
        }

        while (remainderDegree > 0 && IsZero(remainder[remainderDegree])) {
            remainderDegree--;
        }
    }

    delete[] remainder;
    delete[] coeffs;
    coeffs = quotient;
    degree = quotientDegree;
    Trim();
    return *this;
}

Polynomial Polynomial::Remainder(const Polynomial& other) const {
    bool divisorIsZero = (other.degree == 0) && IsZero(other.coeffs[0]);
    if (divisorIsZero) {
        throw std::invalid_argument("Division by zero polynomial");
    }

    int remainderDegree = degree;
    double* remainder = new double[degree + 1];
    for (int i = 0; i <= degree; i++) {
        remainder[i] = coeffs[i];
    }

    while (remainderDegree >= other.degree) {
        bool remainderIsZero = true;
        for (int i = 0; i <= remainderDegree; i++) {
            if (!IsZero(remainder[i])) {
                remainderIsZero = false;
                break;
            }
        }
        if (remainderIsZero) break;

        double leadCoeff = remainder[remainderDegree] / other.coeffs[other.degree];
        int shift = remainderDegree - other.degree;

        for (int i = 0; i <= other.degree; i++) {
            remainder[shift + i] -= leadCoeff * other.coeffs[i];
        }

        while (remainderDegree > 0 && IsZero(remainder[remainderDegree])) {
            remainderDegree--;
        }
    }

    Polynomial result(remainderDegree, remainder);
    delete[] remainder;
    return result;
}

bool Polynomial::operator==(const Polynomial& other) const {
    if (degree != other.degree) return false;
    for (int i = 0; i <= degree; i++) {
        if (!IsZero(coeffs[i] - other.coeffs[i])) return false;
    }
    return true;
}

bool Polynomial::operator!=(const Polynomial& other) const {
    return !(*this == other);
}

Polynomial operator+(Polynomial lhs, const Polynomial& rhs) { lhs += rhs; return lhs; }
Polynomial operator-(Polynomial lhs, const Polynomial& rhs) { lhs -= rhs; return lhs; }
Polynomial operator*(Polynomial lhs, const Polynomial& rhs) { lhs *= rhs; return lhs; }
Polynomial operator/(Polynomial lhs, const Polynomial& rhs) { lhs /= rhs; return lhs; }

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    if (p.Degree() == 0 && IsZero(p[0])) {
        os << "0";
        return os;
    }

    bool first = true;
    for (int i = p.Degree(); i >= 0; i--) {
        double c = p[i];
        if (IsZero(c)) continue;

        if (first) {
            if (c < 0) os << "-";
        }
        else {
            os << (c < 0 ? " - " : " + ");
        }

        double absC = Abs(c);

        if (i == 0) {
            os << absC;
        }
        else if (absC == 1.0) {
            os << "x";
            if (i != 1) os << "^" << i;
        }
        else {
            os << absC << "x";
            if (i != 1) os << "^" << i;
        }

        first = false;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Polynomial& p) {
    int degree;
    if (!(is >> degree)) {
        return is;
    }
    if (degree < 0) {
        is.setstate(std::ios::failbit);
        return is;
    }

    double* coeffs = new double[degree + 1];
    for (int i = 0; i <= degree; i++) {
        if (!(is >> coeffs[i])) {
            delete[] coeffs;
            return is;
        }
    }

    p = Polynomial(degree, coeffs);
    delete[] coeffs;
    return is;
}
