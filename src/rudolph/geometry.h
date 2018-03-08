#ifndef RUDOLPH_GEOMETRY_H
#define RUDOLPH_GEOMETRY_H

namespace rudolph {
namespace geometry {

struct Size {
    int width{0};
    int height{0};

    Size(int w, int h):
        width{w},
        height{h}
    {}
};

}
}

#endif
