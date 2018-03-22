#include "geometry.h"

using rudolph::geometry::Point;

namespace rudolph {

Point& Point::operator+=(const Point& p) {
    x += p.x;
    y += p.y;
    return *this;
}

Point& Point::operator-=(const Point& p) {
    return *this += -p;
}

Point geometry::operator-(const Point& p) {
    return Point{-p.x, -p.y};
}

Point geometry::operator+(const Point& lhs, const Point& rhs) {
    return Point{rhs.x + lhs.x, rhs.y + lhs.y};
}

Point geometry::operator-(const Point& lhs, const Point& rhs) {
    return lhs + (-rhs);
}

Point geometry::operator*(const Point& p, int value) {
    return Point{p.x * value, p.y * value};
}

Point geometry::operator*(const Point& p, double value) {
    return Point{int(p.x * value), int(p.y * value)};
}

}
