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

    Line(int x1, int y1, int x2, int y2):
        _a{x1, y1},
        _b{x2, y2}
    {}

    void draw(RenderTarget&) const;

private:
    Point2D _a;
    Point2D _b;
};

class Polygon {
public:
    Polygon(std::vector<Point2D> points):
        _points{points}
    {}

    void draw(RenderTarget&) const;

private:
    std::vector<Point2D> _points;
};

}
}

#endif
