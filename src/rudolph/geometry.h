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

    Point& operator+=(const Point& p) {
        *this = *this + p;
        return *this;
    }

    Point& operator-=(const Point& p) {
        *this = *this - p;
        return *this;
    }

    friend Point operator-(const Point& p) {
        return Point{-p.x, -p.y};
    }

    friend Point operator+(const Point& lhs, const Point& rhs) {
        return Point{rhs.x + lhs.x, rhs.y + lhs.y};
    }

    friend Point operator-(const Point& lhs, const Point& rhs) {
        return rhs + (-lhs);
    }

    friend Point operator*(const Point& p, int value) {
        return Point{p.x * value, p.y * value};
    }

    friend Point operator*(const Point& p, double value) {
        return Point{int(p.x * value), int(p.y * value)};
    }

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
