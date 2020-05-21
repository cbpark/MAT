#ifndef MAT_SRC_MAOS_H_
#define MAT_SRC_MAOS_H_

#include "momentum.h"

#include <utility>
#include <vector>

namespace mat {
double mt2(const FourMomentum& p1, const FourMomentum& p2, double metx,
           double mety, Mass mInvis);

std::vector<std::pair<FourMomentum, FourMomentum>> maos(
    const FourMomentum& p1, const FourMomentum& p2, double metx, double mety,
    Mass mMother, Mass mInvis);
}  // namespace mat

#endif  // MAT_SRC_MAOS_H_
