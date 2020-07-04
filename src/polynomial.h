#ifndef MAT_SRC_POLYNOMIAL_H_
#define MAT_SRC_POLYNOMIAL_H_

#include <array>
#include <functional>
#include <vector>

namespace mat {
using Polynomial = std::function<double(double)>;

std::vector<double> quarticEqSol(Polynomial f, const std::array<double, 4>& xs,
                                 double eps);
}  // namespace mat

#endif  // MAT_SRC_POLYNOMIAL_H_
