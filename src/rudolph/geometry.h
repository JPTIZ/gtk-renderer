#ifndef RUDOLPH_GEOMETRY_H
#define RUDOLPH_GEOMETRY_H

#include "matrix.h"

namespace rudolph {
namespace geometry {

struct Size {
    int width{0};
    int height{0};

    Size(int w, int h):
        width{w},
        height{h}
    {}
};


struct Point2D {
    Matrix<int> data;
    
    Point2D():
        data{ *(new std::vector<int>{0, 0, 1}) }
    {}

    Point2D(int x, int y):
        data{ *(new std::vector<int>{x, y, 1}) }
    {}

    int& x() {
        return data(0, 0);
    }

    int& y() {
        return data(0, 1);
    }

    const int& x() const {
        return data(0, 0);
    }

    const int& y() const {
        return data(0, 1);
    }

    Point2D& operator+=(const Point2D& p);
    Point2D& operator-=(const Point2D& p);

    void translate(int dx, int dy);
    void scale(int sx, int sy);
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
    int x{0};
    int y{0};
    int width{0};
    int height{0};

    Rect(int x, int y, int w, int h):
        x{x},
        y{y},
        width{w},
        height{h}
    {}
};

}
}


#endif
