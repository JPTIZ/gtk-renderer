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

inline Point operator-(const Point& p) {
    return Point{-p.x, -p.y};
}

inline Point operator+(const Point& lhs, const Point& rhs) {
    return Point{rhs.x + lhs.x, rhs.y + lhs.y};
}

inline Point operator-(const Point& lhs, const Point& rhs) {
    return rhs + (-lhs);
}

inline Point operator*(const Point& p, int value) {
    return Point{p.x * value, p.y * value};
}

inline Point operator*(const Point& p, double value) {
    return Point{int(p.x * value), int(p.y * value)};
}


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

inline Rect operator+(const Rect& r, const Point& p) {
    return Rect{r.x + p.x, r.y + p.y, r.width, r.height};
}

inline Rect operator-(const Rect& r, const Point& p) {
    return r + (-p);
}

}
}


#endif
