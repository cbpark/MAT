/*
 *  Copyright (c) 2020 Chan Beom Park <cbpark@gmail.com>
 */

#include <iostream>
#include <string>
#include <vector>
#include "antler.h"

void printVar(const std::string &varname, const std::vector<double> &ms) {
    std::cout << varname << " = ";
    for (const auto &m : ms) { std::cout << m << "  "; }
    std::cout << '\n';
}

int main() {
    /**
     *  For X --> A1 + A2 --> v1 (p1) B1 + v2 (p2) B2,
     *  where v1 and v2 are visible, and B1 and B2 are invisible particles.
     */
    const mat::FourMomentum p1{351.49241, 22.24011, 26.391145, -324.80662};
    const mat::FourMomentum p2{224.89580, 14.16262, -48.55755, 196.35579};
    const double metx = -36.40273, mety = 22.16641;
    const mat::Mass mA{173.0};  // m_{A1} = m_{A2} = m_{A}
    const mat::Mass mB{0};      // m_{B1} = m_{B2} = m_{B}

    // the longitudinal momentum of X is set to be 0.
    const auto mAT0 = mat::mAT(p1, p2, metx, mety, 0.0, mA, mB);
    printVar("mAT(0)", mAT0);

    // the true longitudinal momentum of X (qz).
    const double qz = -172.89418;
    const auto mATtrue = mat::mAT(p1, p2, metx, mety, qz, mA, mB);
    printVar("mAT(Qz)", mATtrue);

    // the longitudinal momentum of X is obtained by the MAOS method.
    const auto mATmaos = mat::mATmaos(p1, p2, metx, mety, mA, mB);
    printVar("mAT(maos)", mATmaos);
}
