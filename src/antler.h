/*
 *  Copyright (c) 2020 Chan Beom Park <cbpark@gmail.com>
 */

#ifndef MAT_SRC_ANTLER_H_
#define MAT_SRC_ANTLER_H_

#include <vector>
#include "momentum.h"

namespace mat {
/**
 * @param q the four-momentum of the resonance.
 * @param p1 the four-momentum of the first visible particle.
 * @param p2 the four-momentum of the second visible particle.
 * @param mA the mass of the intermediate particle.
 * @param mB the mass of the invisible particle in the final state.
 */
double deltaAT(const FourMomentum &q, const FourMomentum &p1,
               const FourMomentum &p2, const Mass &mA, const Mass &mB);

/**
 * @param p1 the four-momentum of the first visible particle.
 * @param p2 the four-momentum of the second visible particle.
 * @param metx the x component of the missing transverse energy.
 * @param mety the y component of the missing transverse energy.
 * @param qz a guess value for the longitudinal momentum of the resonance.
 * @param mA the mass of the intermediate particle.
 * @param mB the mass of the invisible particle in the final state.
 */
std::vector<double> mAT(const FourMomentum &p1, const FourMomentum &p2,
                        double metx, double mety, double qz, const Mass &mA,
                        const Mass &mB);

/**
 * @param p1 the four-momentum of the first visible particle.
 * @param p2 the four-momentum of the second visible particle.
 * @param metx the x component of the missing transverse energy.
 * @param mety the y component of the missing transverse energy.
 * @param mA the mass of the intermediate particle.
 * @param mB the mass of the invisible particle in the final state.
 */
std::vector<double> mATmaos(const FourMomentum &p1, const FourMomentum &p2,
                            double metx, double mety, const Mass &mA,
                            const Mass &mB);
}  // namespace mat

#endif  // MAT_SRC_ANTLER_H_
