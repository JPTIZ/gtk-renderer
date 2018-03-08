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
        location{x, y}
    {}

    void draw(RenderTarget&) const;

    int x() const {
        return location.x;
    }

    int y() const {
        return location.y;
    }

private:
    Point2D location;
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
    Polygon();

    void draw(RenderTarget&) const;

private:
    std::vector<Point2D> _points;
};

}
}

#endif
