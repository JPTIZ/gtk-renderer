#include "geometry.h"

#include <cmath>

#include "../../algebra.h"

using rudolph::geometry::Point3D;

namespace rudolph {

void Point3D::translate(double dx, double dy, double dz) {
    Matrix<double> t({
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        dx, dy, dz, 1
        },
        4, 4
    );

    data = data * t;
}

void Point3D::scale(double sx, double sy, double sz) {
    Matrix<double> t({
        sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1
        },
        4, 4
    );

    data = data * t;
}

void Point3D::rotate_x(double angle) {
    double radian = angle*algebra::pi/180;

    Matrix<double> t({
        1, 0, 0, 0,
        0, std::cos(radian), std::sin(radian), 0,
        0, -std::sin(radian), std::cos(radian), 0,
        0, 0, 0, 1
        },
        4, 4
    );

    data = data * t;
}

void Point3D::rotate_y(double angle) {
    double radian = angle*algebra::pi/180;

    Matrix<double> t({
        std::cos(radian), 0, -std::sin(radian), 0,
        0, 1, 0, 0,
        std::sin(radian), 0, std::cos(radian), 0,
        0, 0, 0, 1
        },
        4, 4
    );

    data = data * t;
}

void Point3D::rotate_z(double angle) {
    double radian = angle*algebra::pi/180;

    Matrix<double> t({
        std::cos(radian), std::sin(radian), 0, 0,
        -std::sin(radian), std::cos(radian), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
        },
        4, 4
    );

    data = data * t;
}

Point3D& Point3D::operator+=(const Point3D& p) {
    x() += p.x();
    y() += p.y();
    z() += p.z();
    return *this;
}

Point3D& Point3D::operator-=(const Point3D& p) {
    return *this += -p;
}

bool Point3D::operator==(const Point3D& p) {
    return ( (x() == p.x()) && (y() == p.y()) && (z() == p.z()) );
}

Point3D geometry::operator-(const Point3D& p) {
    return Point3D{-p.x(), -p.y(), -p.z()};
}

Point3D geometry::operator+(const Point3D& lhs, const Point3D& rhs) {
    return Point3D{rhs.x() + lhs.x(), rhs.y() + lhs.y(), rhs.z() + lhs.z()};
}

Point3D geometry::operator-(const Point3D& lhs, const Point3D& rhs) {
    return lhs + (-rhs);
}

Point3D geometry::operator*(const Point3D& p, int value) {
    return Point3D{p.x() * value, p.y() * value, p.z() * value};
}

Point3D geometry::operator*(const Point3D& p, double value) {
    return Point3D{p.x() * value, p.y() * value, p.z() * value};
}

Point3D geometry::operator*(int value, const Point3D& p) {
    return Point3D{p.x() * value, p.y() * value, p.z() * value};
}

Point3D geometry::operator*(double value, const Point3D& p) {
    return Point3D{p.x() * value, p.y() * value, p.z() * value};
}

}
