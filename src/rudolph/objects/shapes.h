#ifndef RUDOLPH_OBJECTS_SHAPES_H
#define RUDOLPH_OBJECTS_SHAPES_H

#include <vector>
#include <string>
#include "../render.h"
#include "../geometry.h"

namespace rudolph {
namespace objects {

using Point2D = geometry::Point2D;

class Point {
public:
    Point(double x, double y):
        point{x, y},
        _id{points_id++},
        _name{"point" + std::to_string(_id)}
    {}

    void draw(RenderTarget&) const;

    double x() const {
        return point.x();
    }

    double y() const {
        return point.y();
    }

    std::string name() const {
        return _name;
    }
    
    Point2D center() const {
        return point;
    }

    void translate(double dx, double dy);

    void scale(double sx, double sy);

    void rotate_origin(double angle);
    void rotate_pin(double angle, Point2D pin);
    void rotate_center(double angle);


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

    Line(double x1, double y1, double x2, double y2):
        _a{x1, y1},
        _b{x2, y2},
        _id{lines_id++},
        _name{"line" + std::to_string(_id)}
    {}

    void draw(RenderTarget&) const;

    std::string name() const {
        return _name;
    }

    Point2D center() const;

    void translate(double dx, double dy);

    void scale(double sx, double sy);

    void rotate_origin(double angle);
    void rotate_pin(double angle, Point2D pin);
    void rotate_center(double angle);

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

    Point2D center() const;

    void translate(double dx, double dy);

    void scale(double sx, double sy);

    void rotate_origin(double angle);
    void rotate_pin(double angle, Point2D pin);
    void rotate_center(double angle);

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
