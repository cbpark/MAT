#include "antler.h"
#include "maos.h"
#include "matrix.h"
#include "momentum.h"
#include "polynomial.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <vector>

double mat::deltaAT(const mat::FourMomentum& q, const mat::FourMomentum& p1,
                    const mat::FourMomentum& p2, double mA, double mB) {
    const double qp1 = q.dot(p1);
    const double qp2 = q.dot(p2);
    const double qSq = q.m2();

    const double deltaM = mA * mA - mB * mB;
    const double mV1sq = p1.m2();
    const double mV2sq = p2.m2();

    const double a00 = 2 * mA * mA;
    const double a01 = deltaM + mV1sq;
    const double a02 = -deltaM + 2 * qp2 - mV2sq;
    const double a03 = qSq;

    const double a10 = a01;
    const double a11 = 2 * mV1sq;
    const double a12 = 2 * p1.dot(p2);
    const double a13 = 2 * qp1;

    const double a20 = a02;
    const double a21 = a12;
    const double a22 = 2 * mV2sq;
    const double a23 = 2 * qp2;

    const double a30 = a03;
    const double a31 = a13;
    const double a32 = a23;
    const double a33 = 2 * qSq;

    const auto m1 = mat::Matrix22(a00, a01, a10, a11);
    const auto m1_ = mat::Matrix22(a22, a23, a32, a33);

    const auto m2 = mat::Matrix22(a00, a02, a10, a12);
    const auto m2_ = mat::Matrix22(a21, a23, a31, a33);

    const auto m3 = mat::Matrix22(a00, a03, a10, a13);
    const auto m3_ = mat::Matrix22(a21, a22, a31, a32);

    const auto m4 = mat::Matrix22(a01, a02, a11, a12);
    const auto m4_ = mat::Matrix22(a20, a23, a30, a33);

    const auto m5 = mat::Matrix22(a01, a03, a11, a13);
    const auto m5_ = mat::Matrix22(a20, a22, a30, a32);

    const auto m6 = mat::Matrix22(a02, a03, a12, a13);
    const auto m6_ = mat::Matrix22(a20, a21, a30, a31);

    return m1.det() * m1_.det() - m2.det() * m2_.det() + m3.det() * m3_.det() +
           m4.det() * m4_.det() - m5.det() * m5_.det() + m6.det() * m6_.det();
}

auto deltaATFunc(const mat::FourMomentum& p1, const mat::FourMomentum& p2,
                 double mA, double mB, double qx, double qy, double qz) {
    return [=](double e) {
        auto q = mat::FourMomentum(e, qx, qy, qz);
        return mat::deltaAT(q, p1, p2, mA, mB) / (std::pow(mA, 8) + 1.0e-12);
    };
}

double sqrt0(double x) { return x < 0 ? 1.0e+10 : std::sqrt(x); }

std::vector<double> mat::mAT(const mat::FourMomentum& p1,
                             const mat::FourMomentum& p2, double metx,
                             double mety, double qz, double mA, double mB) {
    const double qx = p1.px() + p2.px() + metx;
    const double qy = p1.py() + p2.py() + mety;
    auto f = deltaATFunc(p1, p2, mA, mB, qx, qy, qz);
    const std::array<double, 4> inps = {mA, 10 * mA, 100 * mA, 1000 * mA};
    auto sols = mat::quarticEqSol(f, inps, 1.0e-3);

    const double q2 = qx * qx + qy * qy + qz * qz;
    std::transform(sols.begin(), sols.end(), sols.begin(),
                   [=](double eT) { return sqrt0(eT * eT - q2); });

    // remove zero solutions.
    sols.erase(std::remove_if(sols.begin(), sols.end(),
                              [](double s) { return std::abs(s) < 1.0e-4; }),
               sols.end());
    return sols;
}

std::vector<double> mat::mATmaos(const mat::FourMomentum& p1,
                                 const mat::FourMomentum& p2, double metx,
                                 double mety, double mA, double mB) {
    const double qz_ = p1.pz() + p2.pz();
    std::vector<double> qz;
    auto maosSols = mat::maos(p1, p2, metx, mety, mA, mB);
    for (const auto& s : maosSols) {
        qz.push_back(qz_ + s.first.pz() + s.second.pz());
    }

    std::vector<double> mATs;
    for (const auto& qzSol : qz) {
        const auto mATs_ = mat::mAT(p1, p2, metx, mety, qzSol, mA, mB);
        mATs.insert(mATs.end(), mATs_.cbegin(), mATs_.cend());
    }
    std::sort(mATs.begin(), mATs.end());
    return mATs;
}
