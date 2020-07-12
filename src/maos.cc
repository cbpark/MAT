/*
 *  Copyright (c) 2020 Chan Beom Park <cbpark@gmail.com>
 */

#include "maos.h"

#include <cmath>
#include <utility>
#include <vector>

#include "lester_mt2_bisect.h"
#include "momentum.h"

using FourMomentum = mat::FourMomentum;
using Mass = mat::Mass;

double mat::mt2(const FourMomentum &p1, const FourMomentum &p2, double metx,
                double mety, Mass mInvis) {
    const double mVis1 = p1.m();
    const double mVis2 = p2.m();
    asymm_mt2_lester_bisect::disableCopyrightMessage();
    return asymm_mt2_lester_bisect::get_mT2(mVis1, p1.px(), p1.py(), mVis2,
                                            p2.px(), p2.py(), metx, mety,
                                            mInvis.value, mInvis.value);
}

std::vector<FourMomentum> onShellSolution(const FourMomentum &vis, double pChix,
                                          double pChiy, Mass mMother,
                                          Mass mInvis) {
    const double lambda =
        0.5 * (mMother.square() - vis.m2() - mInvis.square()) +
        vis.px() * pChix + vis.py() * pChiy;
    const double etVis = vis.transverseEnergy();
    const double etChi =
        std::sqrt(pChix * pChix + pChiy * pChiy + mInvis.square());

    const double a = etVis * etVis;
    const double b = lambda * vis.pz();

    double det = lambda * lambda - std::pow(etVis * etChi, 2);
    if (det < 0 && det > -1.0e-4) { det = 0; }

    std::vector<FourMomentum> sols;
    if (det >= 0) {
        const double c = vis.e() * std::sqrt(det);
        double pChiz = (b + c) / a;
        double eChi = std::sqrt(etChi * etChi + pChiz * pChiz);
        sols.push_back(FourMomentum(eChi, pChix, pChiy, pChiz));

        pChiz = (b - c) / a;
        eChi = std::sqrt(etChi * etChi + pChiz * pChiz);
        sols.push_back(FourMomentum(eChi, pChix, pChiy, pChiz));
    }

    return sols;
}

std::vector<std::pair<FourMomentum, FourMomentum>> mat::maos(
    const FourMomentum &p1, const FourMomentum &p2, double metx, double mety,
    Mass mMother, Mass mInvis) {
    const double mt2 = mat::mt2(p1, p2, metx, mety, mInvis);
    auto mt2sol =
        ben_findsols(mt2, p1.px(), p1.py(), p1.m(), mInvis.value, p2.px(),
                     p2.py(), metx, mety, p2.m(), mInvis.value);
    const double pChi1x = mt2sol.first;
    const double pChi1y = mt2sol.second;
    const double pChi2x = metx - pChi1x;
    const double pChi2y = mety - pChi1y;

    auto sols1 = onShellSolution(p1, pChi1x, pChi1y, mMother, mInvis);
    auto sols2 = onShellSolution(p2, pChi2x, pChi2y, mMother, mInvis);

    std::vector<std::pair<FourMomentum, FourMomentum>> maosSols;
    if (!sols1.empty() && !sols2.empty()) {
        for (const auto &s1 : sols1) {
            for (const auto &s2 : sols2) {
                maosSols.push_back(std::make_pair(s1, s2));
            }
        }
    }
    return maosSols;
}
