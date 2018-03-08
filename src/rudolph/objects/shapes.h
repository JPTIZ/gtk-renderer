#ifndef RUDOLPH_OBJECTS_SHAPES_H
#define RUDOLPH_OBJECTS_SHAPES_H

#include <vector>
#include "../render.h"

namespace rudolph{
namespace objects {

class Point: render::Drawable {
public:
    Point(int x, int y):
        _x{x}, _y{y}
    {}

    void draw(render::RenderTarget&) const override;

    int x() const {
        return _x;
    }

    int y() const {
        return _y;
    }

private:
    int _x;
    int _y;
};

class Line: render::Drawable {
public:
    Line(Point a, Point b):
        _a{a}, _b{b}
    {}

    void draw(render::RenderTarget&) const override;

private:
    Point _a;
    Point _b;
};

class Polygon: render::Drawable {
public:
    Polygon();

    void draw(render::RenderTarget&) const override;

private:
    std::vector<Point> _points;
};

}
}
#endif
