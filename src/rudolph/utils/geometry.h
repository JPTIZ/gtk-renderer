#ifndef RUDOLPH_GEOMETRY_H
#define RUDOLPH_GEOMETRY_H

#include <memory>

namespace rudolph {
namespace geometry {

struct Size {
    double width{0};
    double height{0};

    Size(double w, double h):
        width{w},
        height{h}
    {}
};

}
}


#endif
