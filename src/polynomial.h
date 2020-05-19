#ifndef MAT_SRC_POLYNOMIAL_H_
#define MAT_SRC_POLYNOMIAL_H_

#include <array>
#include <functional>
#include <vector>

std::vector<double> quarticEqSol(std::function<double(double)> f,
                                 const std::array<double, 4>& xs, double eps);

#endif  // MAT_SRC_POLYNOMIAL_H_
