#ifndef RUDOLPH_OBJECTS_SHAPES_H
#define RUDOLPH_OBJECTS_SHAPES_H

#include <vector>
#include "../render.h"
#include "../geometry.h"

namespace rudolph {
namespace objects {

using Point2D = geometry::Point;

class Point {
public:
    Point(int x, int y):
        point{x, y}
    {}

    void draw(RenderTarget&) const;

    int x() const {
        return point.x;
    }

    int y() const {
        return point.y;
    }

private:
    Point2D point;
};

class Line {
public:
    Line(Point2D a, Point2D b):
        _a{a}, _b{b}
    {}

    void draw(RenderTarget&) const;

private:
    Point2D _a;
    Point2D _b;
};

class Polygon {
public:
    void draw(RenderTarget&) const;

private:
    std::vector<Point2D> _points;
};

}
}

#endif
