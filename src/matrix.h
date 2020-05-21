#ifndef MAT_SRC_MATRIX_H_
#define MAT_SRC_MATRIX_H_

namespace mat {
class Matrix22 {
private:
    double a_, b_, c_, d_;

public:
    Matrix22() = delete;
    Matrix22(const double a, const double b, const double c, const double d)
        : a_(a), b_(b), c_(c), d_(d) {}

    double det() const { return a_ * d_ - b_ * c_; }
};
}  // namespace mat

#endif  // MAT_SRC_MATRIX_H_
