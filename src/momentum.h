#ifndef MAT_SRC_MOMENTUM_H_
#define MAT_SRC_MOMENTUM_H_

namespace mat {

class FourMomentum {
private:
    double t_, x_, y_, z_;

public:
    FourMomentum() = delete;
    FourMomentum(double t, double x, double y, double z)
        : t_(t), x_(x), y_(y), z_(z) {}

    double e() const { return t_; }
    double px() const { return x_; }
    double py() const { return y_; }
    double pz() const { return z_; }

    double m2() const  {
        return t_ * t_ - x_ * x_ - y_ * y_ - z_ * z_;
    }

    double dot(const FourMomentum& p) const {
        return e() * p.e() - px() * p.px() - py() * p.py() - pz() * p.pz();
    }
};
}  // namespace mat

#endif  // MAT_SRC_MOMENTUM_H_
