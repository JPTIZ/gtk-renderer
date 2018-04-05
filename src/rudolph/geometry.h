#ifndef RUDOLPH_GEOMETRY_H
#define RUDOLPH_GEOMETRY_H

#include "matrix.h"

namespace rudolph {
namespace geometry {

struct Size {
    double width{0};
    double height{0};

    Size(double w, double h):
        width{w},
        height{h}
    {}
};


struct Point2D {
    Matrix<double> data;
    
    Point2D():
        data{ *(new std::vector<double>{0, 0, 1}) }
    {}

    Point2D(double x, double y):
        data{ *(new std::vector<double>{x, y, 1}) }
    {}

    double& x() {
        return data(0, 0);
    }

    double& y() {
        return data(0, 1);
    }

    const double& x() const {
        return data(0, 0);
    }

    const double& y() const {
        return data(0, 1);
    }

    Point2D& operator+=(const Point2D& p);
    Point2D& operator-=(const Point2D& p);

    void translate(double dx, double dy);
    void scale(double sx, double sy);
    void rotate(double angle);

};

Point2D operator-(const Point2D&);
Point2D operator+(const Point2D&, const Point2D&);
Point2D operator-(const Point2D&, const Point2D&);
Point2D operator*(const Point2D&, int);
Point2D operator*(const Point2D&, double);
Point2D operator*(int value, const Point2D& p);
Point2D operator*(double value, const Point2D& p);


struct Rect {
    double x{0};
    double y{0};
    double width{0};
    double height{0};

    Rect(double x, double y, double w, double h):
        x{x},
        y{y},
        width{w},
        height{h}
    {}
};

}
}


#endif
