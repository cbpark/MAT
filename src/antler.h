#ifndef MAT_SRC_ANTLER_H_
#define MAT_SRC_ANTLER_H_

#include "momentum.h"

#include <vector>

namespace mat {
double deltaAT(const mat::FourMomentum& q, const mat::FourMomentum& p1,
               const mat::FourMomentum& p2, Mass mA, Mass mB);

std::vector<double> mAT(const mat::FourMomentum& p1,
                        const mat::FourMomentum& p2, double metx, double mety,
                        double qz, Mass mA, Mass mB);

std::vector<double> mATmaos(const mat::FourMomentum& p1,
                            const mat::FourMomentum& p2, double metx,
                            double mety, Mass mA, Mass mB);
}  // namespace mat

#endif  // MAT_SRC_ANTLER_H_
