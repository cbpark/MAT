#include "polynomial.h"

#include <array>
#include <functional>
#include <vector>

std::array<double, 5> coeffQuartic(std::function<double(double)> f,
                                   const std::array<double, 4>& xs) {
    const double f1 = f(xs[0]);
    const double f2 = f(xs[1]);
    const double f3 = f(xs[2]);
    const double f4 = f(xs[3]);

    const double d1 =
        xs[0] * (xs[1] - xs[0]) * (xs[2] - xs[0]) * (xs[3] - xs[0]);
    const double d2 =
        xs[1] * (xs[1] - xs[0]) * (xs[2] - xs[1]) * (xs[3] - xs[1]);
    const double d3 =
        xs[2] * (xs[2] - xs[0]) * (xs[2] - xs[1]) * (xs[3] - xs[2]);
    const double d4 =
        xs[3] * (xs[3] - xs[0]) * (xs[3] - xs[1]) * (xs[3] - xs[2]);

    const double p12 = xs[0] * xs[1];
    const double p13 = xs[0] * xs[2];
    const double p14 = xs[0] * xs[3];
    const double p23 = xs[1] * xs[2];
    const double p24 = xs[1] * xs[3];
    const double p34 = xs[2] * xs[3];
    const double p1234 = p12 * p34;

    const double e = f(0);

    const double a = -f1 / d1 + f2 / d2 - f3 / d3 + f4 / d4 + e / p1234;

    const double b =
        f1 * (xs[1] + xs[2] + xs[3]) / d1 - f2 * (xs[3] + xs[2] + xs[0]) / d2 +
        f3 * (xs[3] + xs[1] + xs[0]) / d3 - f4 * (xs[2] + xs[1] + xs[0]) / d4 -
        e * (xs[0] + xs[1] + xs[2] + xs[3]) / p1234;

    const double c = -f1 * (p34 + p24 + p23) / d1 +
                     f2 * (p34 + p14 + p13) / d2 - f3 * (p24 + p14 + p12) / d3 +
                     f4 * (p23 + p13 + p12) / d4 +
                     e * (p34 + p24 + p14 + p23 + p13 + p12) / p1234;

    const double d =
        f1 * xs[1] * p34 / d1 - f2 * xs[2] * p14 / d2 + f3 * xs[3] * p12 / d3 -
        f4 * xs[0] * p23 / d4 -
        e * (xs[1] * p34 + xs[2] * p14 + xs[3] * p12 + xs[0] * p23) / p1234;

    return {e, d, c, b, a};
}

std::vector<double> quarticEqSol(std::function<double(double)> f,
                                 const std::array<double, 4>& xs, double eps) {
    return {0};
}
