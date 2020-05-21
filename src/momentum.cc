#include "momentum.h"

#include <ostream>

namespace mat {
std::ostream& operator<<(std::ostream& os, const FourMomentum& p) {
    os << "e = " << p.t_ << ", px = " << p.x_ << ", py = " << p.y_
       << ", pz = " << p.z_;
    return os;
}
}  // namespace mat
