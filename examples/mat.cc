#include "polynomial.h"

#include <array>
#include <iostream>

double func1(double x) {
    const double a = 3;
    const double b = 6;
    const double c = -123;
    const double d = -126;
    const double e = 1080;
    double x2 = x * x, x3 = x2 * x, x4 = x3 * x;
    return a * x4 + b * x3 + c * x2 + d * x + e;
}

int main() {
    std::cout << "hello, world!\n";
    std::array<double, 4> xs = {1, 10, 100, 1000};
    auto coeff = mat::quarticEqSol(func1, xs, 1.0e-8);
    for (const auto& c : coeff) { std::cout << c << '\n'; }
}
