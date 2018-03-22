#ifndef RUDOLPH_CAMERA_H
#define RUDOLPH_CAMERA_H

#include <cmath>

#include "../geometry.h"

namespace rudolph {

class CameraWindow {
    using Point2D = geometry::Point;
public:
    CameraWindow():
        _top_right{Point2D{200, 100}},
        _bottom_left{Point2D{0, 0}}
    {}

    CameraWindow(Point2D bottom_left, Point2D top_right):
        _top_right{top_right},
        _bottom_left{bottom_left}
    {}

    CameraWindow(geometry::Size size):
        _top_right{size.width, size.height},
        _bottom_left{0, 0}
    {}

    Point2D top_right() const {
        return _top_right;
    }

    Point2D bottom_left() const {
        return _bottom_left;
    }

    int width() const {
        return std::abs((_bottom_left - _top_right).x);
    }

    int height() const {
        return std::abs((_bottom_left - _top_right).y);
    }

    void move(int dx, int dy);
    void zoom(double step);
    void set_width(int width);
    void set_height(int height);

  private:
    Point2D _top_right;
    Point2D _bottom_left;
};

}

#endif
