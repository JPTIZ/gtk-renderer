#ifndef RUDOLPH_OBJECTS_SHAPES_H
#define RUDOLPH_OBJECTS_SHAPES_H

#include <vector>
#include <string>
#include "../render.h"
#include "../geometry.h"

namespace rudolph {
namespace objects {

using Point2D = geometry::Point;

class Point {
public:
    Point(int x, int y):
        point{x, y},
        _id{points_id++},
        _name{"point" + std::to_string(_id)}
    {}

    void draw(RenderTarget&) const;

    int x() const {
        return point.x;
    }

    int y() const {
        return point.y;
    }

    std::string name() const {
        return _name;
    }

private:
    Point2D point;
    unsigned _id;
    std::string _name;
    const std::string _type{"Point"};
    static unsigned int points_id;
};

class Line {
public:
    Line(Point2D a, Point2D b):
        _a{a}, _b{b},
        _id{lines_id++},
        _name{"line" + std::to_string(_id)}
    {}

    Line(int x1, int y1, int x2, int y2):
        _a{x1, y1},
        _b{x2, y2},
        _id{lines_id++},
        _name{"line" + std::to_string(_id)}
    {}

    void draw(RenderTarget&) const;

    std::string name() const {
        return _name;
    }

private:
    Point2D _a;
    Point2D _b;
    unsigned _id;
    std::string _name;
    const std::string _type{"Line"};
    static unsigned int lines_id;
};

class Polygon {
public:
    Polygon(std::vector<Point2D> points):
        _points{std::move(points)},
        _id{polygons_id++},
        _name{"polygon" + std::to_string(_id)}
    {}

    void draw(RenderTarget&) const;

    std::string name() const {
        return _name;
    }

private:
    std::vector<Point2D> _points;
    unsigned _id;
    std::string _name;
    const std::string _type{"Polygon"};
    static unsigned int polygons_id;
};

}
}

#endif
