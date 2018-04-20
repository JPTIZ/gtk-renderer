#include "geometry.h"

#include <cmath>

#include "../algebra.h"

using rudolph::geometry::Point2D;

namespace rudolph {

void Point2D::translate(double dx, double dy) {
    Matrix<double> t(3, 3);
    t(0, 0) = 1;
    t(1, 1) = 1;
    t(2, 0) = dx;
    t(2, 1) = dy;
    t(2, 2) = 1;

    data = data * t;
}

void Point2D::scale(double sx, double sy) {
    Matrix<double> t(3, 3);
    t(0, 0) = sx;
    t(1, 1) = sy;
    t(2, 2) = 1;

    data = data * t;
}

void Point2D::rotate(double angle) {
    Matrix<double> t(3, 3);
    t(0, 0) = std::cos(angle*algebra::pi/180);
    t(0, 1) = -std::sin(angle*algebra::pi/180);
    t(1, 0) = std::sin(angle*algebra::pi/180);
    t(1, 1) = std::cos(angle*algebra::pi/180);
    t(2, 2) = 1;

    data = data * t;
}

Point2D& Point2D::operator+=(const Point2D& p) {
    x() += p.x();
    y() += p.y();
    return *this;
}

Point2D& Point2D::operator-=(const Point2D& p) {
    return *this += -p;
}

bool Point2D::operator==(const Point2D& p) {
    return ( (x() == p.x()) && (y() == p.y()) );
}

Point2D geometry::operator-(const Point2D& p) {
    return Point2D{-p.x(), -p.y()};
}

Point2D geometry::operator+(const Point2D& lhs, const Point2D& rhs) {
    return Point2D{rhs.x() + lhs.x(), rhs.y() + lhs.y()};
}

Point2D geometry::operator-(const Point2D& lhs, const Point2D& rhs) {
    return lhs + (-rhs);
}

Point2D geometry::operator*(const Point2D& p, int value) {
    return Point2D{p.x() * value, p.y() * value};
}

Point2D geometry::operator*(const Point2D& p, double value) {
    return Point2D{p.x() * value, p.y() * value};
}

Point2D geometry::operator*(int value, const Point2D& p) {
    return Point2D{p.x() * value, p.y() * value};
}

Point2D geometry::operator*(double value, const Point2D& p) {
    return Point2D{p.x() * value, p.y() * value};
}

}
