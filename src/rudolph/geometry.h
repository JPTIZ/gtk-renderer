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


struct Point {
    int x{0};
    int y{0};

    Point(int x, int y):
        x{x},
        y{y}
    {}
};


struct Rect {
    int x{0};
    int y{0};
    int width{0};
    int height{0};

    Rect(int x, int y, int w, int h):
        x{x},
        y{y},
        width{w},
        height{h}
    {}
};

}
}


#endif
