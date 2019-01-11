#ifndef RUDOLPH_OBJECTS_SHAPES_H
#define RUDOLPH_OBJECTS_SHAPES_H

#include <vector>
#include <string>
#include "../render/render.h"
#include "../utils/geometry.h"
#include "../utils/matrix.h"

namespace rudolph {
namespace objects {

using Point3D = geometry::Point3D;

class Point {
public:
    Point(double x, double y):
        point{x, y},
        scn_point{x, y},
        scn_valid{false},
        _id{points_id++},
        _name{"point" + std::to_string(_id)}
    {}

    void draw(RenderTarget&);

    double x() const {
        return point.x();
    }

    double y() const {
        return point.y();
    }

    std::string name() const {
        return _name;
    }

    Point3D center() const {
        return point;
    }

    void translate(double dx, double dy);

    void scale(double sx, double sy);

    void rotate_origin(double angle);
    void rotate_pin(double angle, Point3D pin);
    void rotate_center(double angle);


private:
    Point3D point;
    Point3D scn_point;
    bool scn_valid;
    unsigned _id;
    std::string _name;
    const std::string _type{"Point"};
    static unsigned int points_id;
};

class Line {
public:
    Line(Point3D a, Point3D b):
        _a{a}, _b{b},
        scn_valid{false},
        _id{lines_id++},
        _name{"line" + std::to_string(_id)}
    {}

    Line(double x1, double y1, double x2, double y2):
        _a{x1, y1},
        _b{x2, y2},
        scn_valid{false},
        _id{lines_id++},
        _name{"line" + std::to_string(_id)}
    {}

    void draw(RenderTarget&);

    std::string name() const {
        return _name;
    }

    Point3D center() const;

    void translate(double dx, double dy);

    void scale(double sx, double sy);

    void rotate_origin(double angle);
    void rotate_pin(double angle, Point3D pin);
    void rotate_center(double angle);

private:
    Point3D _a;
    Point3D _b;
    Point3D scn_a;
    Point3D scn_b;
    bool scn_valid;
    unsigned _id;
    std::string _name;
    const std::string _type{"Line"};
    static unsigned int lines_id;
};

class Polygon {
public:
    Polygon(std::vector<Point3D> points, bool filled = false):
        _points{std::move(points)},
        scn_points{_points},
        scn_valid{false},
        _id{polygons_id++},
        _name{"polygon" + std::to_string(_id)},
        _filled{filled}
    {}

    void draw(RenderTarget&);

    std::string name() const {
        return _name;
    }

    Point3D center() const;

    void translate(double dx, double dy);

    void scale(double sx, double sy);

    void rotate_origin(double angle);
    void rotate_pin(double angle, Point3D pin);
    void rotate_center(double angle);

private:
    std::vector<Point3D> _points;
    std::vector<Point3D> scn_points;
    bool scn_valid;
    unsigned _id;
    std::string _name;
    bool _filled;

    const std::string _type{"Polygon"};
    static unsigned int polygons_id;
};

class BezierCurve {
public:
    BezierCurve(std::vector<Point3D> points, double step = 0.01);

    void draw(RenderTarget&);

    std::string name() const {
        return _name;
    }

    Point3D center() const;

    void translate(double dx, double dy);
    void scale(double sx, double sy);
    void rotate_origin(double angle);
    void rotate_pin(double angle, Point3D pin);
    void rotate_center(double angle);

    Matrix<double> m_t(double t);
    void generate_curve();

private:
    std::vector<Point3D> _input;
    std::vector<Point3D> _points;
    std::vector<Point3D> scn_points;
    double _step;
    bool scn_valid;
    unsigned _id;
    std::string _name;

    const std::string _type{"BezierCurve"};
    static unsigned int bezier_id;
    static const Matrix<double> matrix_b;
};

}
}

#endif
