#include "shapes.h"

#include <iostream>

namespace rudolph {
namespace objects {

unsigned int Point::points_id = 0;
unsigned int Line::lines_id = 0;
unsigned int Polygon::polygons_id = 0;

void Point::draw(RenderTarget& target) {
    if (!scn_valid) {
        scn_point = target.world_to_normal(point);
        scn_valid = true;
    }
    target.draw_point(scn_point);
}

void Point::translate(double dx, double dy) {
	point.translate(dx, dy);
    scn_valid = false;
}

void Point::scale(double sx, double sy) {
	point.scale(sx, sy);
    scn_valid = false;
}

void Point::rotate_origin(double angle) {
    point.rotate(angle);
    scn_valid = false;
}

void Point::rotate_pin(double angle, Point2D pin) {
    point.translate(-pin.x(), -pin.y());
    point.rotate(angle);
    point.translate(pin.x(), pin.y());
    scn_valid = false;
}

void Point::rotate_center(double angle) {
	// do nothing
}

void Line::draw(RenderTarget& target) {
    if (!scn_valid) {
        scn_a = target.world_to_normal(_a);
        scn_b = target.world_to_normal(_b);
        scn_valid = true;
    }
    target.draw_line(scn_a, scn_b);
}

Point2D Line::center() const {
    Point2D point{(_a.x() + _b.x())/2, (_a.y() + _b.y())/2};
    return point;
}

void Line::translate(double dx, double dy) {
    _a.translate(dx, dy);
    _b.translate(dx, dy);
    scn_valid = false;
}

void Line::scale(double sx, double sy) {
    auto center = this->center();
    _a.translate(-center.x(), -center.y());
    _b.translate(-center.x(), -center.y());
    _a.scale(sx, sy);
    _b.scale(sx, sy);
    _a.translate(center.x(), center.y());
    _b.translate(center.x(), center.y());
    scn_valid = false;
}

void Line::rotate_origin(double angle) {
    _a.rotate(angle);
    _b.rotate(angle);
    scn_valid = false;
}

void Line::rotate_pin(double angle, Point2D pin) {
    _a.translate(-pin.x(), -pin.y());
    _b.translate(-pin.x(), -pin.y());
    _a.rotate(angle);
    _b.rotate(angle);
    _a.translate(pin.x(), pin.y());
    _b.translate(pin.x(), pin.y());
    scn_valid = false;
}

void Line::rotate_center(double angle) {
    rotate_pin(angle, center());
}

void Polygon::draw(RenderTarget& target) {
    if (!scn_valid) {
        for (auto i = 0u; i < scn_points.size(); ++i) {
            scn_points[i] = target.world_to_normal(_points[i]);
        }
        scn_valid = true;
    }
    target.draw_polygon(scn_points, _filled);
}

Point2D Polygon::center() const {
    auto point = _points[0];
    for (auto i = 1u; i < _points.size(); ++i) {
        point += _points[i];
    }
    point.x() = point.x()/_points.size();
    point.y() = point.y()/_points.size();
    return point;
}

void Polygon::translate(double dx, double dy) {
    for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].translate(dx, dy);
    }
    scn_valid = false;
}

void Polygon::scale(double sx, double sy) {
    auto center = this->center();
    for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].translate(-center.x(), -center.y());
    }
    for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].scale(sx, sy);
    }
    for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].translate(center.x(), center.y());
    }
    scn_valid = false;
}

void Polygon::rotate_origin(double angle) {
	for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].rotate(angle);
    }
    scn_valid = false;
}

void Polygon::rotate_pin(double angle, Point2D pin) {
	for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].translate(-pin.x(), -pin.y());
    }
    for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].rotate(angle);
    }
    for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].translate(pin.x(), pin.y());
    }
    scn_valid = false;
}

void Polygon::rotate_center(double angle) {
    rotate_pin(angle, center());
}

}
}
