#include "antler.h"
#include "momentum.h"

#include <iostream>
#include <string>
#include <vector>

void printVar(const std::string &varname, const std::vector<double> &ms) {
    std::cout << varname << " = ";
    for (const auto &m : ms) { std::cout << m << "  "; }
    std::cout << '\n';
}

int main() {
    const auto pV1 =
        mat::FourMomentum(351.49241, 22.24011, 26.391145, -324.80662);
    const auto pV2 =
        mat::FourMomentum(224.89580, 14.16262, -48.55755, 196.35579);
    const double metx = -36.40273, mety = 22.16641;
    const auto mA = mat::Mass(173.0), mB = mat::Mass(0);

    const auto mAT0 = mat::mAT(pV1, pV2, metx, mety, 0, mA, mB);
    printVar("mAT(0)", mAT0);

    // the true longitudinal momentum of the resonance
    const double qz = -172.89418;
    const auto mATtrue = mat::mAT(pV1, pV2, metx, mety, qz, mA, mB);
    printVar("mAT(Qz)", mATtrue);

    const auto mATmaos = mat::mATmaos(pV1, pV2, metx, mety, mA, mB);
    printVar("mAT(maos)", mATmaos);
}
