#ifndef RUDOLPH_CAMERA_H
#define RUDOLPH_CAMERA_H

#include "../geometry.h"

namespace rudolph {

class CameraWindow {
    using Point2D = geometry::Point2D;
public:
    CameraWindow():
        _top_right{Point2D{200, 100}},
        _bottom_left{Point2D{0, 0}},
        _angle{0}
    {}

    CameraWindow(Point2D bottom_left, Point2D top_right):
        _top_right{top_right},
        _bottom_left{bottom_left},
        _angle{0}
    {}

    CameraWindow(geometry::Size size):
        _top_right{size.width, size.height},
        _bottom_left{0, 0},
        _angle{0}
    {}

    Point2D top_right() const {
        return _top_right;
    }

    Point2D bottom_left() const {
        return _bottom_left;
    }

    int width() const {
        return (_top_right - _bottom_left).x();
    }

    int height() const {
        return (_top_right - _bottom_left).y();
    }

    double angle() const {
        return _angle;
    }

    void move(double dx, double dy);
    void zoom(double step);
    void set_width(int width);
    void set_height(int height);

    void resize(int width, int height) {
        set_width(width);
        set_height(height);
    }

    void resize(geometry::Size size) {
        resize(size.width, size.height);
    }

  private:
    Point2D _top_right;
    Point2D _bottom_left;
    double _angle;
};

}

#endif
