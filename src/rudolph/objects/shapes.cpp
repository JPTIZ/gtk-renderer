#include "shapes.h"

#include <iostream>

namespace rudolph {
namespace objects {

unsigned int Point::points_id = 0;
unsigned int Line::lines_id = 0;
unsigned int Polygon::polygons_id = 0;

void Point::draw(RenderTarget& target) const {
    target.draw_point(point);
}

void Point::translate(double dx, double dy) {
	point.translate(dx, dy);
}

void Point::scale(double sx, double sy) {
	point.scale(sx, sy);
}

void Point::rotate_origin(double angle) {
    point.rotate(angle);
}

void Point::rotate_pin(double angle, Point2D pin) {
    point.translate(-pin.x(), -pin.y());
    point.rotate(angle);
    point.translate(pin.x(), pin.y());
}

void Point::rotate_center(double angle) {
	// do nothing
}

void Line::draw(RenderTarget& target) const {
    target.draw_line(_a, _b);
}

Point2D Line::center() const {
    Point2D point{(_a.x() + _b.x())/2, (_a.y() + _b.y())/2};
    return point;
}

void Line::translate(double dx, double dy) {
    _a.translate(dx, dy);
    _b.translate(dx, dy);
}

void Line::scale(double sx, double sy) {
    auto center = this->center();
	  _a.translate(-center.x(), -center.y());
    _b.translate(-center.x(), -center.y());
	  _a.scale(sx, sy);
	  _b.scale(sx, sy);
	  _a.translate(center.x(), center.y());
    _b.translate(center.x(), center.y());
}

void Line::rotate_origin(double angle) {
    _a.rotate(angle);
    _b.rotate(angle);
}

void Line::rotate_pin(double angle, Point2D pin) {
    _a.translate(-pin.x(), -pin.y());
    _b.translate(-pin.x(), -pin.y());
    _a.rotate(angle);
    _b.rotate(angle);
    _a.translate(pin.x(), pin.y());
    _b.translate(pin.x(), pin.y());
}

void Line::rotate_center(double angle) {
	  this->rotate_pin(angle, center());
}

void Polygon::draw(RenderTarget& target) const {
    for (auto i = 0u; i < _points.size() - 1; ++i) {
        target.draw_line(_points[i], _points[i + 1]);
    }

    target.draw_line(_points.back(), _points.front());
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
}

void Polygon::rotate_origin(double angle) {
	for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].rotate(angle);
    }
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
}

void Polygon::rotate_center(double angle) {
	  rotate_pin(angle, center());
}

}
}
