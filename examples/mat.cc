#include "antler.h"
#include "momentum.h"

#include <array>
#include <iostream>

int main() {
    const auto pV1 =
        mat::FourMomentum(351.49241, 22.24011, 26.391145, -324.80662);
    const auto pV2 =
        mat::FourMomentum(224.89580, 14.16262, -48.55755, 196.35579);
    const double qx = 0, qy = 0, qz = -172.89418;
    const double mA = 173.0, mB = 0;

    const auto mAT0 = mat::mAT(pV1, pV2, mA, mB, qx, qy, 0);
    std::cout << "mAT(0):   ";
    for (const auto& m : mAT0) { std::cout << m << "  "; }
    std::cout << '\n';

    const auto mAT = mat::mAT(pV1, pV2, mA, mB, qx, qy, qz);
    std::cout << "mAT(Q_z): ";
    for (const auto& m : mAT) { std::cout << m << "  "; }
    std::cout << '\n';
}
