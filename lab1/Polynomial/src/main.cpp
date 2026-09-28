#include <iostream>
#include <limits>
#include "Polynomial.h"

namespace {
    void ClearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    Polynomial ReadPolynomial() {
        int degree;
        std::cout << "Enter polynomial degree: ";
        while (!(std::cin >> degree) || degree < 0) {
            std::cout << "Invalid degree. Try again: ";
            ClearInput();
        }

        double* coeffs = new double[degree + 1];
        std::cout << "Enter " << (degree + 1)
            << " coefficient(s) (from x^0 to x^" << degree << "): ";
        for (int i = 0; i <= degree; i++) {
            while (!(std::cin >> coeffs[i])) {
                std::cout << "Invalid coefficient. Try again: ";
                ClearInput();
            }
        }

        Polynomial p(degree, coeffs);
        delete[] coeffs;
        return p;
    }
}

int main() {
    while (true) {
        std::cout << "\n-- Polynomial --\n"
            << "1. Enter and print a polynomial\n"
            << "2. Evaluate at a point\n"
            << "3. Add two polynomials\n"
            << "4. Subtract two polynomials\n"
            << "5. Multiply two polynomials\n"
            << "6. Divide two polynomials\n"
            << "0. Exit\n> ";

        int choice;
        if (!(std::cin >> choice)) {
            ClearInput();
            std::cout << "Invalid menu choice." << std::endl;
            continue;
        }
        if (choice == 0) break;

        try {
            if (choice == 1) {
                Polynomial p = ReadPolynomial();
                std::cout << "Polynomial (degree " << p.Degree() << "): " << p << std::endl;
            }
            else if (choice == 2) {
                Polynomial p = ReadPolynomial();
                double x;
                std::cout << "x = ";
                while (!(std::cin >> x)) {
                    std::cout << "Invalid x. Try again: ";
                    ClearInput();
                }
                std::cout << "Value: " << p(x) << std::endl;
            }
            else if (choice >= 3 && choice <= 6) {
                std::cout << "First polynomial:\n";
                Polynomial p1 = ReadPolynomial();
                std::cout << "Second polynomial:\n";
                Polynomial p2 = ReadPolynomial();

                Polynomial result;
                if (choice == 3) {
                    result = p1 + p2;
                    std::cout << "Result: " << result << std::endl;
                }
                else if (choice == 4) {
                    result = p1 - p2;
                    std::cout << "Result: " << result << std::endl;
                }
                else if (choice == 5) {
                    result = p1 * p2;
                    std::cout << "Result: " << result << std::endl;
                }
                else {
                    result = p1 / p2;
                    Polynomial rem = p1.Remainder(p2);
                    std::cout << "Quotient:  " << result << std::endl;
                    std::cout << "Remainder: " << rem << std::endl;
                }
            }
            else {
                std::cout << "Invalid menu choice." << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}
